
#include "string_bitfield_map.h"

#include <ranges>

using namespace boost;
using namespace FRS::utility;

auto string_bitfield_map::id(const std::string& s) -> boost::dynamic_bitset<>
{
	lock_t lk (_mutex);

	if (_map.right.count(s) == 1) return _map.right.at(s);

	/** need to add this value **/

	/* find max current bitfield value */
	const auto max_value = this->max_valid_id();

	auto result = max_value << 1;
	if (result.none()) result.set(0);

	_map.insert(map_t::value_type(result, s));
	return result;
}

auto string_bitfield_map::to_string(const boost::dynamic_bitset<>& id) const -> std::string
{
	try 
	{
		lock_t lk (_mutex);

		if (id.size() == _max_bitfield_size) return _map.left.at(id);

		/* the bitfield size of the map has changed and the
			 * given value needs to be adjusted
			 *
			 * This happens if more strings are added to the map
			 * (enough to cause it to resize) and an old value
			 * is used
			 */

		/* NOTE: This is _VERY_ inefficient and should be avoided
			 * ie. set a breakpoint here and if it hits,
			 * the initial bitset size needs to be increased
			 */

		auto id2 = id;
		id2.resize(this->max_bitfield_size());

		return _map.left.at(id2);
	}
	catch (std::out_of_range&)
	{
		return "UNK 0x" + to_hex(id);
	}	
}

auto string_bitfield_map::to_hex(const boost::dynamic_bitset<>& v) -> std::string
{
	std::vector<boost::dynamic_bitset<>::block_type> blocks;
	boost::to_block_range(v, back_inserter(blocks));
		
	std::string result;
	boost::algorithm::hex(blocks.rbegin(), blocks.rend(), back_inserter(result));

	/* erase leading zeros */
	while (result.size() > 1 && result[0] == '0')
		result.erase(result.begin());

	return result;
}

auto string_bitfield_map::min_valid_bit_position() const -> size_t
{
	const auto min_id = this->min_valid_id();
	if (min_id.none()) return -1;

	/* there should only be 1 bit set,
		 * so return the first one */

	return min_id.find_first();
}

auto string_bitfield_map::max_valid_bit_position() const -> size_t
{
	const auto max_id = this->max_valid_id();
	if (max_id.none()) return -1;

	/* there should only be 1 bit set,
		 * so return the first one */

	return max_id.find_first();
}

auto string_bitfield_map::min_valid_id() const -> boost::dynamic_bitset<>
{
	lock_t lk (_mutex);

	/* if no values in map, return bitset with no bits set */
	if (_map.empty()) return boost::dynamic_bitset<>(_max_bitfield_size);

	const auto initial = _map.left.begin()->first;

	return std::accumulate(_map.left.begin(), _map.left.end(),
	                       initial,
	                       [](const auto& m, const auto& e) { return std::min(m, e.first); });
}

auto string_bitfield_map::max_valid_id() const -> boost::dynamic_bitset<>
{
	lock_t lk (_mutex);

	/* if no values in map, return bitset with no bits set */
	if (_map.empty()) return boost::dynamic_bitset<>(_max_bitfield_size);

	const auto initial = _map.left.begin()->first;

	return std::accumulate(_map.left.begin(), _map.left.end(),
	                       initial,
	                       [](const auto& m, const auto& e) { return std::max(m, e.first); });
}

bool string_bitfield_map::exists(const boost::dynamic_bitset<>& id) const
{
	lock_t lk (_mutex);

	if (id.size() == _max_bitfield_size) return _map.left.count(id) == 1;

	/* see note in to_string */

	auto id2 = id;
	id2.resize(this->max_bitfield_size());

	return _map.left.count(id2) == 1;
}

bool string_bitfield_map::exists(const std::string& s) const
{
	lock_t lk (_mutex);
	return _map.right.count(s) == 1;
}

auto string_bitfield_map::size() const -> unsigned
{
	return static_cast<unsigned>(_map.size());
}

void string_bitfield_map::set_max_bitfield_size(unsigned bits)
{
	if (_max_bitfield_size == bits) return;

	lock_t lk (_mutex);
		
	_max_bitfield_size = bits;

	/* recreate map with correct number of bits */
		
	map_t old_map (_map);
	_map.clear();
		
	for (auto& kv : old_map.left)
	{
		auto bs = kv.first;
		bs.resize(_max_bitfield_size);
		_map.insert(map_t::value_type(bs, kv.second));
	}
}

void string_bitfield_map::set_bit_shift(unsigned shift)
{
	if (_bit_shift == shift) return;
		
	lock_t lk (_mutex);
		
	const auto old_shift = _bit_shift;
	_bit_shift = shift;

	const auto adjustment = _bit_shift - old_shift;

	/* recreate map with correct shift */
		
	map_t old_map (_map);
	_map.clear();
		
	for (auto& kv : old_map.left)
	{
		auto bs = kv.first << adjustment;
		_map.insert(map_t::value_type(bs, kv.second));
	}
}

auto string_bitfield_map::generate_bitmask(const std::vector<std::string> strs) const -> boost::dynamic_bitset<>
{
	lock_t lk (_mutex);

	/* bitset with nothing set */
	boost::dynamic_bitset<> result(this->max_bitfield_size(), 0);

	if (strs.empty()) return result;

	/* add specified channels first */
	for (auto& s : strs)
	{
		if (s[0] == '-') continue;

		if (this->exists(s) == false) continue;

		/* set given bit */
		result |= _map.right.at(s);
	}

	/* subtracted removed channels */
	for (auto& s : strs)
	{
		if (s[0] != '-') continue;

		std::string s1 = s.substr(1);

		/* if no bits are set, set them all and subtract */
		if (result.none())
			result = full_bitmask();

		if (this->exists(s1) == false) continue;

		/* unset given bit */
		result &= ~_map.right.at(s1);
	}

	return result;
}

auto string_bitfield_map::full_bitmask() const -> boost::dynamic_bitset<>
{
	lock_t lk (_mutex);
		
	/* bitset with nothing set */
	boost::dynamic_bitset<> result(this->max_bitfield_size(), 0);

	/* set bits for defined values (there may be a shift and/or gaps) */
	for (const auto& kv : _map.left)
		result |= kv.first;

	return result;
}

auto string_bitfield_map::max_string_width() const -> size_t
{
	auto r = _map.right | std::ranges::views::transform([](const auto& x) { return x.first.size(); });
	return std::ranges::max(r);
}


#pragma once

#include <mutex>
#include <boost/bimap.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/algorithm/string.hpp>

/* bidirectional mapping from string to bitfield
 *
 * bit assignments are generated automatically
 */

namespace FRS { namespace utility {

class string_bitfield_map
{
public:
	using lock_t = std::lock_guard<std::recursive_mutex>;

	string_bitfield_map () : _max_bitfield_size(64), _bit_shift(0) {}

	string_bitfield_map (const string_bitfield_map&) = delete;
	string_bitfield_map (string_bitfield_map&&) = delete;

	auto operator= (const string_bitfield_map&) -> string_bitfield_map& = delete;	
	auto operator= (string_bitfield_map&&) -> string_bitfield_map& = delete;	

	virtual ~string_bitfield_map() = default;

	/* get bitfield value for string */
	auto id (const std::string& s) -> boost::dynamic_bitset<>;

	/* get string for specific bitfield value */
	auto to_string (const boost::dynamic_bitset<>& id) const -> std::string;

	static auto to_hex(const boost::dynamic_bitset<>& v) -> std::string;

	auto min_valid_bit_position() const -> size_t;

	auto max_valid_bit_position() const -> size_t;

	auto min_valid_id() const -> boost::dynamic_bitset<>;

	auto max_valid_id() const -> boost::dynamic_bitset<>;

	bool exists(const boost::dynamic_bitset<>& id) const;

	bool exists(const std::string& s) const;

	auto size() const -> unsigned;

	auto max_bitfield_size () const -> unsigned { return _max_bitfield_size; }

	void set_max_bitfield_size(unsigned bits);

	auto bit_shift () const -> unsigned { return _bit_shift; }

	void set_bit_shift(unsigned shift);

	/* generate a bitmask for the given strings, support "-XXX" for disabling a bit */
	auto generate_bitmask (const std::vector<std::string> strs) const -> boost::dynamic_bitset<>;

	auto full_bitmask () const -> boost::dynamic_bitset<>;

	auto max_string_width() const -> size_t;

protected:
	unsigned _max_bitfield_size;
	unsigned _bit_shift;

	class str_ci_less_than : public std::less<std::string> 
	{
		public:
			bool operator() (const std::string& s1, const std::string& s2) const 
			{
				return boost::algorithm::lexicographical_compare(s1, s2, boost::is_iless());
			}
	};

	using map_t = boost::bimap<boost::dynamic_bitset<>, boost::bimaps::set_of<std::string, str_ci_less_than>>;
	map_t _map;

	mutable std::recursive_mutex _mutex;
};

}}

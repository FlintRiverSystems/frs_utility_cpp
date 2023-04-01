
#pragma once

/* floating point comparison function from 
 * Comparing Floating Point Numbers by Bruce Dawson
 * https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
 *
 * see the article for details on maxUlps = maximum error in terms of 
 * Units in the Last Place.  A value of 1 means only the two adjacent 
 * floating point numbers are considered equal.
 */

#include <assert.h>
#include <stdlib.h>

namespace FRS {
namespace utility {

// Usable AlmostEqual function
inline bool float_compare (float A, float B, int maxUlps) 
{
	//
    // Make sure maxUlps is non-negative and small enough that the
    // default NAN won't compare as equal to anything.
    assert(maxUlps > 0 && maxUlps < 4 * 1024 * 1024);
	
    // Different signs means they do not match
    if (A < 0 != B < 0)
    {
        // Check for equality to make sure +0 == -0
        if (A == B) return true;
        return false;
    }

    // Make aInt lexicographically ordered as a twos-complement int
    int aInt = *(int*)&A;
	
    // Make bInt lexicographically ordered as a twos-complement int
    int bInt = *(int*)&B;

    int intDiff = abs(aInt - bInt);
    if (intDiff <= maxUlps)
        return true;

    return false;
}

// better name
inline bool float_equal (float A, float B, int maxUlps) 
{
	return float_compare(A,B,maxUlps);
}

}}


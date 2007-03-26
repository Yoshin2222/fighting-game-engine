#ifndef INLINE_PAIR

#include "pair.hpp"
#include "assert.hpp"
#include <iostream> // for abs()
#include "debug.hpp"

// 2^32 / 2 / 2 - 1, two of these added together won't overflow a
// signed 32-bit int (Unit)
#define UNIT_SAFE_MAX 1073741823
// TODO: Maybe make this allow larger maximum values, or maybe not.

INLINE Pair::Pair(Unit newX, Unit newY)
	: x(newX), y(newY)
{
	
}

INLINE Pair Pair::operator+(Pair p) const
{
	// This should make sure that each part is less than half the
	// maximum value of Unit.  -1 for starting at 1, -1 for sign
	// bit and -1 for half of that is -3.
	REQUIRE(
		(abs(  x) < UNIT_SAFE_MAX) &&
		(abs(p.x) < UNIT_SAFE_MAX) &&
		(abs(  y) < UNIT_SAFE_MAX) &&
		(abs(p.y) < UNIT_SAFE_MAX) 
		);
	return Pair(x + p.x, y + p.y);
}

INLINE Pair Pair::operator-(Pair p) const
{
	// This should make sure that each part is less than half the
	// maximum value of Unit.  -1 for starting at 1, -1 for sign
	// bit and -1 for half of that is -3.
	REQUIRE(
		(abs(  x) < UNIT_SAFE_MAX) &&
		(abs(p.x) < UNIT_SAFE_MAX) &&
		(abs(  y) < UNIT_SAFE_MAX) &&
		(abs(p.y) < UNIT_SAFE_MAX) 
		);
	return Pair(x - p.x, y - p.y);
}
	
INLINE Pair& Pair::operator+=(Pair p)
{
	// This should make sure that each part is less than half the
	// maximum value of Unit.  -1 for starting at 1, -1 for sign
	// bit and -1 for half of that is -3.
	REQUIRE(
		(abs(  x) < UNIT_SAFE_MAX) &&
		(abs(p.x) < UNIT_SAFE_MAX) &&
		(abs(  y) < UNIT_SAFE_MAX) &&
		(abs(p.y) < UNIT_SAFE_MAX) 
		);
	x += p.x;
	y += p.y;
	return *this;
}

INLINE Pair& Pair::operator-=(Pair p)
{
	// This should make sure that each part is less than half the
	// maximum value of Unit.  -1 for starting at 1, -1 for sign
	// bit and -1 for half of that is -3.
	REQUIRE(
		(abs(  x) < UNIT_SAFE_MAX) &&
		(abs(p.x) < UNIT_SAFE_MAX) &&
		(abs(  y) < UNIT_SAFE_MAX) &&
		(abs(p.y) < UNIT_SAFE_MAX) 
		);
	x -= p.x;
	y -= p.y;
	return *this;
}

INLINE Pair& Pair::operator=(Pair p)
{
	x = p.x;
	y = p.y;

	return *this;
}

INLINE Pair Pair::min(Pair p) const
{
	return Pair(std::min(x, p.x), std::min(y, p.y));
}

INLINE Pair Pair::max(Pair p) const
{
	return Pair(std::max(x, p.x), std::max(y, p.y));
}


/*
#include <iostream>
void Pair::print()
{
	REQUIRE(
		(abs(  x) < UNIT_SAFE_MAX) &&
		(abs(p.x) < UNIT_SAFE_MAX) &&
		(abs(  y) < UNIT_SAFE_MAX) &&
		(abs(p.y) < UNIT_SAFE_MAX) 
		);
	x = p.x;
	y = p.y;
}

INLINE void Pair::debugPrint() const
{
	std::cout << "(" << x << ", " << y << ")";
}
*/

#endif // ifndef INLINE

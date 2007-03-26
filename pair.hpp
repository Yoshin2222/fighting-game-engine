#ifndef PAIR_H
#define PAIR_H

#include "unit.hpp"

#ifdef INLINE_PAIR
#define INLINE inline
#else
#define INLINE
#endif // INLINE_PAIR

// Since Pair is such a small data type, and because ideally it will
// be completely inlined, it tends to not use references
struct Pair
{
	INLINE Pair(Unit newX = 0, Unit newY = 0);

	INLINE Pair operator+(Pair p) const;
	INLINE Pair operator-(Pair p) const;	

	INLINE Pair& operator+=(Pair p);
	INLINE Pair& operator-=(Pair p);

	INLINE Pair& operator=(Pair p);

	INLINE Pair min(Pair p) const;
	INLINE Pair max(Pair p) const;

	Unit x, y;

	INLINE void debugPrint( void ) const;
};

#ifdef INLINE_PAIR
#undef INLINE_PAIR
#include "pair.cpp"
#define INLINE_PAIR
#endif // INLINE_PAIR

#endif // PAIR_H



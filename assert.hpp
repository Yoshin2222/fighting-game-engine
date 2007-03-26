#ifndef ASSERT_H
#define ASSERT_H

/*------------------------------------------------------------------*/

#ifndef BREAK
#define OPTIONALLY_ABORT ((void) 0)
#else
#define OPTIONALLY_ABORT abort()
#endif // BREAK

/*------------------------------------------------------------------*/

#ifndef NDEBUG

namespace assert
{
	void aFailed(char *expr, char *file, int line);
} 

// REQUIRE and ENSURE are the same as ASSERT.  The reason for the
// distinction is that REQUIRE and ENSURE imply that a function's
// pre-conditions and post-conditions respectively are being checked,
// while ASSERT is for all other cases.

#define ASSERT(expr) \
if (expr) {} else assert::aFailed(#expr,__FILE__,__LINE__)

#define REQUIRE(expr) \
if (expr) {} else assert::aFailed(#expr,__FILE__,__LINE__)

#define ENSURE(expr) \
if (expr) {} else assert::aFailed(#expr,__FILE__,__LINE__)

/*********************************************************************
*       NDEBUG                                                       *
*********************************************************************/

#else // NDEBUG

#define ASSERT(ignore) ((void) 0)
#define REQUIRE(ignore) ((void) 0)
#define ENSURE(ignore) ((void) 0)

#endif // NDEBUG

#endif // ASSERT_H

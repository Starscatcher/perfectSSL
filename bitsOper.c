#include "ssl.h"

t_uint	fBit(t_uint x, t_uint y, t_uint z)
{
	t_uint	res;

	res = (x & y) | ((~x) & z);
	return (res);
}

t_uint	gBit(t_uint x, t_uint y, t_uint z)
{
	t_uint res;

	res = (x & z) | ((~z) & y);
	return (res);
}

t_uint	hBit(t_uint x, t_uint y, t_uint z)
{
	t_uint res;

	res = x ^ y ^ z;
	return (res);
}

t_uint	lBit(t_uint x, t_uint y, t_uint z)
{
	t_uint res;

	res = y ^ ((~z) | x);
	return (res);
}

t_ullint	fRotr512(t_ullint a, int s)
{
	a = a >> s | a << (64 - s);
	return (a);
}

t_uint	fRotr(t_uint a, int s)
{
	a = a >> s | a << (32 - s);
	return (a);
}

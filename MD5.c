#include "ssl.h"

// algo

void	rMD5(t_md *hash, t_uint *param, t_uint (*f)(t_uint, t_uint, t_uint))
{
	t_uint			n;
	const t_uint	t[] = {
			0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
			0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
			0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
			0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
			0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
			0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
			0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
			0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
			0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
			0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
			0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
			0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
			0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
			0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
			0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
			0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
	};

	n = hash->a + \
		f(hash->next->a, hash->next->next->a, hash->next->next->next->a) \
		+ param[0] + t[param[2]];
	n = n << param[1] | n >> (32 - param[1]);
	hash->a = hash->next->a + n;
}

void	transformationMD5(int *i, int *x, t_md *hash, t_uint *arr)
{
	t_uint			param[3];
	const t_uint	r[] = {
			7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
			5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
			4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
			6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
	};

	param[0] = (t_uint)arr[*x];
	param[1] = r[*i];
	param[2] = (t_uint)*i;
	if (*i < 16)
		rMD5(hash, param, &fBit);
	else if (*i < 32)
		rMD5(hash, param, &gBit);
	else if (*i < 48)
		rMD5(hash, param, &hBit);
	else if (*i < 64)
		rMD5(hash, param, &lBit);
	*x = *i < 16 ? *x + 1 : *x;
	*x = *i >= 16 && *i < 32 ? (*x + 5) % 16 : *x;
	*x = *i >= 32 && *i < 48 ? (*x + 3) % 16 : *x;
	*x = *i >= 48 && *i < 64 ? (*x + 7) % 16 : *x;
	++*i;
}

void	aaEqualAMD5(t_md *hash)
{
	hash->aa = hash->a;
	hash = hash->next;
	hash->aa = hash->a;
	hash = hash->next;
	hash->aa = hash->a;
	hash = hash->next;
	hash->aa = hash->a;
}

void	aPlusEqualAaMD5(t_md *hash)
{
	hash->a += hash->aa;
	hash = hash->next;
	hash->a += hash->aa;
	hash = hash->next;
	hash->a += hash->aa;
	hash = hash->next;
	hash->a += hash->aa;
}

void	algMD5(t_md *hash, ssize_t size, t_uint *arr)
{
	int i;
	int x;
	int j;
	int k;

	x = 0;
	j = 0;
	k = 0;
	while (j < size)
	{
		i = 0;
		aaEqualAMD5(hash);
		while (i < 64)
		{
			transformationMD5(&i, &x, hash, arr + k);
			hash = hash->next->next->next;
			x = i == 16 ? 1 : x;
			x = i == 32 ? 5 : x;
			x = i == 48 ? 0 : x;
		}
		aPlusEqualAaMD5(hash);
		j += 64;
		k += 16;
	}
	free(arr);
}

// end

void		initializeBuffMD5(t_md *lst)
{
	t_md	*hash;
	t_md	*head;

	head = lst;
	lst->a = 0x67452301;
	hash = createMdStruct();
	lst->next = hash;
	lst = lst->next;
	lst->a = 0xEFCDAB89;
	hash = createMdStruct();
	lst->next = hash;
	lst = lst->next;
	lst->a = 0x98BADCFE;
	hash = createMdStruct();
	lst->next = hash;
	lst = lst->next;
	lst->a = 0x10325476;
	lst->next = head;
}

t_uint			*char2intMD5(t_uchar *bef, ssize_t newsize, ssize_t size)
{
	t_uint	*aft;
	int		i;

	i = 0;
	aft = (t_uint*)malloc(sizeof(t_uint) * newsize);
	while (i < newsize)
		aft[i++] = 0;
	size--;
	newsize--;
	while (newsize >= 0)
	{
		aft[newsize] = aft[newsize] | bef[size--] << 24;
		aft[newsize] = aft[newsize] | bef[size--] << 16;
		aft[newsize] = aft[newsize] | bef[size--] << 8;
		aft[newsize] = aft[newsize] | bef[size--] << 0;
		newsize--;
	}
	free(bef);
	return (aft);
}

t_uint			*writeLenMD5(ssize_t len, t_uint *data, ssize_t i)
{
	while (len)
	{
		data[i] = data[i] | (t_uint)len << 0;
		len = len >> 8;
		data[i] = data[i] | (t_uint)len << 8;
		len = len >> 8;
		data[i] = data[i] | (t_uint)len << 16;
		len = len >> 8;
		data[i] = data[i] | (t_uint)len << 24;
		len = len >> 8;
		i++;
	}
	return (data);
}

void	printHashMD5(t_md *hash)
{
	int				i;
	unsigned char	*tmp;
	t_md			*head;

	i = 0;
	head = hash;
	while (i < 4)
	{
		tmp = (unsigned char *)&hash->a;
		ft_printf("%.2x%.2x%.2x%.2x", tmp[0], tmp[1], tmp[2], tmp[3]);
		hash = hash->next;
		i++;
	}
	delMdStruct(head);
}

void	MD5(char *input, size_t len)
{
	ssize_t	size;
	t_uchar	*newinp;
	t_uint	*arr;
	t_md	*hash;

	size = ft_find_size(len);
	newinp = ft_alignment(size, input);
	hash = createMdStruct();
	initializeBuffMD5(hash);
	arr = char2intMD5(newinp, size / 4, size);
	arr = writeLenMD5((len * 8), arr, ((size / 4) - 2));
	algMD5(hash, size, arr);
	printHashMD5(hash);
}

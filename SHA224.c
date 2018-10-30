#include "ssl.h"

t_uint		*initializeBuff224(t_uint *hash)
{
	hash = (t_uint*)malloc(sizeof(t_uint) * 8);
	hash[0] = 0xc1059ed8;
	hash[1] = 0x367cd507;
	hash[2] = 0x3070dd17;
	hash[3] = 0xf70e5939;
	hash[4] = 0xffc00b31;
	hash[5] = 0x68581511;
	hash[6] = 0x64f98fa7;
	hash[7] = 0xbefa4fa4;
	return (hash);
}

void	printHash224(t_uint *hash)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		ft_printf("%.8x", hash[i]);
		i++;
	}
	free(hash);
}

void	SHA224(char *input, size_t len)
{
	ssize_t	size;
	t_uchar	*newinp;
	t_uint	*arr;
	t_uint	*hash;

	size = ft_find_size(len);
	newinp = ft_alignment(size, input);
	hash = initializeBuff224(NULL);
	arr = char2int256(newinp, size / 4, size);
	arr = writeLen256((len * 8), arr, ((size / 4) - 1));
	hash = algSHA256(size, arr, hash);
	printHash224(hash);
}

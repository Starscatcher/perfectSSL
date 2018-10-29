#include "ssl.h"

t_ullint	*initializeBuff384(t_ullint *hash)
{
	hash = (t_ullint*)malloc(sizeof(t_ullint) * 8);
	hash[0] = 0xcbbb9d5dc1059ed8;
	hash[1] = 0x629a292a367cd507;
	hash[2] = 0x9159015a3070dd17;
	hash[3] = 0x152fecd8f70e5939;
	hash[4] = 0x67332667ffc00b31;
	hash[5] = 0x8eb44a8768581511;
	hash[6] = 0xdb0c2e0d64f98fa7;
	hash[7] = 0x47b5481dbefa4fa4;
	return (hash);
}

void	printHash384(t_ullint *hash)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		ft_printf("%.16zx", hash[i]);
		i++;
	}
	free(hash);
}

t_ullint	*hash384(char *input, size_t len)
{
	t_ullint	size;
	t_uchar		*newinp;
	t_ullint	*res;
	t_ullint	*hash;

	size = findSize512(len);
	newinp = alignment512(size, input);
	res = initializeBuff384(NULL);
	hash = char2int512(newinp, (ssize_t)size / 8, size);
	hash = writeLen512(len * 8, hash, (size / 8) - 1);
	hash = alg512(size, hash, res);
	return (hash);
}

void	SHA384(char *input, t_flags *flags)
{
	size_t len;

	len = ft_strlen(input);
	if ((flags->p || flags->s ) && !flags->q && !flags->file && !flags->r)
		ft_printf("%s ( %s ) = ", flags->algName, input);
	printHash384(hash384(input, len));
	if (flags->r && !flags->q && !flags->file)
		ft_printf(" \"%s\"\n", input);
	else if (flags->file)
		ft_printf(" %s\n", input);
	else
		ft_printf("\n");
}

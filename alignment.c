#include "ssl.h"

ssize_t			ft_find_size(ssize_t len)
{
	ssize_t size;

	size = len * 8 + 1;
	while (size % 512 != 448)
		size++;
	size = (size + 64) / 8;
	return (size);
}

t_uchar			*ft_alignment(ssize_t size, char *input)
{
	int		i;
	t_uchar	*res;

	res = (t_uchar*)malloc(sizeof(t_uchar) * (size));
	i = 0;
	while (i < size && input[i])
	{
		res[i] = (t_uchar)input[i];
		i++;
	}
	res[i++] = 0x80;
	while (i < size)
		res[i++] = 0;
	return (res);
}

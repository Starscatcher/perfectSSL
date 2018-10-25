#include "ssl.h"

char	*readFd(int fd)
{
	char		*res;
	ssize_t		ret;
	char		buf[BUFF_SIZE + 1];

	res = ft_strnew(0);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		res = ft_reallcat(res, buf);
	}
	return (res);
}

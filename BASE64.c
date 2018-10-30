#include "ssl.h"

void	printBASE64(ssize_t newlen, char *base64, int equ)
{
	int 	i;
	t_uchar	alph[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	i = 0;
	while (i < newlen)
	{
		ft_printf("%c",alph[(int)(base64[i])]);
		i++;
	}
	while (equ)
	{
		ft_printf("=");
		equ--;
	}
}

void	BASE64(char *input, size_t len)
{
	size_t i;
	size_t j;
	char 	*res;
	size_t	newlen;
	int		equ;

	equ = 0;
	newlen = len + len / 3;
	newlen += len % 3 > 0 ? 1 : 0;
	equ += (len + 1) % 3 == 0 ? 1 : 0;
	equ += (len + 2) % 3 == 0 ? 2 : 0;
	res = ft_strnew(newlen);
	i = 0;
	j = 0;
	while (i < newlen)
	{
		res[i++] = (t_uchar)input[j] >> 2;
		input[j] = (t_uchar)input[j] << 6;
		i < newlen ? res[i++] = (t_uchar)input[j] >> 2 | (t_uchar)input[j + 1] >> 4 : 0;
		j++;
		input[j] = (t_uchar)input[j] << 4;
		i < newlen ? res[i++] = (t_uchar)input[j] >> 2 | input[j + 1] >> 6 : 0;
		j++;
		input[j] = (t_uchar)input[j] << 2;
		i < newlen ? res[i++] = (t_uchar)input[j] >> 2 : 0;
		j++;
	}
	printBASE64(newlen, res, equ);
}

void	printDecBASE64(char *res, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		ft_printf("%c", res[i]);
		i++;
	}
}

void 	decBASE64(char *input, size_t len)
{
	size_t	i;
	size_t 	j;
	char	*alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	char 	*res;

	len -= input[len - 1] == '=' ? 1 : 0;
	len -= input[len - 1] == '=' ? 1 : 0;
	len = len - len / 3;
	res = ft_strnew(len);

	i = 0;
	j = 0;
	while (i < len)
	{
		res[i] = (t_uchar)(ft_strchr(alph, input[j]) - alph) << 2;
		res[i++] |= (t_uchar)(ft_strchr(alph, input[++j]) - alph) >> 4;
		if (i < len)
		{
			res[i] = (t_uchar)(ft_strchr(alph, input[j]) - alph) << 4;
			res[i++] |= (t_uchar)(ft_strchr(alph, input[++j]) - alph) >> 2;
		}
		if (i < len)
		{
			res[i] = (t_uchar)(ft_strchr(alph, input[j++]) - alph) << 6;
			res[i++] |= (t_uchar)(ft_strchr(alph, input[j++]) - alph);
		}
	}
	printDecBASE64(res, len);
}

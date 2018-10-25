/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryabenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 11:17:40 by aryabenk          #+#    #+#             */
/*   Updated: 2018/06/04 10:30:06 by aryabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s) - 1;
	if (s == NULL)
		return (NULL);
	while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i++;
	while (s[j] && j > 0 && (s[j] == ' ' || s[j] == '\t' || s[j] == '\n'))
		j--;
	if (i <= j)
		res = ft_strsub(s, i, j - i + 1);
	else
		res = NULL;
	return (res);
}

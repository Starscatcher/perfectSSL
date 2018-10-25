/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryabenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 15:54:13 by aryabenk          #+#    #+#             */
/*   Updated: 2018/05/08 15:54:14 by aryabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_intcpy(int *new, int *old, int size)
{
	int i;

	i = 0;
	new = (int *)malloc(sizeof(int) * size);
	while (i < size)
	{
		new[i] = old[i];
		i++;
	}
	return (new);
}

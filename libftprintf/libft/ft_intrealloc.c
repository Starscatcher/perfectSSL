/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryabenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 15:54:18 by aryabenk          #+#    #+#             */
/*   Updated: 2018/05/08 15:54:19 by aryabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_int_realloc(int *arr, int size, int newsize)
{
	int *new;
	int i;

	i = 0;
	new = (int*)malloc(sizeof(int) * newsize);
	while (i < size)
	{
		new[i] = arr[i];
		i++;
	}
	free(arr);
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_reverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryabenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 15:53:15 by aryabenk          #+#    #+#             */
/*   Updated: 2018/05/08 15:53:16 by aryabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_int_reverse(int *arr, int len)
{
	int i;

	i = 0;
	len--;
	while (i < len)
	{
		ft_swap(&arr[i], &arr[len]);
		i++;
		len--;
	}
	return (arr);
}

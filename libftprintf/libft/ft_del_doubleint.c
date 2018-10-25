/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_doubleint.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryabenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 15:52:10 by aryabenk          #+#    #+#             */
/*   Updated: 2018/05/08 15:52:10 by aryabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_del_doubleint(int **arr, int len)
{
	if (!arr || !*arr)
		return ;
	while (len)
		ft_intdel(&arr[--len]);
	free(arr);
}

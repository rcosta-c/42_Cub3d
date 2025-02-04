/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcosta-c <rcosta-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 08:19:44 by rcosta-c          #+#    #+#             */
/*   Updated: 2025/01/04 00:03:00 by rcosta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	x;
	int	reslt;
	int	signal;

	x = 0;
	signal = 1;
	reslt = 0;
	while ((nptr[x] >= 9 && nptr[x] <= 13) || nptr[x] == 32)
		x++;
	if (nptr[x] == '-' || nptr[x] == '+')
	{
		if (nptr[x] == '-')
			signal = -1;
		x++;
	}
	while (nptr[x] >= 48 && nptr[x] <= 57)
	{
		reslt *= 10;
		reslt += nptr[x] - 48;
		x++;
	}
	return (reslt * signal);
}

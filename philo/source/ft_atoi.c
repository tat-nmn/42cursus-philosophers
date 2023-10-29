/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnualman <tnualman@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:44:25 by tnualman          #+#    #+#             */
/*   Updated: 2022/09/19 03:41:58 by tnualman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_static_isspace(const char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\r' || c == '\f')
		return (1);
	return (0);
}

static int	ft_atoi_cutoff_handler(int acc, int n)
{
	if (acc < -214748364)
		return (0);
	if (acc > 214748364)
		return (-1);
	if (acc == -214748364)
	{
		if (n > 8)
			return (0);
		return (acc * 10 - n);
	}
	if (acc == 214748364)
	{
		if (n > 7)
			return (-1);
		return (acc * 10 + n);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	acc;

	acc = 0;
	sign = 1;
	while (ft_static_isspace(*str))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while ('0' <= *str && *str <= '9')
	{
		if (acc <= -214748364 || acc >= 214748364)
			return (ft_atoi_cutoff_handler(acc, *str - '0'));
		acc *= 10;
		acc += sign * (*str - '0');
		str++;
	}
	return (acc);
}

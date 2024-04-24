/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:04:13 by yakim             #+#    #+#             */
/*   Updated: 2024/04/24 16:18:06 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "essential_bonus.h"
#include "utils_bonus.h"
#include "error_bonus.h"

int	ft_isspace(char c)
{
	if (c >= 9 && c <= 13)
		return (1);
	else if (c == 32)
		return (1);
	return (0);
}

void	ft_strtod_num(const char *str, double *d)
{
	double	n;

	while (*str && *str != '.')
	{
		if (ft_isdigit(*str) == 0 && *str != '.')
			cus_error("Error\nInput error\n");
		*d = (*d * 10) + (double)(*str - '0');
		str++;
	}
	if (*str == '.')
		str++;
	n = 0.1;
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			cus_error("Error\nInput error\n");
		*d += (*str - '0') * n;
		n /= 10;
		str++;
	}
}

double	ft_strtod(const char *str)
{
	double	d;
	char	sign;

	d = 0.0;
	sign = 0;
	if (str == NULL)
		cus_error("Error\nInput error\n");
	while (ft_isspace(*str))
		str++;
	if (*str == '-' | *str == '+')
	{
		if (*str == '-')
			sign = 1;
		str++;
	}
	ft_strtod_num(str, &d);
	if (sign)
		return (d * -1);
	return (d);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:41:08 by jgoo              #+#    #+#             */
/*   Updated: 2023/10/09 13:42:10 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_cast(unsigned long long ret, int sign)
{
	if (ret > MAXLONG)
	{
		if (sign == -1)
			return (0);
		else
			return (-1);
	}
	return ((int)ret * sign);
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	ret;
	int					sign;

	i = 0;
	ret = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	return (ft_cast(ret, sign));
}

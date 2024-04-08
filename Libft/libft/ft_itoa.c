/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:56:59 by jgoo              #+#    #+#             */
/*   Updated: 2023/10/09 17:40:37 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_numlen(long long n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		len += 1;
		n *= -1;
	}
	while (n != 0)
	{
		n /= 10;
		len ++;
	}
	return (len);
}

void	ft_initialize(long long n, char *s, int len)
{
	int	i;

	i = len - 1;
	if (n == 0)
	{
		s[0] = '0';
		return ;
	}
	while (n != 0)
	{
		s[i--] = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	int			len;
	char		*ret;
	long long	num;

	len = ft_numlen(n);
	num = (long long)n;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	if (num < 0)
	{
		ret[0] = '-';
		num *= -1;
	}
	ft_initialize(num, ret, len);
	if (num == 0)
		ret[1] = '\0';
	else
		ret[len] = '\0';
	return (ret);
}

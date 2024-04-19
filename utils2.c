/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:48:23 by yakim             #+#    #+#             */
/*   Updated: 2024/04/19 13:25:54 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "error.h"

int	is_spacetab(const char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c >= 9 && c <= 13)
		return (1);
	else if (c == 32)
		return (1);
	return (0);
}

double	ft_strtod(const char *str)
{
	double	d;
	char	sign;
	double	n;

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
	while (*str && *str != '.')
	{
		if (ft_isdigit(*str) == 0 && *str != '.')
			cus_error("Error\nInput error\n");
		d = (d * 10) + (double)(*str - '0');
		str++;
	}
	if (*str == '.')
		str++;
	n = 0.1;
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			cus_error("Error\nInput error\n");
		d += (*str - '0') * n;
		n /= 10;
		str++;
	}
	if (sign)
		return (d * -1);
	return (d);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 == '\0' || *s2 == '\0')
			break ;
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	free_split(char **arr)
{
	char	**temp;

	temp = arr;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(arr);
}

char	*remove_nl(char *line)
{
	char *nl;
	char *ret;

	nl = ft_strchr(line, '\n');
	if (nl)
	{
		ret = malloc(ft_strlen(line));
		ft_strlcpy(ret, line, ft_strlen(line));
		free(line);
		return (ret);
	}
	else
		return (line);
}

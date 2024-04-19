/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:24:09 by yakim             #+#    #+#             */
/*   Updated: 2024/04/19 11:54:15 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ft_word_count(char const *s)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && is_spacetab(s[i]) == 1)
			i++;
		if (s[i] != '\0')
			cnt++;
		while (s[i] != '\0' && is_spacetab(s[i]) == 0)
			i++;
	}
	return (cnt);
}

static char	*ft_word_dup(char const *s)
{
	int		i;
	char	*d;
	int		len;

	i = 0;
	len = 0;
	while (s[len] && is_spacetab(s[len]) == 0)
		len++;
	d = (char *)malloc(sizeof(char) * (len + 1));
	if (!d)
		return (0);
	while (s[i] && is_spacetab(s[i]) == 0)
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

static void	ft_free(char **strs, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static int	ft_allocate(char **strs, char const *s, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		while (*s != '\0' && is_spacetab(*s) == 1)
			s++;
		if (*s != '\0')
		{
			strs[i] = ft_word_dup(s);
			if (strs[i] == 0)
			{
				ft_free(strs, i);
				return (0);
			}
		}
		while (*s != '\0' && is_spacetab(*s) == 0)
			s++;
		i++;
	}
	return (1);
}

char	**ft_split_rt(char const *s)
{
	int		len;
	char	**ret;

	len = ft_word_count(s);
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	if (!ret)
	{
		ft_putstr_fd("Memory allocation failed\n", 2);
		exit(1);
	}
	if (ft_allocate(ret, s, len))
		ret[len] = 0;
	else
	{
		ft_putstr_fd("Memory allocation failed\n", 2);
		exit(1);
	}
	return (ret);
}

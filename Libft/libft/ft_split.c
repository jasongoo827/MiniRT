/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:52:45 by jgoo              #+#    #+#             */
/*   Updated: 2023/10/09 16:56:34 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_word_count(char const *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0')
			cnt++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (cnt);
}

char	*ft_word_dup(char const *s, char c)
{
	int		i;
	char	*d;
	int		len;

	i = 0;
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	d = (char *)malloc(sizeof(char) * (len + 1));
	if (!d)
		return (0);
	while (s[i] && s[i] != c)
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

void	ft_free(char **strs, int len)
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

int	ft_allocate(char **strs, char const *s, char c, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != '\0')
		{
			strs[i] = ft_word_dup(s, c);
			if (strs[i] == 0)
			{
				ft_free(strs, i);
				return (0);
			}
		}
		while (*s != '\0' && *s != c)
			s++;
		i++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		len;
	char	**ret;

	len = ft_word_count(s, c);
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	if (!ret)
	{
		ft_putstr_fd("Memory allocation failed\n", 2);
		exit(1);
	}
	if (ft_allocate(ret, s, c, len))
		ret[len] = 0;
	else
	{
		ft_putstr_fd("Memory allocation failed\n", 2);
		exit(1);
	}
	return (ret);
}

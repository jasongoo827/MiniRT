/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:48:23 by yakim             #+#    #+#             */
/*   Updated: 2024/04/24 14:33:27 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"
#include "error_bonus.h"

int	is_spacetab(const char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
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
	char	*nl;
	char	*ret;

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

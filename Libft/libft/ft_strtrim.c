/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:32:00 by jgoo              #+#    #+#             */
/*   Updated: 2023/10/09 16:24:12 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_set(const char *set, char c)
{
	while (*set != '\0')
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

int	ft_count_str(char const *s1, char const *set, int *start, int *end)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	while (s1[i] != '\0')
	{
		if (check_set(set, s1[i]) == 0)
		{
			*start = i;
			break ;
		}
		i++;
	}
	i = len - 1;
	while (i >= 0)
	{
		if (check_set(set, s1[i]) == 0)
		{
			*end = i;
			break ;
		}
		i--;
	}
	return (*end - *start + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;
	int		len;
	char	*ret;

	i = 0;
	start = -1;
	end = -1;
	len = ft_count_str(s1, set, &start, &end);
	if (ft_strlen(s1) == 0 || (start == -1 && end == -1))
	{
		ret = (char *)malloc(sizeof(char));
		if (!ret)
			return (0);
		ret[0] = '\0';
		return (ret);
	}
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	while (start <= end)
		ret[i++] = s1[start++];
	ret[i] = '\0';
	return (ret);
}

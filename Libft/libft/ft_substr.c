/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:03:32 by jgoo              #+#    #+#             */
/*   Updated: 2023/10/09 15:12:03 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ret;
	size_t	j;

	i = 0;
	j = start;
	if (start >= ft_strlen(s))
	{
		ret = (char *) malloc(sizeof(char));
		if (!ret)
			return (0);
		ret[0] = '\0';
		return (ret);
	}
	if (start + len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	while (s[j] != '\0' && i < len)
		ret[i++] = s[j++];
	ret[i] = '\0';
	return (ret);
}

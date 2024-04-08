/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:57:06 by jgoo              #+#    #+#             */
/*   Updated: 2023/10/09 13:57:51 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	if (dst != src)
	{
		if (dst < src)
		{
			i = -1;
			while (++i < (int)len)
				*((unsigned char *)dst + i) = *((unsigned char *)src + i);
		}
		else
		{
			i = (int)len;
			while (--i >= 0)
				*((unsigned char *)dst + i) = *((unsigned char *)src + i);
		}
	}
	return (dst);
}

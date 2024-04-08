/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:06:02 by jgoo              #+#    #+#             */
/*   Updated: 2023/10/09 14:07:10 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	long long		len;
	void			*ret;
	unsigned char	*tmp;

	i = 0;
	len = size * count;
	if (len > MAXSIZE)
		return (0);
	ret = malloc(len);
	if (!ret)
		return (0);
	tmp = (unsigned char *)ret;
	while (i < (size_t)len)
		tmp[i++] = 0;
	return (ret);
}

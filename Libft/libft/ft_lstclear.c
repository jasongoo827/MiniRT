/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:14:08 by jgoo              #+#    #+#             */
/*   Updated: 2023/10/10 17:14:43 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*delnode;

	if (!del || !lst)
		return ;
	node = *lst;
	while (node != NULL)
	{
		delnode = node;
		del(node -> content);
		node = node -> next;
		free(delnode);
	}
	*lst = NULL;
}

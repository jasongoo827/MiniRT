/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:22:07 by jgoo              #+#    #+#             */
/*   Updated: 2023/10/10 17:22:50 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_newhead(t_list *lst, void *ptr,
	void *(*f)(void *))
{
	t_list	*newnode;

	ptr = f(lst -> content);
	if (!ptr)
		return (NULL);
	newnode = ft_lstnew(ptr);
	if (!newnode)
	{
		free(ptr);
		return (NULL);
	}
	return (newnode);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*newnode;
	void	*ptr;

	if (!lst || !f || !del)
		return (NULL);
	ptr = NULL;
	newnode = ft_newhead(lst, ptr, f);
	if (!newnode)
		return (NULL);
	head = newnode;
	while (lst -> next != NULL)
	{
		lst = lst -> next;
		ptr = f(lst -> content);
		newnode -> next = ft_lstnew(ptr);
		if (!newnode -> next || !ptr)
		{
			ft_lstclear(&head, del);
			free(ptr);
			return (NULL);
		}
		newnode = newnode -> next;
	}
	return (head);
}

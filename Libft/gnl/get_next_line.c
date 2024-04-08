/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:00:33 by jgoo              #+#    #+#             */
/*   Updated: 2023/11/14 16:31:22 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list_gnl	*head;
	t_list_gnl			*node;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > MAX_SIZE || fd > C_OPEN_MAX)
		return (NULL);
	node = ft_getfd(head, fd);
	if (node == NULL)
	{
		node = gnl_lstnew(&head, head, fd);
		if (node == NULL)
			return (NULL);
	}
	node -> buf = read_file(node, fd);
	if (node -> buf == NULL)
	{
		remove_lst(&head, head, fd);
		return (NULL);
	}
	line = ft_getline(node -> buf);
	node -> buf = gnl_substr(node -> buf);
	if (node -> buf == NULL || line == NULL)
		remove_lst(&head, head, fd);
	return (line);
}

t_list_gnl	*ft_getfd(t_list_gnl *lst, int fd)
{
	if (lst == NULL)
		return (NULL);
	while (lst != NULL)
	{
		if (lst -> fd == fd)
			return (lst);
		lst = lst -> next;
	}
	return (NULL);
}

t_list_gnl	*gnl_lstnew(t_list_gnl **head, t_list_gnl *lst, int fd)
{
	t_list_gnl	*node;

	node = (t_list_gnl *)malloc(sizeof(t_list_gnl));
	if (node == NULL)
		return (NULL);
	node -> fd = fd;
	node -> buf = (char *)malloc(sizeof(char));
	if (node -> buf == NULL)
	{
		free(node);
		node = NULL;
		return (NULL);
	}
	*node -> buf = '\0';
	node -> next = NULL;
	if (lst == NULL)
		*head = node;
	else
	{
		while (lst -> next != NULL)
			lst = lst -> next;
		lst -> next = node;
	}
	return (node);
}

char	*read_file(t_list_gnl *node, int fd)
{
	char	*buf;
	ssize_t	ret;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
	{
		free(node -> buf);
		return (NULL);
	}
	while (1)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
		{
			free(node -> buf);
			free(buf);
			return (NULL);
		}
		buf[ret] = '\0';
		node -> buf = gnl_strjoin(node -> buf, buf);
		if (ret == 0 || node -> buf == NULL || gnl_strchr(node -> buf, '\n'))
			break ;
	}
	free(buf);
	return (node -> buf);
}

char	*ft_getline(char *buf)
{
	char	*line;
	int		i;

	if (buf == NULL || *buf == '\0')
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] && buf[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] && buf[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

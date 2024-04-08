/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:00:43 by jgoo              #+#    #+#             */
/*   Updated: 2023/11/04 17:00:44 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
// # include "../Libft/libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif
# define MAX_SIZE 9223372036854775807
# define C_OPEN_MAX 49152

typedef struct s_list_gnl
{
	char				*buf;
	int					fd;
	struct s_list_gnl	*next;
}		t_list_gnl;

char		*get_next_line(int fd);
t_list_gnl	*ft_getfd(t_list_gnl *lst, int fd);
t_list_gnl	*gnl_lstnew(t_list_gnl **head, t_list_gnl *lst, int fd);
char		*read_file(t_list_gnl *node, int fd);
char		*ft_getline(char *buf);
void		remove_lst(t_list_gnl **lst, t_list_gnl *node, int fd);
char		*gnl_substr(char *buf);
char		*gnl_strjoin(char *s1, char *s2);
int			gnl_strchr(char *str, char c);
size_t		gnl_strlen(char *str);

#endif
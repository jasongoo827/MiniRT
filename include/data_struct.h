/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:32:01 by jgoo              #+#    #+#             */
/*   Updated: 2024/04/23 11:04:18 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCT_H
# define DATA_STRUCT_H

# include "essential.h"

# define INIT_SIZE 10

typedef struct s_darray
{
	void	**arr;
	int		data_type;
	int		size;
	int		capacity;
}	t_darray;

t_darray	*init_array(int capacity);
void		push_back(t_darray *array, void *node);
int			array_find(t_darray *array, void *f_node);
void		copy_array(void **dst, void **src, int size);
void		free_array(t_darray *array);

#endif

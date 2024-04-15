/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:35:04 by jgoo              #+#    #+#             */
/*   Updated: 2024/04/15 11:26:03 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"
#include "error.h"

t_darray	*init_array(int capacity)
{
	t_darray	*array;

	null_check(array = (t_darray *)malloc(sizeof(t_darray)));
	if (capacity == 0)
		capacity = INIT_SIZE;
	null_check(array->arr = (void **)malloc(sizeof(void *) * capacity));
	ft_bzero(array->arr, sizeof(void *) * capacity);
	array->data_type = sizeof(void *);
	array->size = 0;
	array->capacity = capacity;
	return (array);
}

void	push_back(t_darray *array, void *node)
{
	void	**tmp;

	if (array->size == array->capacity)
	{
		null_check(tmp = malloc(sizeof(void *) * (array->capacity * 2)));
		array->capacity *= 2;
		copy_array(tmp, array->arr, array->size);
		free(array->arr);
		array->arr = tmp;
	}
	array->arr[array->size] = node;
	array->size++;
}

int	array_find(t_darray *array, void *f_node)
{
	int	i;

	i = 0;
	while (i < array->size * array->data_type)
	{
		if (array->arr[i] == f_node)
			return (i);
		i += array->data_type;
	}
	return (-1);
}

void	copy_array(void **dst, void **src, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		dst[i] = src[i];
}

void	free_array(t_darray *array)
{
	int	i;

	if (array == NULL)
		return ;
	i = -1;
	// 만약에 할당된 메모리가 array에 저장되어있다면 해제
	if (array->size != 0)
	{
		while (++i < array->size)
			free(array->arr[i]);
	}
	if (array->arr != NULL)
		free(array->arr);
	free(array);
}

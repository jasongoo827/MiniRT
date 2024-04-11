/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:53:03 by yakim             #+#    #+#             */
/*   Updated: 2024/04/09 20:14:43 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "essential.h"

t_obj	*init_obj(t_type type)
{
	t_obj	*obj;

	null_check(obj = malloc(sizeof(t_obj)));
	obj->type = type;
	if (type == SPHERE)
		null_check(obj->ptr = malloc(sizeof(t_sphere)));
	else if (type == PLANE)
		null_check(obj->ptr = malloc(sizeof(t_plane)));
	else if (type == CYLINDER)
		null_check(obj->ptr = malloc(sizeof(t_cylinder)));
	else
		cus_error("Error\nUndefined obj type\n");
	return (obj);
}

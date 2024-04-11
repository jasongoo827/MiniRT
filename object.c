/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:53:03 by yakim             #+#    #+#             */
/*   Updated: 2024/04/11 16:23:36 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "essential.h"
#include "object.h"

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

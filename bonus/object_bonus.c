/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:53:03 by yakim             #+#    #+#             */
/*   Updated: 2024/04/24 14:31:15 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "essential_bonus.h"
#include "object_bonus.h"

t_obj	*init_obj(t_type type)
{
	t_obj	*obj;

	null_check(obj = ft_calloc(1, sizeof(t_obj)));
	obj->type = type;
	if (type == LIGHT)
		null_check(obj->ptr = ft_calloc(1, sizeof(t_light)));
	else if (type == SPHERE)
		null_check(obj->ptr = ft_calloc(1, sizeof(t_sphere)));
	else if (type == PLANE)
		null_check(obj->ptr = ft_calloc(1, sizeof(t_plane)));
	else if (type == CYLINDER)
		null_check(obj->ptr = ft_calloc(1, sizeof(t_cylinder)));
	else if (type == CONE)
		null_check(obj->ptr = ft_calloc(1, sizeof(t_cone)));
	else
		cus_error("Error\nUndefined obj type\n");
	return (obj);
}

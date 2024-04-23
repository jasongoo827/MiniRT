/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:05:07 by jgoo              #+#    #+#             */
/*   Updated: 2024/04/23 19:57:35 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	checkerboard(t_info *info)
{
	double	u;
	double	v;
	int		u2;
	int		v2;

	u = 0.0;
	v = 0.0;
	if (info->record.obj->type == SPHERE)
		sphere_map(info, &u, &v);
	else if (info->record.obj->type == PLANE)
		plane_map(info, &u, &v);
	else if (info->record.obj->type == CYLINDER)
		cylinder_map(info, &u, &v);
	else if (info->record.obj->type == CONE)
		cylinder_map(info, &u, &v);
	u2 = floor(u * 8);
	v2 = floor(v * 8);
	if ((u2 + v2) % 2 == 0)
		info->record.color = vec4(1, 1, 1, 0);
	else
		info->record.color = vec4(0, 0, 0, 0);
}

t_vector	get_normal(t_info *info, int u2, int v2)
{
	t_vector	vec1;
	t_vector	vec2;
	t_vector	normal;
	t_vector	z;
	int			size_line;

	size_line = info->record.obj->bump.size_line;
	vec1 = vec4(1, (get_height(info, size_line / 4 * v2 + u2 + 1) - \
	get_height(info, size_line / 4 * v2 + u2 - 1)) / 2.0, 0, 0);
	vec2 = vec4(0, (get_height(info, size_line / 4 * (v2 + 1) + u2) \
	- get_height(info, size_line / 4 * (v2 - 1) + u2)) / 2.0, 1, 0);
	normal = cross_(&vec2, &vec1);
	z = vec4(0, 0, 1, 0);
	if (dot_(info->record.point, z) < 0)
		normal = cross_(&vec1, &vec2);
	normalize_vector(&normal);
	return (normal);
}

void	convert_normal(t_info *info, t_vector normal)
{
	t_vector	y;
	t_vector	new_axis;
	double		size;
	double		theta;

	y = vec4(0, 1, 0, 0);
	size = sqrt(pow(normal.d[0], 2) + pow(normal.d[1], 2) \
	+ pow(normal.d[2], 2));
	new_axis = cross_(&y, &normal);
	theta = acos(dot_(y, normal) / size);
	cal_normal(info, new_axis, theta);
}

void	bump(t_info *info, t_uv *uv)
{
	t_vector	normal;
	int			u2;
	int			v2;

	if (!uv->init)
		sphere_map(info, &uv->u, &uv->v);
	u2 = (1 - uv->u) * (info->record.obj->bump.width - 1);
	v2 = (1 - uv->v) * (info->record.obj->bump.height - 1);
	normal = get_normal(info, u2, v2);
	convert_normal(info, normal);
}

void	texture(t_info *info, t_uv *uv)
{
	int		u2;
	int		v2;
	int		color;

	if (info->record.obj->type == SPHERE)
		sphere_map(info, &uv->u, &uv->v);
	else if (info->record.obj->type == PLANE)
		plane_map(info, &uv->u, &uv->v);
	else if (info->record.obj->type == CYLINDER)
		cylinder_map(info, &uv->u, &uv->v);
	else if (info->record.obj->type == CONE)
		cylinder_map(info, &uv->u, &uv->v);
	u2 = (1 - uv->u) * (info->record.obj->tex.width - 1);
	v2 = (1 - uv->v) * (info->record.obj->tex.height - 1);
	color = info->record.obj->tex.addr[info->record.obj->tex.size_line \
	/ 4 * v2 + u2];
	info->record.color.d[X] = ((color & 0XFF0000) >> 16) / 255.999;
	info->record.color.d[Y] = ((color & 0X00FF00) >> 8) / 255.999;
	info->record.color.d[Z] = (color & 0X0000FF) / 255.999;
}

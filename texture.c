/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:05:07 by jgoo              #+#    #+#             */
/*   Updated: 2024/04/23 15:14:10 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	checkerboard(t_info *info)
{
	double	u;
	double	v;
	int		u2;
	int		v2;
	if (info->record.type == SPHERE)
		sphere_map(info, &u, &v);
	else if (info->record.type == PLANE)
		plane_map(info, &u, &v);
	else if (info->record.type == CYLINDER)
		cylinder_map(info, &u, &v);
	else
		return ;
	// multiply frequency
	u2 = floor(u);
	v2 = floor(v);
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

	// 높이값 좀 더 나눌수도?
	vec1 = vec4(1, (get_height(info, info->tex.size_line / 4 * v2 + u2 + 1) - \
	get_height(info, info->tex.size_line / 4 * v2 + u2 - 1)) / 2.0, 0, 0);
	vec2 = vec4(0, (get_height(info, info->tex.size_line / 4 * (v2 + 1) + u2) \
	- get_height(info, info->tex.size_line / 4 * (v2 - 1) + u2)) / 2.0, 1, 0);
	normal = cross_(&vec2, &vec1);
	z = vec4(0, 0, 1, 0);
	if (dot_(info->record.point, z) < 0)
		normal = cross_(&vec1, &vec2);
	normalize_vector(&normal);
	return (normal);
}

void	cal_normal(t_info *info, t_vector new_axis, double theta)
{
	double	r[3][3];
	double	k1[3][3];
	double	k2[3][3];
	double	i[3][3];
	t_vector	ret;

	init_k(k1, new_axis);
	init_k(k2, new_axis);
	init_i(i);
	mul_matrix_by_constant(k1, sin(theta));
	mul_matrix(k2, k2, r);
	mul_matrix_by_constant(r, 1 - cos(theta));
	ret = convert(info->record.point, add_matrix(add_matrix(i, k1), r));
	normalize_vector(&ret);
	info->record.n = vec4(ret.d[X], ret.d[Y], ret.d[Z], 0);
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
	u2 = (1 - uv->u) * (info->tex.width - 1);
	v2 = (1 - uv->v) * (info->tex.height - 1);
	normal = get_normal(info, u2, v2);
	convert_normal(info, normal);	
}

void	texture(t_info *info, t_uv *uv)
{
	int		u2;
	int		v2;
	int		color;
	
	if (!uv->init)
		sphere_map(info, &uv->u, &uv->v);
	uv->init = 1;
	u2 = (1 - uv->u) * (info->tex.width - 1);
	v2 = (1 - uv->v) * (info->tex.height - 1);
	color = info->tex.addr[info->tex.size_line / 4 * v2 + u2];
	info->record.color.d[X] = ((color & 0XFF0000) >> 16) / 255.999;
	info->record.color.d[Y] = ((color & 0X00FF00) >> 8) / 255.999;
	info->record.color.d[Z] = (color & 0X0000FF) / 255.999;
}


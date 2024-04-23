/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:48:41 by jgoo              #+#    #+#             */
/*   Updated: 2024/04/23 19:58:55 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	sphere_map(t_info *info, double *u, double *v)
{
	double		theta;
	double		radius;
	double		phi;
	double		raw_u;
	t_sphere	*sp;

	sp = (t_sphere *)info->record.obj->ptr;
	theta = atan2(info->record.point.d[X] - sp->center.d[X], \
	info->record.point.d[Z] - sp->center.d[Z]);
	radius = sp->radius;
	phi = acos((info->record.point.d[Y] - sp->center.d[Y]) / radius);
	raw_u = theta / (2.0 * M_PI);
	*u = 0.5 - raw_u;
	*v = 1 - phi / M_PI;
}

void	plane_map(t_info *info, double *u, double *v)
{
	t_plane	*pl;

	pl = (t_plane *)info->record.obj->ptr;
	if (pl->normal.d[Y] != 0.0)
	{
		*u = fmod(info->record.point.d[X] / 25, 1.0);
		*v = fmod(info->record.point.d[Z] / 25, 1.0);
	}
	else if (pl->normal.d[X] != 0.0)
	{
		*u = fmod(info->record.point.d[Y] / 25, 1.0);
		*v = fmod(info->record.point.d[Z] / 25, 1.0);
	}
	else if (pl->normal.d[Z] != 0.0)
	{
		*u = fmod(info->record.point.d[X] / 25, 1.0);
		*v = fmod(info->record.point.d[Y] / 25, 1.0);
	}
	*u = (*u + 1) / 2.0;
	*v = (*v + 1) / 2.0;
}

void	cylinder_map(t_info *info, double *u, double *v)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)info->record.obj->ptr;
	if (cy->normal.d[Y] != 0.0)
	{
		*u = 0.5 - (atan2(info->record.point.d[X] - cy->center.d[X], \
		info->record.point.d[Z] - cy->center.d[Z]) / (2.0 * M_PI));
		*v = fmod((info->record.point.d[Y] - cy->center.d[Y]) / \
		(cy->height * 2.0), 1.0);
	}
	else if (cy->normal.d[X] != 0.0)
	{
		*u = 0.5 - (atan2(info->record.point.d[Y] - cy->center.d[Y], \
		info->record.point.d[Z] - cy->center.d[Z]) / (2.0 * M_PI));
		*v = fmod((info->record.point.d[X] - cy->center.d[X]) / \
		(cy->height * 2.0), 1.0);
	}
	else if (cy->normal.d[Z] != 0.0)
	{
		*u = 0.5 - (atan2(info->record.point.d[X] - cy->center.d[X], \
		info->record.point.d[Y] - cy->center.d[Y]) / (2.0 * M_PI));
		*v = fmod((info->record.point.d[Z] - cy->center.d[Z]) / \
		(cy->height * 2.0), 1.0);
	}
}

double	get_height(t_info *info, int idx)
{
	int	bump;

	bump = info->record.obj->bump.addr[idx];
	return ((bump & 0XFF0000) >> 16);
}

void	cal_normal(t_info *info, t_vector new_axis, double theta)
{
	double		r[3][3];
	double		k1[3][3];
	double		k2[3][3];
	double		i[3][3];
	t_vector	ret;

	init_k(k1, new_axis);
	init_k(k2, new_axis);
	init_i(i);
	mul_matrix_by_constant(k1, sin(theta));
	mul_matrix(k2, k2, r);
	mul_matrix_by_constant(r, 1 - cos(theta));
	ret = convert(info->record.point, add_matrix(add_matrix(i, k1).d, r).d);
	normalize_vector(&ret);
	info->record.n = vec4(ret.d[X], ret.d[Y], ret.d[Z], 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:48:41 by jgoo              #+#    #+#             */
/*   Updated: 2024/04/23 18:49:42 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	sphere_map(t_info *info, double *u, double *v)
{
	double	theta;
	double	radius;
	double	phi;
	double	raw_u;
	t_sphere	*sp;

	sp = (t_sphere *)info->record.obj->ptr;
	theta = atan2(info->record.point.d[X] - sp->center.d[X], info->record.point.d[Z] - sp->center.d[Z]);
	radius = sp->radius;
	phi = acos((info->record.point.d[Y] - sp->center.d[Y])/ radius);
	raw_u = theta / (2.0 * M_PI);
	*u = 0.5 - raw_u;
	*v = 1 - phi / M_PI;
}

void	plane_map(t_info *info, double *u, double *v)
{
	t_plane	*pl;

	pl = (t_plane *)info->record.obj->ptr;
	// 법선벡터에 따라 가져오는 성분 다르게
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
	double		theta;
	double		raw_u;
	t_cylinder	*cy;

	cy = (t_cylinder *)info->record.obj->ptr;
	theta = 0.0;
	if (cy->normal.d[Y] != 0.0)
	{
		theta = atan2(info->record.point.d[X] - cy->center.d[X], info->record.point.d[Z] - cy->center.d[Z]);
		*v = fmod((info->record.point.d[Y] - cy->center.d[Y]) / (cy->height * 2.0), 1.0);
	}
	else if (cy->normal.d[X] != 0.0)
	{
		theta = atan2(info->record.point.d[Y] - cy->center.d[Y], info->record.point.d[Z] - cy->center.d[Z]);
		*v = fmod((info->record.point.d[X] - cy->center.d[X]) / (cy->height * 2.0), 1.0);
	}
	else if (cy->normal.d[Z] != 0.0)
	{
		theta = atan2(info->record.point.d[X] - cy->center.d[X], info->record.point.d[Y] - cy->center.d[Y]);
		*v = fmod((info->record.point.d[Z] - cy->center.d[Z]) / (cy->height * 2.0), 1.0);
	}
	raw_u = theta / (2.0 * M_PI);
	*u = 0.5 - raw_u;
}

double	get_height(t_info *info, int idx)
{
	int	bump;

	bump = info->record.obj->bump.addr[idx];
	return ((bump & 0XFF0000) >> 16);
}
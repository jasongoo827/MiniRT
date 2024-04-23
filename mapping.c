/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:48:41 by jgoo              #+#    #+#             */
/*   Updated: 2024/04/22 18:48:58 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	sphere_map(t_info *info, double *u, double *v)
{
	double	theta;
	double	radius;
	double	phi;
	double	raw_u;

	theta = atan2(info->record.point.d[X], info->record.point.d[Z]);
	radius = sqrt(pow(info->record.point.d[X], 2) + pow(info->record.point.d[Y], 2) \
	+ pow(info->record.point.d[Z], 2));
	phi = acos(info->record.point.d[Y] / radius);
	raw_u = theta / (2.0 * M_PI);
	*u = 0.5 - raw_u;
	*v = 1 - phi / M_PI;
}

void	plane_map(t_info *info, double *u, double *v)
{
	// 법선벡터에 따라 가져오는 성분 다르게
	*u = fmod(info->record.point.d[X], 1.0);
	*v = fmod(info->record.point.d[Z], 1.0);
}

void	cylinder_map(t_info *info, double *u, double *v)
{
	double	theta;
	double	raw_u;

	theta = atan2(info->record.point.d[X], info->record.point.d[Z]);
	raw_u = theta / (2.0 * M_PI);
	*u = 0.5 - raw_u;
	*v = fmod(info->record.point.d[Y] / 20, 1.0);
}

double	get_height(t_info *info, int idx)
{
	int	bump;

	bump = info->bump.addr[idx];
	return ((bump & 0XFF0000) >> 16);
}
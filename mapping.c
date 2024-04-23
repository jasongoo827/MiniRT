/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:48:41 by jgoo              #+#    #+#             */
/*   Updated: 2024/04/23 15:27:29 by yakim            ###   ########.fr       */
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
	*u = fmod(info->record.point.d[X] / 10, 1.0);
	*v = fmod(info->record.point.d[Z] / 10, 1.0);
	*u = (*u + 1) / 2.0;
	*v = (*v + 1) / 2.0;
	// *u = info->record.point.d[X] / 10;
	// *v = info->record.point.d[Z] / 10;
}

void	cylinder_map(t_info *info, double *u, double *v)
{
	double	theta;
	double	raw_u;

	// 축 방향에 따라 다르게 가져와야 함
	theta = atan2(info->record.point.d[X], info->record.point.d[Z]);
	raw_u = theta / (2.0 * M_PI);
	*u = 0.5 - raw_u;
	// 높이에 비례하게 나눠야 함
	*v = fmod(info->record.point.d[Y] / 20, 1.0);
}

double	get_height(t_info *info, int idx)
{
	int	bump;

	bump = info->record.obj->bump.addr[idx];
	return ((bump & 0XFF0000) >> 16);
}
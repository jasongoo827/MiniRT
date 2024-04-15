/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:46:21 by yakim             #+#    #+#             */
/*   Updated: 2024/04/15 16:14:50 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "essential.h"
#include "object.h"
#include "matrix.h"
#include "light.h"

// int	check_shadow(t_info *info)
// {
// 	t_hit	record;

// 	// if (hit)
// 	// 	return true;
// 	// return false;
// }

t_vector	phong_lightning(t_info *info)
{
	t_vector	color;
	t_vector	lp;
	double		d;
	t_ray		ray;
	t_hit		record_shadow;
	double		t_max;

	// ambient
	color.d[X] = info->record.color.d[X] / 255.999 * (info->ambient.color.d[X] * info->ambient.ratio / 255.999);
	color.d[Y] = info->record.color.d[Y] / 255.999 * (info->ambient.color.d[Y] * info->ambient.ratio / 255.999);
	color.d[Z] = info->record.color.d[Z] / 255.999 * (info->ambient.color.d[Z] * info->ambient.ratio / 255.999);
	
	//shadow_check
	init_record(&record_shadow);
	ray.origin = info->record.point;
	ray.dir = vec_minus(info->light.origin, info->record.point);
	t_max = sqrt(dot(&ray.dir, &ray.dir));
	normalize_vector(&ray.dir);
	ray.origin = vec_plus(ray.origin, vec_scala(ray.dir, 0.001));
	record_shadow = hit_obj(info, ray, record_shadow);
	if (record_shadow.ishit && record_shadow.t < t_max)
		return (color);

	//diffuse
	lp = vec_minus(info->light.origin, info->record.point);
	normalize_vector(&lp);
	d = dot(&lp, &info->record.n);
	if (d < 0)
		d = 0;
	color.d[X] += d * info->light.color.d[X] / 255.999 * info->light.ratio * info->record.color.d[X] / 255.999;
	color.d[Y] += d * info->light.color.d[Y] / 255.999 * info->light.ratio * info->record.color.d[Y] / 255.999;
	color.d[Z] += d * info->light.color.d[Z] / 255.999 * info->light.ratio * info->record.color.d[Z] / 255.999;

	//min, maxing
	if (color.d[X] > 1)
		color.d[X] = 1;
	if (color.d[Y] > 1)
		color.d[Y] = 1;
	if (color.d[Z] > 1)
		color.d[Z] = 1;
	if (color.d[X] < 0)
		color.d[X] = 0;
	if (color.d[Y] < 0)
		color.d[Y] = 0;
	if (color.d[Z] < 0)
		color.d[Z] = 0;
	return (color);
}
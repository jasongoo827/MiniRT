/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:46:21 by yakim             #+#    #+#             */
/*   Updated: 2024/04/12 19:00:42 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "essential.h"
#include "object.h"
#include "matrix.h"
#include "light.h"

t_vector	phong_lightning(t_info *info)
{
	t_vector	color;
	t_vector	lp;
	double		d;

	color.d[X] = info->record.color.d[X] / 255.999 * (info->ambient.color.d[X] * info->ambient.ratio / 255.999);
	color.d[Y] = info->record.color.d[Y] / 255.999 * (info->ambient.color.d[Y] * info->ambient.ratio / 255.999);
	color.d[Z] = info->record.color.d[Z] / 255.999 * (info->ambient.color.d[Z] * info->ambient.ratio / 255.999);

	lp = vec_minus(info->light.origin, info->record.point);
	normalize_vector(&lp);
	d = dot(&lp, &info->record.n);
	if (d < 0)
		d = 0;
	color.d[X] += d * info->light.color.d[X] / 255.999 * info->light.ratio;
	color.d[Y] += d * info->light.color.d[Y] / 255.999 * info->light.ratio;
	color.d[Z] += d * info->light.color.d[Z] / 255.999 * info->light.ratio;
	return (color);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:46:21 by yakim             #+#    #+#             */
/*   Updated: 2024/04/15 11:10:19 by jgoo             ###   ########.fr       */
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

	// check shadow
	
	// if (check_shadow())
		// return black
	color.d[X] = info->record.color.d[X] / 255.999 * (info->ambient.color.d[X] * info->ambient.ratio / 255.999);
	color.d[Y] = info->record.color.d[Y] / 255.999 * (info->ambient.color.d[Y] * info->ambient.ratio / 255.999);
	color.d[Z] = info->record.color.d[Z] / 255.999 * (info->ambient.color.d[Z] * info->ambient.ratio / 255.999);

	lp = vec_minus(info->light.origin, info->record.point);
	normalize_vector(&lp);
	d = dot(&lp, &info->record.n);
	if (d < 0)
		d = 0;
	color.d[X] += d * info->light.color.d[X] / 255.999 * info->light.ratio * info->record.color.d[X] / 255.999;
	color.d[Y] += d * info->light.color.d[Y] / 255.999 * info->light.ratio * info->record.color.d[Y] / 255.999;
	color.d[Z] += d * info->light.color.d[Z] / 255.999 * info->light.ratio * info->record.color.d[Z] / 255.999;
	return (color);
}
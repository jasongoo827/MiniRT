/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:46:21 by yakim             #+#    #+#             */
/*   Updated: 2024/04/15 20:08:38 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "essential.h"
#include "object.h"
#include "matrix.h"
#include "light.h"

void	check_color_bound(t_vector *color)
{
	if (color->d[X] > 1)
		color->d[X] = 1;
	if (color->d[Y] > 1)
		color->d[Y] = 1;
	if (color->d[Z] > 1)
		color->d[Z] = 1;
	if (color->d[X] < 0)
		color->d[X] = 0;
	if (color->d[Y] < 0)
		color->d[Y] = 0;
	if (color->d[Z] < 0)
		color->d[Z] = 0;
}

int	check_shadow(t_info *info)
{
	t_ray		ray;
	t_hit		record_shadow;
	double		t_max;

	init_record(&record_shadow);
	ray.origin = info->record.point;
	ray.dir = vec_minus(info->light.origin, info->record.point);
	t_max = sqrt(dot(&ray.dir, &ray.dir));
	normalize_vector(&ray.dir);
	ray.origin = vec_plus(ray.origin, vec_scala(ray.dir, 0.001));
	record_shadow = hit_obj(info, ray, record_shadow);
	if (record_shadow.ishit && record_shadow.t < t_max)
		return (1);
	return (0);
}

t_vector	diffuse(t_info *info, t_vector *lp)
{
	double		cos;

	cos = dot(lp, &info->record.n);
	if (cos < 0)
		cos = 0;
	return (vec_scala(info->light.color, cos * info->light.ratio));
}

t_vector	specular(t_info *info, t_vector *lp)
{
	t_vector	v;
	t_vector	dot_nv;
	t_vector	reflect;
	double		cos;

	if (BONUS == 0)
		return (vec4(0, 0, 0, 0));
	v = vec_minus(info->camera.origin, info->record.point);
	dot_nv = vec_scala(info->record.n, dot(&v, &info->record.n) * 2);
	reflect = vec_plus(vec_scala(v, -1), dot_nv);
	normalize_vector(&reflect);
	cos = dot(lp, &reflect);
	if (cos < 0)
		cos = 0;
	return (vec_scala(vec_scala(vec_scala(info->light.color, SPECULAR), pow(cos, SHINE)), info->light.ratio));
}

t_vector	phong_lightning(t_info *info)
{
	t_vector	color;
	t_vector	lp;

	// ambient
	color = vec_scala(info->ambient.color, info->ambient.ratio);
	//shadow_check
	if (check_shadow(info))
		return (vec_product(info->record.color, color));
	lp = vec_minus(info->light.origin, info->record.point);
	normalize_vector(&lp);
	//diffuse
	color = vec_plus(color, diffuse(info, &lp));
	//specular
	color = vec_plus(color, specular(info, &lp));
	//min, maxing
	color = vec_product(info->record.color, color);
	check_color_bound(&color);
	return (color);
}

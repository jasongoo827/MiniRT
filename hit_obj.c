/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:38:28 by yakim             #+#    #+#             */
/*   Updated: 2024/04/12 16:51:10 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "essential.h"
#include "object.h"

void	init_record(t_info *info)
{
	info->record.ishit = 0;
	info->record.t = 0;
	info->record.color.d[X] = 0;
	info->record.color.d[Y] = 0;
	info->record.color.d[Z] = 0;
	info->record.color.d[W] = 0;
}


void	hit_obj_sphere(t_info *info, t_ray ray, t_sphere *sphere)
{
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	oc = vec_minus(ray.origin, sphere->center);
	a = dot(&ray.dir, &ray.dir);
	b = dot(&oc, &ray.dir);
	c = dot(&oc, &oc) - pow(sphere->radius, 2);
	discriminant = b * b - a * c;

	if (discriminant >= 0)
	{
		double tempt = (-1 * b - sqrt(discriminant)) / a;
		if (tempt >= 0)
		{
			if (info->record.ishit == 0 || (info->record.ishit && tempt < info->record.t))
			{
				info->record.ishit = 1;
				info->record.t = tempt;
				info->record.point = vec_plus(info->camera.origin, vec_scala(ray.dir, info->record.t));
				info->record.n = vec_minus(info->record.point, sphere->center);
				normalize_vector(&info->record.n);
				info->record.color = sphere->color;
			}
		}
		tempt = (-1 * b + sqrt(discriminant)) / a;
		if (tempt >= 0)
		{
			if (info->record.ishit == 0 || (info->record.ishit && tempt < info->record.t))
			{
				info->record.ishit = 1;
				info->record.t = tempt;
			}
		}
	}
}

void	hit_obj_plane(t_info *info, t_ray ray, t_sphere *sphere)
{
	(void)info;
	(void)ray;
	(void)sphere;
}

void	hit_obj_cylinder(t_info *info, t_ray ray, t_sphere *sphere)
{
	(void)info;
	(void)ray;
	(void)sphere;
}

void	hit_obj(t_info *info, t_ray ray)
{
	int	i;

	i = 0;
	init_record(info);
	while (i < info->objarr->size)
	{
		if (((t_obj *)(info->objarr->arr[i]))->type == SPHERE)
			hit_obj_sphere(info, ray, ((t_obj *)(info->objarr->arr[i]))->ptr);
		// else if (((t_obj *)(info->objarr->arr[i]))->type == PLANE)
		// 	hit_obj_plane(info, ray, ((t_obj *)(info->objarr->arr[i]))->ptr);
		// else if (((t_obj *)(info->objarr->arr[i]))->type == CYLINDER)
		// 	hit_obj_cylinder(info, ray, ((t_obj *)(info->objarr->arr[i]))->ptr);
		i++;
	}
}
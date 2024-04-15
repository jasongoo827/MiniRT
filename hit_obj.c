/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:38:28 by yakim             #+#    #+#             */
/*   Updated: 2024/04/15 16:16:01 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "essential.h"
#include "object.h"

void	init_record(t_hit *record)
{
	record->ishit = 0;
	record->t = 0;
	record->color.d[X] = 0;
	record->color.d[Y] = 0;
	record->color.d[Z] = 0;
	record->color.d[W] = 0;
}


void	hit_obj_sphere(t_info *info, t_ray ray, t_hit *record, t_sphere *sphere)
{
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	(void)info;
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
			if (record->ishit == 0 || (record->ishit && tempt < record->t))
			{
				record->ishit = 1;
				record->t = tempt;
				record->point = vec_plus(ray.origin, vec_scala(ray.dir, record->t));
				record->n = vec_minus(record->point, sphere->center);
				normalize_vector(&record->n);
				if (dot(&record->n, &ray.dir) > 0)
					record->n = vec_scala(record->n, -1);
				record->color = sphere->color;
			}
		}
		tempt = (-1 * b + sqrt(discriminant)) / a;
		if (tempt >= 0)
		{
			if (record->ishit == 0 || (record->ishit && tempt < record->t))
			{
				record->ishit = 1;
				record->t = tempt;
				record->point = vec_plus(ray.origin, vec_scala(ray.dir, record->t));
				record->n = vec_minus(record->point, sphere->center);
				normalize_vector(&record->n);
				if (dot(&record->n, &ray.dir) > 0)
					record->n = vec_scala(record->n, -1);
				record->color = sphere->color;
			}
		}
	}
}

void	hit_obj_plane(t_info *info, t_ray ray, t_hit *record, t_plane *plane)
{
	double		tempt;
	double		divider;
	t_vector	oc;

	(void)info;
	divider = dot(&ray.dir, &plane->normal);
	if (divider == 0)
		return ;
	oc = vec_minus(plane->point, ray.origin);
	tempt = dot(&oc, &plane->normal) / divider;
	if (tempt >= 0)
	{
		if (record->ishit == 0 || (record->ishit && tempt < record->t))
		{
			record->ishit = 1;
			record->t = tempt;
			record->point = vec_plus(ray.origin, vec_scala(ray.dir, record->t));
			record->n = plane->normal;
			if (dot(&record->n, &ray.dir) > 0)
				record->n = vec_scala(record->n, -1);
			record->color = plane->color;
		}
	}
}

void	hit_obj_cylinder(t_info *info, t_ray ray, t_hit *record, t_sphere *sphere)
{
	(void)info;
	(void)ray;
	(void)sphere;
	(void)record;
}

t_hit	hit_obj(t_info *info, t_ray ray, t_hit record)
{
	int		i;

	i = 0;
	init_record(&record);
	while (i < info->objarr->size)
	{
		if (((t_obj *)(info->objarr->arr[i]))->type == SPHERE)
			hit_obj_sphere(info, ray, &record, ((t_obj *)(info->objarr->arr[i]))->ptr);
		else if (((t_obj *)(info->objarr->arr[i]))->type == PLANE)
			hit_obj_plane(info, ray, &record, ((t_obj *)(info->objarr->arr[i]))->ptr);
		// else if (((t_obj *)(info->objarr->arr[i]))->type == CYLINDER)
		// 	hit_obj_cylinder(info, ray, ((t_obj *)(info->objarr->arr[i]))->ptr);
		i++;
	}
	return (record);
}
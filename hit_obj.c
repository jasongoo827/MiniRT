/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:38:28 by yakim             #+#    #+#             */
/*   Updated: 2024/04/16 19:11:40 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "essential.h"
#include "object.h"

void	init_record(t_hit *rec)
{
	rec->ishit = 0;
	rec->t = 0;
	rec->color.d[X] = 0;
	rec->color.d[Y] = 0;
	rec->color.d[Z] = 0;
	rec->color.d[W] = 0;
}

void	hit_obj_sphere(t_ray ray, t_hit *rec, t_sphere *sp)
{
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	oc = vec_minus(ray.origin, sp->center);
	a = dot(&ray.dir, &ray.dir);
	b = dot(&oc, &ray.dir);
	c = dot(&oc, &oc) - pow(sp->radius, 2);
	discriminant = b * b - a * c;
	if (discriminant >= 0)
	{
		double tempt = (-1 * b - sqrt(discriminant)) / a;
		if (tempt >= 0)
		{
			if (rec->ishit == 0 || (rec->ishit && tempt < rec->t))
			{
				rec->ishit = 1;
				rec->t = tempt;
				rec->point = vec_plus(ray.origin, vec_scala(ray.dir, rec->t));
				rec->n = vec_minus(rec->point, sp->center);
				normalize_vector(&rec->n);
				if (dot(&rec->n, &ray.dir) > 0)
					rec->n = vec_scala(rec->n, -1);
				rec->color = sp->color;
			}
		}
		tempt = (-1 * b + sqrt(discriminant)) / a;
		if (tempt >= 0)
		{
			if (rec->ishit == 0 || (rec->ishit && tempt < rec->t))
			{
				rec->ishit = 1;
				rec->t = tempt;
				rec->point = vec_plus(ray.origin, vec_scala(ray.dir, rec->t));
				rec->n = vec_minus(rec->point, sp->center);
				normalize_vector(&rec->n);
				if (dot(&rec->n, &ray.dir) > 0)
					rec->n = vec_scala(rec->n, -1);
				rec->color = sp->color;
			}
		}
	}
}

void	hit_obj_plane(t_ray ray, t_hit *rec, t_plane *plane)
{
	double		tempt;
	double		divider;
	t_vector	oc;

	divider = dot(&ray.dir, &plane->normal);
	if (divider == 0)
		return ;
	oc = vec_minus(plane->point, ray.origin);
	tempt = dot(&oc, &plane->normal) / divider;
	if (tempt >= 0)
	{
		if (rec->ishit == 0 || (rec->ishit && tempt < rec->t))
		{
			rec->ishit = 1;
			rec->t = tempt;
			rec->point = vec_plus(ray.origin, vec_scala(ray.dir, rec->t));
			rec->n = plane->normal;
			if (dot(&rec->n, &ray.dir) > 0)
				rec->n = vec_scala(rec->n, -1);
			rec->color = plane->color;
		}
	}
}

t_hit	hit_obj(t_info *info, t_ray ray, t_hit rec)
{
	int		i;

	i = 0;
	init_record(&rec);
	while (i < info->objarr->size)
	{
		if (((t_obj *)(info->objarr->arr[i]))->type == SPHERE)
			hit_obj_sphere(ray, &rec, ((t_obj *)(info->objarr->arr[i]))->ptr);
		else if (((t_obj *)(info->objarr->arr[i]))->type == PLANE)
			hit_obj_plane(ray, &rec, ((t_obj *)(info->objarr->arr[i]))->ptr);
		else if (((t_obj *)(info->objarr->arr[i]))->type == CYLINDER)
			hit_obj_cylinder(ray, &rec, ((t_obj *)(info->objarr->arr[i]))->ptr);
		i++;
	}
	return (rec);
}

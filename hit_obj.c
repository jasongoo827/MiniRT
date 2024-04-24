/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:38:28 by yakim             #+#    #+#             */
/*   Updated: 2024/04/24 16:07:28 by yakim            ###   ########.fr       */
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

void	hit_obj_sphere(t_ray ray, t_hit *rec, t_sphere *sp, t_obj *obj)
{
	t_vector	oc;
	t_dscrmnt	d;

	oc = vec_minus(ray.origin, sp->center);
	if (dscrmnt_sp(&d, &ray, sp, &oc) == 1)
	{
		if ((rec->ishit == 0 || (rec->ishit && d.root < rec->t)))
		{
			rec->ishit = 1;
			rec->t = d.root;
			rec->point = vec_plus(ray.origin, vec_scala(ray.dir, rec->t));
			rec->n = vec_minus(rec->point, sp->center);
			normalize_vector(&rec->n);
			if (dot(&rec->n, &ray.dir) > 0)
				rec->n = vec_scala(rec->n, -1);
			rec->color = sp->color;
			rec->type = SPHERE;
			rec->obj = obj;
		}
	}
}

void	hit_obj_plane(t_ray ray, t_hit *rec, t_plane *plane, t_obj *obj)
{
	double		tempt;
	double		divider;
	t_vector	oc;

	divider = dot(&ray.dir, &plane->normal);
	if (divider == 0)
		return ;
	oc = vec_minus(plane->point, ray.origin);
	tempt = dot(&oc, &plane->normal) / divider;
	if (tempt > 0)
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
			rec->type = PLANE;
			rec->obj = obj;
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
			hit_obj_sphere(ray, &rec, ((t_obj *)(info->objarr->arr[i]))->ptr, \
			info->objarr->arr[i]);
		else if (((t_obj *)(info->objarr->arr[i]))->type == PLANE)
			hit_obj_plane(ray, &rec, ((t_obj *)(info->objarr->arr[i]))->ptr, \
			info->objarr->arr[i]);
		else if (((t_obj *)(info->objarr->arr[i]))->type == CYLINDER)
			hit_obj_cylinder(ray, &rec, ((t_obj *)(info->objarr->arr[i]))->ptr, \
			info->objarr->arr[i]);
		else if (((t_obj *)(info->objarr->arr[i]))->type == CONE)
			hit_obj_cone(ray, &rec, ((t_obj *)(info->objarr->arr[i]))->ptr, \
			info->objarr->arr[i]);
		i++;
	}
	return (rec);
}

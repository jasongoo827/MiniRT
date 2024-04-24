/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj_cy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:23:48 by yakim             #+#    #+#             */
/*   Updated: 2024/04/24 15:58:17 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "essential.h"
#include "object.h"

double	cy_get_height(t_ray *ray, double t, t_cylinder *cy)
{
	t_vector	point;

	point = vec_plus(ray->origin, vec_scala(ray->dir, t));
	return (dot_(vec_minus(point, cy->center), cy->normal));
}

t_vector	cy_get_normal(t_vector p, double height, t_cylinder *cy)
{
	t_vector	normal;
	t_vector	hit_center;

	hit_center = vec_plus(cy->center, vec_scala(cy->normal, height));
	normal = vec_minus(p, hit_center);
	normalize_vector(&normal);
	return (normal);
}

void	hit_obj_cylinder_down(t_ray ray, t_hit *rec, t_cylinder *cy, t_obj *obj)
{
	t_vector	cap;
	t_dscrmnt	d;

	cap = vec_minus(cy->center, vec_scala(cy->normal, cy->height / 2));
	if (dscrmnt_cy_cap(&d, &ray, cy, &cap) == 1)
	{
		if (rec->ishit == 0 || (rec->ishit && d.root < rec->t))
		{
			rec->ishit = 1;
			rec->t = d.root;
			rec->point = vec_plus(ray.origin, vec_scala(ray.dir, d.root));
			rec->n = cy->normal;
			if (dot(&rec->n, &ray.dir) > 0)
				rec->n = vec_scala(rec->n, -1);
			rec->color = cy->color;
			rec->type = CYLINDER;
			rec->obj = obj;
		}
	}
}

void	hit_obj_cylinder_up(t_ray ray, t_hit *rec, t_cylinder *cy, t_obj *obj)
{
	t_vector	cap;
	t_dscrmnt	d;

	cap = vec_plus(cy->center, vec_scala(cy->normal, cy->height / 2));
	if (dscrmnt_cy_cap(&d, &ray, cy, &cap) == 1)
	{
		if (rec->ishit == 0 || (rec->ishit && d.root < rec->t))
		{
			rec->ishit = 1;
			rec->t = d.root;
			rec->point = vec_plus(ray.origin, vec_scala(ray.dir, d.root));
			rec->n = cy->normal;
			if (dot(&rec->n, &ray.dir) > 0)
				rec->n = vec_scala(rec->n, -1);
			rec->color = cy->color;
			rec->type = CYLINDER;
			rec->obj = obj;
		}
	}
}

void	hit_obj_cylinder(t_ray ray, t_hit *rec, t_cylinder *cy, t_obj *obj)
{
	t_vector	oc;
	t_dscrmnt	d;

	oc = vec_minus(ray.origin, cy->center);
	if (dscrmnt_cy(&d, &ray, cy, &oc) == 1)
	{
		if ((rec->ishit == 0 || (rec->ishit && d.root < rec->t)))
		{
			rec->ishit = 1;
			rec->t = d.root;
			rec->point = vec_plus(ray.origin, vec_scala(ray.dir, rec->t));
			rec->n = cy_get_normal(rec->point, d.height, cy);
			if (dot(&rec->n, &ray.dir) > 0)
				rec->n = vec_scala(rec->n, -1);
			rec->color = cy->color;
			rec->type = CYLINDER;
			rec->obj = obj;
		}
	}
	hit_obj_cylinder_up(ray, rec, cy, obj);
	hit_obj_cylinder_down(ray, rec, cy, obj);
}

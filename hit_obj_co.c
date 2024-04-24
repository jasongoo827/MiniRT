/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj_co.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:25:11 by yakim             #+#    #+#             */
/*   Updated: 2024/04/24 13:29:43 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "essential.h"
#include "object.h"

double	co_get_height(t_ray *ray, double t, t_cone *co)
{
	t_vector	point;

	point = vec_plus(ray->origin, vec_scala(ray->dir, t));
	return (dot_(vec_minus(point, co->center), co->normal));
}

t_vector	co_get_normal(t_vector p, t_cone *co)
{
	t_vector	normal;
	t_vector	cp;

	cp = vec_minus(p, co->center);
	normal = vec_plus(cp, vec_scala(co->normal, -2 * dot(&co->normal, &cp)));
	normalize_vector(&normal);
	return (normal);
}

void	hit_obj_cone_cap(t_ray ray, t_hit *rec, t_cone *co, t_obj *obj)
{
	double		tempt;
	double		divider;
	t_vector	oc;
	t_vector	cap;
	t_vector	point;

	divider = dot(&ray.dir, &co->normal);
	if (divider == 0)
		return ;
	cap = vec_plus(co->center, vec_scala(co->normal, co->height));
	oc = vec_minus(cap, ray.origin);
	tempt = dot(&oc, &co->normal) / divider;
	if (tempt > 0)
	{
		point = vec_plus(ray.origin, vec_scala(ray.dir, tempt));
		if (vec_length2(vec_minus(point, cap)) <= pow(co->height, 2) && \
		(rec->ishit == 0 || (rec->ishit && tempt < rec->t)))
		{
			rec->ishit = 1;
			rec->t = tempt;
			rec->point = point;
			rec->n = co->normal;
			if (dot(&rec->n, &ray.dir) > 0)
				rec->n = vec_scala(rec->n, -1);
			rec->color = co->color;
			rec->type = CONE;
			rec->obj = obj;
		}
	}
}

void	hit_obj_cone(t_ray ray, t_hit *rec, t_cone *co, t_obj *obj)
{
	t_vector	oc;
	t_dscrmnt	d;

	oc = vec_minus(ray.origin, co->center);
	if (dscrmnt_co(&d, &ray, co, &oc) == 1)
	{
		if ((rec->ishit == 0 || (rec->ishit && d.root < rec->t)))
		{
			rec->ishit = 1;
			rec->t = d.root;
			rec->point = vec_plus(ray.origin, vec_scala(ray.dir, rec->t));
			rec->n = co_get_normal(rec->point, co);
			if (dot(&rec->n, &ray.dir) > 0)
				rec->n = vec_scala(rec->n, -1);
			rec->color = co->color;
			rec->type = CONE;
			rec->obj = obj;
		}
	}
	hit_obj_cone_cap(ray, rec, co, obj);
}

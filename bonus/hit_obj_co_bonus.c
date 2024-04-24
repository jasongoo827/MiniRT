/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj_co_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:25:11 by yakim             #+#    #+#             */
/*   Updated: 2024/04/24 16:18:56 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "essential_bonus.h"
#include "object_bonus.h"

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
	t_vector	cap;
	t_dscrmnt	d;

	cap = vec_plus(co->center, vec_scala(co->normal, co->height));
	if (dscrmnt_co_cap(&d, &ray, co, &cap) == 1)
	{
		if (rec->ishit == 0 || (rec->ishit && d.root < rec->t))
		{
			rec->ishit = 1;
			rec->t = d.root;
			rec->point = vec_plus(ray.origin, vec_scala(ray.dir, d.root));
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

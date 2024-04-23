/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj_co.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:25:11 by yakim             #+#    #+#             */
/*   Updated: 2024/04/23 15:08:56 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "essential.h"
#include "object.h"

double	co_get_height(t_ray ray, double t, t_cone *co)
{
	t_vector	point;

	point = vec_plus(ray.origin, vec_scala(ray.dir, t));
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
void	hit_obj_cone_sp(t_ray ray, t_hit *rec, t_cone *co, t_obj *obj)
{
	double		tempt;
	double		divider;
	t_vector	oc;
	t_vector	cap;

	divider = dot(&ray.dir, &co->normal);
	if (divider == 0)
		return ;
	cap = vec_plus(co->center, vec_scala(co->normal, co->height));
	oc = vec_minus(cap, ray.origin);
	tempt = dot(&oc, &co->normal) / divider;
	if (tempt >= 0)
	{
		t_vector point = vec_plus(ray.origin, vec_scala(ray.dir, tempt));
		if (vec_length2(vec_minus(point, cap)) <= pow(co->height, 2) && (rec->ishit == 0 || (rec->ishit && tempt < rec->t)))
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
	double		a;
	double		b;
	double		c;
	double		discriminant;

	oc = vec_minus(ray.origin, co->center);
	a = dot(&ray.dir, &ray.dir) - 2 * pow(dot(&ray.dir, &co->normal), 2);
	b = dot(&ray.dir, &oc) - 2 * dot(&ray.dir, &co->normal) * dot(&oc, &co->normal);
	c = dot(&oc, &oc) - 2 * pow(dot(&oc, &co->normal), 2);
	discriminant = b * b - a * c;
	if (discriminant >= 0)
	{
		double tempt = (-1 * b - sqrt(discriminant)) / a;
		if (tempt >= 0)
		{
			double height = co_get_height(ray, tempt, co);
			if (height <= co->height && height >= 0 && (rec->ishit == 0 || (rec->ishit && tempt < rec->t)))
			{
				rec->ishit = 1;
				rec->t = tempt;
				rec->point = vec_plus(ray.origin, vec_scala(ray.dir, rec->t));
				rec->n = co_get_normal(rec->point, co);
				if (dot(&rec->n, &ray.dir) > 0)
					rec->n = vec_scala(rec->n, -1);
				rec->color = co->color;
				rec->type = CONE;
				rec->obj = obj;
			}
		}
		tempt = (-1 * b + sqrt(discriminant)) / a;
		if (tempt >= 0)
		{
			double height = co_get_height(ray, tempt, co);
			if (height <= co->height && height >= 0 && (rec->ishit == 0 || (rec->ishit && tempt < rec->t)))
			{
				rec->ishit = 1;
				rec->t = tempt;
				rec->point = vec_plus(ray.origin, vec_scala(ray.dir, rec->t));
				rec->n = co_get_normal(rec->point, co);
				if (dot(&rec->n, &ray.dir) > 0)
					rec->n = vec_scala(rec->n, -1);
				rec->color = co->color;
				rec->type = CONE;
				rec->obj = obj;
			}
		}
	}
	hit_obj_cone_sp(ray, rec, co, obj);
}
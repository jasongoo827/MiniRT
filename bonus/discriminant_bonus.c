/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   discriminant_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:46:58 by yakim             #+#    #+#             */
/*   Updated: 2024/04/24 14:27:26 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_bonus.h"

int	dscrmnt_sp(t_dscrmnt *d, t_ray *ray, t_sphere *sp, t_vector *oc)
{
	d->a = dot(&ray->dir, &ray->dir);
	d->b = dot(oc, &ray->dir);
	d->c = dot(oc, oc) - pow(sp->radius, 2);
	d->dscrmnt = d->b * d->b - d->a * d->c;
	if (d->dscrmnt < 0)
		return (0);
	d->root = (-1 * d->b - sqrt(d->dscrmnt)) / d->a;
	if (d->root > 0)
		return (1);
	d->root = (-1 * d->b + sqrt(d->dscrmnt)) / d->a;
	if (d->root > 0)
		return (1);
	return (0);
}

int	dscrmnt_cy(t_dscrmnt *d, t_ray *ray, t_cylinder *cy, t_vector *oc)
{
	d->a = vec_length2(cross_(&ray->dir, &cy->normal));
	d->b = dot_(cross_(&ray->dir, &cy->normal), cross_(oc, &cy->normal));
	d->c = vec_length2(cross_(oc, &cy->normal)) - pow(cy->diameter, 2);
	d->dscrmnt = d->b * d->b - d->a * d->c;
	if (d->dscrmnt < 0)
		return (0);
	d->root = (-1 * d->b - sqrt(d->dscrmnt)) / d->a;
	if (d->root > 0)
	{
		d->height = cy_get_height(ray, d->root, cy);
		if (fabs(d->height) <= cy->height / 2)
			return (1);
	}
	d->root = (-1 * d->b + sqrt(d->dscrmnt)) / d->a;
	if (d->root > 0)
	{
		d->height = cy_get_height(ray, d->root, cy);
		if (fabs(d->height) <= cy->height / 2)
			return (1);
	}
	return (0);
}

int	dscrmnt_co(t_dscrmnt *d, t_ray *ray, t_cone *co, t_vector *oc)
{
	d->a = dot(&ray->dir, &ray->dir) - 2 * pow(dot(&ray->dir, &co->normal), 2);
	d->b = dot(&ray->dir, oc) - 2 * dot(&ray->dir, &co->normal) \
	* dot(oc, &co->normal);
	d->c = dot(oc, oc) - 2 * pow(dot(oc, &co->normal), 2);
	d->dscrmnt = d->b * d->b - d->a * d->c;
	if (d->dscrmnt < 0)
		return (0);
	d->root = (-1 * d->b - sqrt(d->dscrmnt)) / d->a;
	if (d->root > 0)
	{
		d->height = co_get_height(ray, d->root, co);
		if (d->height <= co->height && d->height >= 0)
			return (1);
	}
	d->root = (-1 * d->b + sqrt(d->dscrmnt)) / d->a;
	if (d->root > 0)
	{
		d->height = co_get_height(ray, d->root, co);
		if (d->height <= co->height && d->height >= 0)
			return (1);
	}
	return (0);
}

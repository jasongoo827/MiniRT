/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:19:52 by jgoo              #+#    #+#             */
/*   Updated: 2024/04/23 19:24:54 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_vector	vec4(double x, double y, double z, double w)
{
	t_vector	vector;

	vector.d[X] = x;
	vector.d[Y] = y;
	vector.d[Z] = z;
	vector.d[W] = w;
	return (vector);
}

void	cross(t_vector *ret, t_vector *v1, t_vector *v2)
{
	ret->d[X] = v1->d[Y] * v2->d[Z] - v1->d[Z] * v2->d[Y];
	ret->d[Y] = v1->d[Z] * v2->d[X] - v1->d[X] * v2->d[Z];
	ret->d[Z] = v1->d[X] * v2->d[Y] - v1->d[Y] * v2->d[X];
}

t_vector	cross_(t_vector *v1, t_vector *v2)
{
	t_vector	ret;

	ret.d[X] = v1->d[Y] * v2->d[Z] - v1->d[Z] * v2->d[Y];
	ret.d[Y] = v1->d[Z] * v2->d[X] - v1->d[X] * v2->d[Z];
	ret.d[Z] = v1->d[X] * v2->d[Y] - v1->d[Y] * v2->d[X];
	return (ret);
}

double	dot(t_vector *v1, t_vector *v2)
{
	double		x;
	double		y;
	double		z;

	x = v1->d[X] * v2->d[X];
	y = v1->d[Y] * v2->d[Y];
	z = v1->d[Z] * v2->d[Z];
	return (x + y + z);
}

double	dot_(t_vector v1, t_vector v2)
{
	double		x;
	double		y;
	double		z;

	x = v1.d[X] * v2.d[X];
	y = v1.d[Y] * v2.d[Y];
	z = v1.d[Z] * v2.d[Z];
	return (x + y + z);
}

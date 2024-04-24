/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vector2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:25:39 by jgoo              #+#    #+#             */
/*   Updated: 2024/04/24 14:29:54 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_bonus.h"

t_vector	vec_minus(t_vector v1, t_vector v2)
{
	t_vector	ret;

	ret.d[X] = v1.d[X] - v2.d[X];
	ret.d[Y] = v1.d[Y] - v2.d[Y];
	ret.d[Z] = v1.d[Z] - v2.d[Z];
	return (ret);
}

t_vector	vec_plus(t_vector v1, t_vector v2)
{
	t_vector	ret;

	ret.d[X] = v1.d[X] + v2.d[X];
	ret.d[Y] = v1.d[Y] + v2.d[Y];
	ret.d[Z] = v1.d[Z] + v2.d[Z];
	return (ret);
}

t_vector	vec_scala(t_vector v, double scala)
{
	t_vector	ret;

	ret.d[X] = v.d[X] * scala;
	ret.d[Y] = v.d[Y] * scala;
	ret.d[Z] = v.d[Z] * scala;
	return (ret);
}

t_vector	vec_product(t_vector v1, t_vector v2)
{
	t_vector	ret;

	ret.d[X] = v1.d[X] * v2.d[X];
	ret.d[Y] = v1.d[Y] * v2.d[Y];
	ret.d[Z] = v1.d[Z] * v2.d[Z];
	return (ret);
}

double	vec_length2(t_vector v)
{
	double	ret;

	ret = pow(v.d[X], 2) + pow(v.d[Y], 2) + pow(v.d[Z], 2);
	return (ret);
}

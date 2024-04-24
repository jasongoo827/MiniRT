/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vector3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:24:27 by jgoo              #+#    #+#             */
/*   Updated: 2024/04/24 19:10:17 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_bonus.h"

void	normalize_vector(t_vector *vector)
{
	double	size;

	size = sqrt(pow(vector->d[0], 2) + pow(vector->d[1], 2) \
	+ pow(vector->d[2], 2));
	vector->d[0] /= size;
	vector->d[1] /= size;
	vector->d[2] /= size;
}

int	cmp_vec(t_vector v1, t_vector v2)
{
	if (fabs(v1.d[X]) != fabs(v2.d[X]))
		return (0);
	if (fabs(v1.d[Y]) != fabs(v2.d[Y]))
		return (0);
	if (fabs(v1.d[Z]) != fabs(v2.d[Z]))
		return (0);
	return (1);
}

void	init_k(double k[3][3], t_vector new_axis)
{
	k[0][0] = 0;
	k[0][1] = -new_axis.d[Z];
	k[0][2] = new_axis.d[Y];
	k[1][0] = new_axis.d[Z];
	k[1][1] = 0;
	k[1][2] = -new_axis.d[X];
	k[2][0] = -new_axis.d[Y];
	k[2][1] = new_axis.d[X];
	k[2][2] = 0;
}

void	init_i(double i[3][3])
{
	i[0][0] = 1;
	i[0][1] = 0;
	i[0][2] = 0;
	i[1][0] = 0;
	i[1][1] = 1;
	i[1][2] = 0;
	i[2][0] = 0;
	i[2][1] = 0;
	i[2][2] = 1;
}

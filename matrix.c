/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:26:43 by jgoo              #+#    #+#             */
/*   Updated: 2024/04/23 19:50:18 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

void	mul_matrix(double a[][3], double b[][3], double result[][3])
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			result[i][j] = 0;
			k = -1;
			while (++k < 3)
				result[i][j] += a[i][k] * b[k][j];
		}
	}
}

void	mul_matrix_by_constant(double matrix[][3], double constant)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			matrix[i][j] *= constant;
	}
}

t_matrix	add_matrix(double matrix1[][3], double matrix2[][3])
{
	int				i;
	int				j;
	t_matrix		matrix;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			matrix.d[i][j] = matrix1[i][j] + matrix2[i][j];
	}
	return (matrix);
}

t_vector	convert(t_vector point, double mat[][3])
{
	t_vector	vec;
	int			i;
	int			j;

	i = -1;
	while (++i < 3)
	{
		vec.d[i] = 0;
		j = -1;
		while (++j < 3)
			vec.d[i] += mat[i][j] * point.d[j];
	}
	vec.d[W] = 0;
	return (vec);
}

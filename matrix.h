/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:22:31 by yakim             #+#    #+#             */
/*   Updated: 2024/04/22 19:46:49 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "essential.h"
# include "error.h"

typedef	struct s_matrix
{
	double	d[4][4];
}	t_matrix;

typedef	struct s_vector
{
	double	d[4];
}	t_vector;

enum e_xyzw
{
	X = 0,
	Y,
	Z,
	W
};

# include "object.h"
typedef	struct s_camera	t_camera;

// matrix.c
t_matrix	*alloc_matrix(void);
t_matrix	*init_look_at_matrix(t_vector *eye_position, t_vector *r0, \
t_vector *r1, t_vector *r2);
void		get_axis(t_camera *camera);
void		mul_matrix(double a[][3], double b[][3], double result[][3]);
void		mul_matrix_by_constant(double matrix[3][3], double constant);
double 		(*add_matrix(double matrix1[][3], double matrix2[][3]))[3];
t_vector 	convert(t_vector point, double mat[][3]);
void		init_k(double k[3][3], t_vector new_axis);
void		init_i(double i[3][3]);

// math_vector.c
t_vector	*alloc_vector(double x, double y, double z, double w);
t_vector	vec4(double x, double y, double z, double w);
void		cross(t_vector *ret, t_vector *v1, t_vector *v2);
t_vector	cross_(t_vector *v1, t_vector *v2);
double		dot(t_vector *v1, t_vector *v2);
double		dot_(t_vector v1, t_vector v2);
void		normalize_vector(t_vector *vector);
int			cmp_vec(t_vector v1, t_vector v2);

// math_vector2.c
t_vector	vec_minus(t_vector v1, t_vector v2);
t_vector	vec_plus(t_vector v1, t_vector v2);
t_vector	vec_scala(t_vector v, double scala);
t_vector	vec_product(t_vector v1, t_vector v2);
double		vec_length2(t_vector v);

#endif

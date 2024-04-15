/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:22:31 by yakim             #+#    #+#             */
/*   Updated: 2024/04/15 20:15:30 by jgoo             ###   ########.fr       */
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

// math_vector.c
t_vector	*alloc_vector(double x, double y, double z, double w);
t_vector	vec4(double x, double y, double z, double w);
void		cross(t_vector *ret, t_vector *v1, t_vector *v2);
double		dot(t_vector *v1, t_vector *v2);
void		normalize_vector(t_vector *vector);
int			cmp_vec(t_vector v1, t_vector v2);

// math_vector2.c
t_vector	vec_minus(t_vector v1, t_vector v2);
t_vector	vec_plus(t_vector v1, t_vector v2);
t_vector	vec_scala(t_vector v, double scala);
t_vector	vec_product(t_vector v1, t_vector v2);

#endif

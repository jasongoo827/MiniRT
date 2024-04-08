/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:22:31 by yakim             #+#    #+#             */
/*   Updated: 2024/04/03 17:01:55 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "essential.h"

typedef	struct s_matrix
{
	double	d[4][4];
}	t_matrix;

typedef	struct s_vector
{
	double	d[4];
}	t_vector;

// 시야 행렬
// typedef struct s_look_at_matrix
// {
// 	// eye position
// 	t_vector *eye_position;
// 	// focus position
// 	t_vector *focus_position;
// 	// Up Direction
// 	t_vector *up_direction;
// 	// look_at_matrix
// }	t_look_at_matrix;


enum e_xyzw
{
	X = 0,
	Y,
	Z,
	W
};

// matrix.c
t_matrix	*alloc_matrix(void);
t_vector	*alloc_vector(double x, double y, double z, double w);
t_matrix	*init_look_at_matrix(t_vector *eye_position, t_vector *r0, \
t_vector *r1, t_vector *r2);
t_matrix	*get_look_at_matrix(t_vector *camera);

// matrix_math.c
void		cross(t_vector *ret, t_vector *v1, t_vector *v2);
double		dot(t_vector *v1, t_vector *v2);
void		normalize_vector(t_vector *vector);


#endif

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

# include "minirt.h"

typedef	struct s_matrix
{
	double	d[4][4];
}	t_matrix;

typedef	struct s_vector
{
	double	d[4];
}	t_vector;

// 시야 행렬
typedef struct s_look_at_matrix
{
	// eye position
	struct s_vector *eye_position;
	// focus position
	struct s_vector *focus_position;
	// Up Direction
	struct s_vector *up_direction;
}	t_look_at_matrix;

// 외적
void	cross(t_vector *v1, t_vector *v2);
// 내적
void	dot(t_vector *v1, t_vector *v2);
// normalize
void	normalize_vector(t_vector *vector);

#endif

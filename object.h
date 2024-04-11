/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:54:50 by yakim             #+#    #+#             */
/*   Updated: 2024/04/11 14:56:23 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "data_struct.h"
# include "matrix.h"

typedef struct s_darray t_darray;

typedef enum e_type
{
	CAMERA = 0,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}	t_type;

typedef struct s_vector t_vector;

typedef struct s_camera
{
	t_vector	origin;
	t_vector	dir;
	double		fov;
	t_vector	horizontal;
	t_vector	vertical;
}	t_camera;

typedef struct s_light
{
	t_vector	origin;
	double		ratio;
	t_vector	color;
}	t_light;

typedef struct s_ambient
{
	double		ratio;
	t_vector	color;
}	t_ambient;

typedef struct s_obj
{
	t_type	type;
	void	*ptr;
}	t_obj;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	dir;
}	t_ray;

typedef struct s_sphere
{
	t_vector	center;
	double		radius;
	t_vector	color;
}	t_sphere;

typedef struct s_plane
{
	t_vector	point;
	t_vector	normal;
	t_vector	color;
}	t_plane;

typedef struct s_cylinder
{
	t_vector	center;
	t_vector	normal;
	double		diameter;
	double		height;
	t_vector	color;
}	t_cylinder;

typedef struct s_info
{
	void		*mlx;
	void		*win;
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_darray	*objarr;
}	t_info;

t_obj	*init_obj(t_type type);

#endif

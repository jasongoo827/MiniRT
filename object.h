/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:54:50 by yakim             #+#    #+#             */
/*   Updated: 2024/04/08 20:20:23 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "matrix.h"

typedef enum e_type
{
	CAMERA = 0,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}	t_type;

typedef struct s_obj
{
	t_type	type;
	void	*ptr;
}	t_obj;

typedef struct s_camera
{
	t_vector	origin;
	t_vector	dir;
	t_vector	horizontal;
	t_vector	vertical;
}	t_camera;

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

t_camera	camera(t_vector origin, t_vector dir, double fov);
t_ray		ray(t_vector origin, t_vector dir);
t_sphere	sphere(t_vector center, double radius, t_vector color);
t_plane		plane(t_vector point, t_vector normal, t_vector color);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:54:50 by yakim             #+#    #+#             */
/*   Updated: 2024/04/03 17:11:41 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"

typedef struct s_obj
{
	char	type;
	void	*ptr;
}	t_obj;

typedef struct s_camera
{
	t_point3	origin;
	t_vec3		dir;
	t_vec3		horizontal;
	t_vec3		vertical;
}	t_camera;

typedef struct s_ray
{
	t_point3	origin;
	t_vec3		dir;
}	t_ray;

typedef struct s_sphere
{
	t_point3	center;
	double		radius;
	t_color3	color;
}	t_sphere;

typedef struct s_plane
{
	t_point3	point;
	t_vec3		normal;
	t_color3	color;
}	t_plane;

t_camera	camera(t_point3 origin, t_vec3 dir, double fov);
t_ray		ray(t_point3 origin, t_vec3 dir);
t_sphere	sphere(t_point3 center, double radius, t_color3 color);
t_plane		plane(t_point3 point, t_vec3 normal, t_color3 color);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:53:03 by yakim             #+#    #+#             */
/*   Updated: 2024/04/03 18:04:57 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

t_camera	camera(t_point3 origin, t_vec3 dir, double fov)
{
	t_camera	camera;

	camera.origin = point3(0, 0, 0);
	camera.horizontal = vec3(4, 0, 0);
	camera.vertical = vec3(0, 2, 0);
	return (camera);
}

t_ray	ray(t_point3 origin, t_vec3 dir)
{
	t_ray	ray;

	ray.origin = origin;
	ray.dir = dir;
	return (ray);
}

t_sphere	sphere(t_point3 center, double radius, t_color3 color)
{
	t_sphere	sphere;

	sphere.center = center;
	sphere.radius = radius;
	sphere.color = color;
	return (sphere);
}

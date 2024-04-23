/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:54:11 by jgoo              #+#    #+#             */
/*   Updated: 2024/04/23 19:54:22 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	get_axis(t_camera *camera)
{
	t_vector	up_direction;
	t_vector	r0;
	t_vector	r1;

	up_direction = vec4(0, 1, 0, 0);
	if (cmp_vec(camera->dir, up_direction))
	{
		if (camera->dir.d[Y] < 0)
		{
			camera->horizontal = vec4(-1, 0, 0, 0);
			camera->vertical = vec4(0, 0, -1, 0);
		}
		else
		{
			camera->horizontal = vec4(1, 0, 0, 0);
			camera->vertical = vec4(0, 0, 1, 0);
		}
		return ;
	}
	r0 = cross_(&camera->dir, &up_direction);
	normalize_vector(&r0);
	camera->horizontal = vec4(r0.d[X], r0.d[Y], r0.d[Z], r0.d[W]);
	r1 = cross_(&camera->dir, &r0);
	normalize_vector(&r1);
	camera->vertical = vec4(-r1.d[X], -r1.d[Y], -r1.d[Z], -r1.d[W]);
}

t_canvas	set_canvas(void)
{
	t_canvas	canvas;

	canvas.width = WIDTH;
	canvas.height = HEIGHT;
	canvas.aspect_ratio = (double)HEIGHT / (double)WIDTH;
	return (canvas);
}

t_viewport	set_viewport(t_camera camera, t_canvas canvas)
{
	t_viewport	viewport;
	t_vector	hor;
	t_vector	ver;

	viewport.v_width = 2 * tan(camera.fov * M_PI / (2.0 * 180));
	viewport.v_height = viewport.v_width * canvas.aspect_ratio;
	hor = vec_scala(camera.horizontal, viewport.v_width);
	ver = vec_scala(camera.vertical, viewport.v_height);
	viewport.left_bottom = vec_plus(vec_minus(vec_minus(camera.origin, \
	vec_scala(hor, 0.5)), vec_scala(ver, 0.5)), camera.dir);
	return (viewport);
}

t_ray	set_ray(t_camera camera, double u, double v, t_viewport viewport)
{
	t_ray		ray;
	t_vector	hor;
	t_vector	ver;

	ray.origin = camera.origin;
	hor = vec_scala(camera.horizontal, viewport.v_width);
	ver = vec_scala(camera.vertical, viewport.v_height);
	ray.dir = vec_minus(vec_plus(vec_plus(viewport.left_bottom, \
	vec_scala(hor, u)), vec_scala(ver, v)), ray.origin);
	normalize_vector(&ray.dir);
	return (ray);
}

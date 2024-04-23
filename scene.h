/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:34:51 by jgoo              #+#    #+#             */
/*   Updated: 2024/04/23 19:57:04 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "essential.h"
# include "matrix.h"
# include "object.h"

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_viewport
{
	double		v_height;
	double		v_width;
	t_vector	left_bottom;
}	t_viewport;

typedef struct s_canvas
{
	int		width;
	int		height;
	double	aspect_ratio;
}	t_canvas;

typedef struct s_uv
{
	int		init;
	double	u;
	double	v;
}	t_uv;

// settings.c
void		get_axis(t_camera *camera);
t_canvas	set_canvas(void);
t_viewport	set_viewport(t_camera camera, t_canvas canvas);
t_ray		set_ray(t_camera camera, double u, double v, t_viewport viewport);

// scene.c
t_vector	ray_color(t_info *info, t_ray ray);
void		render(t_info *info, t_canvas canvas, t_viewport viewport);
void		set_scene(t_info *info);

// texture.c
t_vector	get_normal(t_info *info, int u2, int v2);
void		checkerboard(t_info *info);
void		texture(t_info *info, t_uv *uv);
void		bump(t_info *info, t_uv *uv);

// mapping.c
void		sphere_map(t_info *info, double *u, double *v);
void		plane_map(t_info *info, double *u, double *v);
void		cylinder_map(t_info *info, double *u, double *v);
double		get_height(t_info *info, int idx);
void		cal_normal(t_info *info, t_vector new_axis, double theta);

#endif
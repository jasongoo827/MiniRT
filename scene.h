/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:34:51 by jgoo              #+#    #+#             */
/*   Updated: 2024/04/12 13:35:46 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "essential.h"
# include "matrix.h"

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

// settings.c
t_canvas	set_canvas(void);
t_viewport	set_viewport(t_camera camera, t_canvas canvas);
t_ray		set_ray(t_camera camera, double u, double v, t_viewport viewport);

// scene.c
t_vector	ray_color(t_ray ray, t_sphere sphere);
void		render(t_info *info, t_canvas canvas, t_viewport viewport);
void		set_scene(t_info *info);


#endif
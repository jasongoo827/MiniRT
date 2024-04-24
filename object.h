/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:54:50 by yakim             #+#    #+#             */
/*   Updated: 2024/04/24 16:04:57 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "data_struct.h"
# include "matrix.h"

typedef struct s_darray	t_darray;

typedef enum e_type
{
	CAMERA = 0,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
}	t_type;

typedef struct s_vector	t_vector;

typedef struct s_dscrmnt
{
	double	a;
	double	b;
	double	c;
	double	dscrmnt;
	double	root;
	double	height;
}	t_dscrmnt;

typedef struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_image;

typedef struct s_texture
{
	void	*tex_ptr;
	int		*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_texture;

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
	t_type		type;
	void		*ptr;
	int			checker;
	t_texture	tex;
	t_texture	bump;
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

typedef struct s_cone
{
	t_vector	center;
	t_vector	normal;
	t_vector	color;
	double		height;
}	t_cone;

typedef struct s_hit
{
	int			ishit;
	t_vector	point;
	t_vector	n;
	double		t;
	t_vector	color;
	t_obj		*obj;
	t_type		type;
}	t_hit;

typedef struct s_info
{
	void		*mlx;
	void		*win;
	t_texture	tex;
	t_texture	bump;
	t_ambient	ambient;
	t_camera	camera;
	t_darray	*lightarr;
	t_darray	*objarr;
	t_hit		record;
	t_image		img;
	int			count_light;
	int			count_camera;
	int			count_ambient;
}	t_info;

t_obj	*init_obj(t_type type);
void	init_record(t_hit *record);
t_hit	hit_obj(t_info *info, t_ray ray, t_hit record);
void	hit_obj_sphere(t_ray ray, t_hit *record, t_sphere *sphere, t_obj *obj);
void	hit_obj_plane(t_ray ray, t_hit *record, t_plane *plane, t_obj *obj);
void	hit_obj_cylinder(t_ray ray, t_hit *record, t_cylinder *cy, t_obj *obj);
void	hit_obj_cone(t_ray ray, t_hit *rec, t_cone *co, t_obj *obj);
double	co_get_height(t_ray *ray, double t, t_cone *co);
double	cy_get_height(t_ray *ray, double t, t_cylinder *cy);
int		dscrmnt_sp(t_dscrmnt *d, t_ray *ray, t_sphere *sp, t_vector *oc);
int		dscrmnt_cy(t_dscrmnt *d, t_ray *ray, t_cylinder *cy, t_vector *oc);
int		dscrmnt_cy_cap(t_dscrmnt *d, t_ray *ray, t_cylinder *cy, t_vector *cap);
int		dscrmnt_co(t_dscrmnt *d, t_ray *ray, t_cone *co, t_vector *oc);
int		dscrmnt_co_cap(t_dscrmnt *d, t_ray *ray, t_cone *co, t_vector *cap);

#endif

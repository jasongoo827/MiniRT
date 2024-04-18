#include "scene.h"

void	checkerboard(t_info *info)
{
	// without uv mapping
	// int	jump;
	// int	x = (info->record.point.d[X]);
	// int	y = (info->record.point.d[Y]);
	// // int	z = (info->record.point.d[Z]);

	// jump = (x + y) % 2;
	// // printf("x: %d y: %d z: %d jump: %d\n", x, y, z, jump);
	// if (jump == 0)
	// 	info->record.color = vec4(1, 1, 1, 0);
	// else
	// 	info->record.color = vec4(0, 0, 0, 0);

	// with uv mapping
	double	theta = atan2(info->record.point.d[X], info->record.point.d[Z]);
	double	radius = sqrt(pow(info->record.point.d[X], 2) + pow(info->record.point.d[Y], 2) \
	+ pow(info->record.point.d[Z], 2));
	double	phi = acos(info->record.point.d[Y] / radius);
	// printf("theta: %lf phi: %lf\n", theta, phi);
	double	raw_u = theta / (2.0 * M_PI);
	double	u = 0.5 - raw_u;
	double	v = 1 - phi / M_PI;
	int	u2 = floor(u * 32);
	int	v2 = floor(v * 32);
	if ((u2 + v2) % 2 == 0)
		info->record.color = vec4(1, 1, 1, 0);
	// else
	// 	info->record.color = vec4(0, 0, 0, 0);
}

void	texture(t_info *info)
{
	if (info->record.ishit)
	{
		double	theta = atan2(info->record.point.d[X], info->record.point.d[Z]);
		double	radius = sqrt(pow(info->record.point.d[X], 2) + pow(info->record.point.d[Y], 2) \
		+ pow(info->record.point.d[Z], 2));
		double	phi = acos(info->record.point.d[Y] / radius);
		double	raw_u = theta / (2.0 * M_PI);
		double	u = 0.5 - raw_u;
		double	v = 1 - phi / M_PI;
		int	u2 = (1 - u) * (info->tex.width - 1);
		int	v2 = (1 - v) * (info->tex.height - 1);

		// int color = info->tex.addr[info->tex.size_line / 4 * v2 + u2];
		// int x = ((color & 0XFF0000) >> 16);
		// int y = ((color & 0X00FF00) >> 8);
		// int z = (color & 0X0000FF);

		// int	bump = info->bump.addr[info->tex.size_line / 4 * v2 + u2];
		// int height = ((bump & 0XFF0000) >> 16);

		// // without bump map
		// info->record.color.d[X] =  ((double)x / 255.999);
		// info->record.color.d[Y] = ((double)y / 255.999);
		// info->record.color.d[Z] = ((double)z / 255.999);

		int	fx = info->tex.size_line / 4 * v2 + u2 - 1;
		int fx_bump = info->bump.addr[fx];
		int	height_fx = ((fx_bump & 0XFF0000) >> 16);

		int	nx = info->tex.size_line / 4 * v2 + u2 + 1;
		int nx_bump = info->bump.addr[nx];
		int	height_x = ((nx_bump & 0XFF0000) >> 16);

		int fy = info->tex.size_line / 4 * (v2 - 1) + u2;
		int fy_bump = info->bump.addr[fy];
		int height_fy = ((fy_bump & 0XFF0000) >> 16);

		int ny = info->tex.size_line / 4 * (v2 + 1) + u2;
		int ny_bump = info->bump.addr[ny];
		int height_y = ((ny_bump & 0XFF0000) >> 16);

		t_vector vec1 = vec4(1, (double)(height_x - height_fx), 0, 0);
		t_vector vec2 = vec4(0, (double)(height_y - height_fy), 1, 0);
		t_vector normal = cross_(&vec1, &vec2);
		normalize_vector(&normal);
		info->record.n = vec4(normal.d[X], normal.d[Y], normal.d[Z], 0);
	}
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
	ray.dir = vec_minus(vec_plus(vec_plus(viewport.left_bottom, vec_scala(hor, u)), vec_scala(ver, v)), ray.origin);
	normalize_vector(&ray.dir);
	return (ray);
}
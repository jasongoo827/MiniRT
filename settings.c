#include "scene.h"

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

	// viewport.v_height = 2.0;
	viewport.v_width = 2 * tan(camera.fov * M_PI / (2.0 * 180));
	viewport.v_height = viewport.v_width * canvas.aspect_ratio;
	hor = vec_scala(camera.horizontal, viewport.v_width);
	ver = vec_scala(camera.vertical, viewport.v_height);
	viewport.left_bottom = vec_plus(vec_minus(vec_minus(camera.origin, \
	vec_scala(hor, 0.5)), vec_scala(ver, 0.5)), camera.dir);

	// printf("fov: %lf\n", camera.fov / 2.0);
	// printf("v_height: %lf\n", viewport.v_height);
	// printf("v_width: %lf\n", viewport.v_width);
	// printf("h: %lf %lf %lf\n", camera.horizontal.d[X], camera.horizontal.d[Y], camera.horizontal.d[Z]);
	// printf("origin: %lf %lf %lf\n", camera.origin.d[X], camera.origin.d[Y], camera.origin.d[Z]);
	// printf("left_bottom: %lf %lf %lf\n", viewport.left_bottom.d[X], viewport.left_bottom.d[Y], viewport.left_bottom.d[Z]);

	return (viewport);
}

t_ray	set_ray(t_camera camera, double u, double v, t_viewport viewport)
{
	t_ray		ray;
	t_vector	hor;
	t_vector	ver;

	ray.origin = camera.origin;
	// printf("%lf, %lf", viewport.v_height, viewport.v_width);
	hor = vec_scala(camera.horizontal, viewport.v_width);
	ver = vec_scala(camera.vertical, viewport.v_height);
	ray.dir = vec_minus(vec_plus(vec_plus(viewport.left_bottom, vec_scala(hor, u)), vec_scala(ver, v)), ray.origin);
	// printf("ray.dir: %lf %lf %lf\n", ray.dir.d[X], ray.dir.d[Y], ray.dir.d[Z]);
	normalize_vector(&ray.dir);
	return (ray);
}
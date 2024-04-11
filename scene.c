#include "scene.h"

void	write_color(t_vector vector)
{
	// printf("%lf %lf %lf\n", vector.d[X], vector.d[Y], vector.d[Z]);
	printf("%d %d %d\n", (int)(255.999 * vector.d[X]), \
	(int)(255.999 * vector.d[Y]), (int)(255.999 * vector.d[Z]));
}

t_vector	ray_color(t_ray ray)
{
	double	t;

	t = 0.5 * (ray.dir.d[Y]  + 1.0);
    // (1-t) * 흰색 + t * 하늘색
    // return (vplus(vmult(color3(1, 1, 1), 1.0 - t), vmult(color3(0.5, 0.7, 1.0), t)));
	return (vec_plus(vec_scala(vec4(1, 1, 1, 1), 1.0 - t), vec_scala(vec4(0.5, 0.7, 1.0, 1), t)));
}

void	render(t_info *info, t_canvas canvas, t_viewport viewport)
{
	int		i;
	int		j;
	double	u;
	double	v;
	t_ray	ray;

	j = canvas.height;
	printf("P3\n%d %d\n255\n", canvas.width, canvas.height);
	while (--j >= 0)
	{
		i = -1;
		while (++i < canvas.width)
		{
			u = (double)i / (canvas.width - 1);
			v = (double)j / (canvas.height - 1);
			ray = set_ray(info->camera, u, v, viewport);
			write_color(ray_color(ray));
		}
	}
}

void	set_scene(t_info *info)
{
	t_canvas	canvas;
	t_viewport	viewport;
	t_matrix	*matrix;

	matrix = get_look_at_matrix(&info->camera);
	canvas = set_canvas();
	viewport = set_viewport(info->camera, canvas);
	// render
	render(info, canvas, viewport);
}
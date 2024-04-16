#include "scene.h"
#include "light.h"

int	create_argb(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

void	write_color(t_info *info, t_vector vector, int y, int x)
{
	char	*dst;
	// printf("%lf %lf %lf\n", vector.d[X], vector.d[Y], vector.d[Z]);
	// printf("%d %d %d\n", (int)(255.999 * vector.d[X]), \
	// (int)(255.999 * vector.d[Y]), (int)(255.999 * vector.d[Z]));

	dst = info->img.addr + y * info->img.size_line + x * (info->img.bits_per_pixel / 8);
	*(int *)dst = create_argb(0, (int)(255.999 * vector.d[X]), (int)(255.999 * vector.d[Y]), (int)(255.999 * vector.d[Z]));
}

int	hit_sphere(t_ray ray, t_sphere sphere)
{
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	oc = vec_minus(ray.origin, sphere.center);
	a = dot(&ray.dir, &ray.dir);
	b = 2.0 * dot(&oc, &ray.dir);
	c = dot(&oc, &oc) - pow(sphere.radius, 2);
	discriminant = b * b - 4 * a * c;

	return (discriminant > 0);
}

t_vector	ray_color(t_info *info, t_ray ray)
{
	double	t;
	t_hit	record;

	init_record(&record);
	record = hit_obj(info, ray, record);
	if (record.ishit)
	{
		info->record = record;
		// check texture
		checkerboard(info);
		return (phong_lightning(info));
	}
	else
	{
		t = 0.5 * (ray.dir.d[Y]  + 1.0);
		return (vec_plus(vec_scala(vec4(1, 1, 1, 1), 1.0 - t), vec_scala(vec4(0.5, 0.7, 1.0, 1), t)));
	}
}

void	render(t_info *info, t_canvas canvas, t_viewport viewport)
{
	int		i;
	int		j;
	double	u;
	double	v;
	t_ray	ray;

	j = canvas.height;
	// printf("P3\n%d %d\n255\n", canvas.width, canvas.height);
	while (--j >= 0)
	{
		i = -1;
		while (++i < canvas.width)
		{
			u = (double)i / (canvas.width - 1);
			v = (double)j / (canvas.height - 1);
			ray = set_ray(info->camera, u, v, viewport);
			write_color(info, ray_color(info, ray), canvas.height - j - 1, i);
		}
	}
}

void	set_scene(t_info *info)
{
	t_canvas	canvas;
	t_viewport	viewport;

	get_axis(&info->camera);
	canvas = set_canvas();
	viewport = set_viewport(info->camera, canvas);
	render(info, canvas, viewport);
}
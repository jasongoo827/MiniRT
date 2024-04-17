/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:36:40 by yakim             #+#    #+#             */
/*   Updated: 2024/04/17 21:04:21 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "object.h"
#include "scene.h"
#include "parse.h"

int	win_init(void *mlx, void **win)
{
	*win = mlx_new_window(mlx, 1920, 1080, "minirt");
	mlx_clear_window(mlx, *win);
	return (0);
}

void	l(void)
{
	system("leaks $PPID");
}

static int	key_hook(int keycode, t_info *info)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(info->mlx, info->win);
		exit(0);
	}
	return (0);
}

static int	exit_window(t_info *info)
{
	mlx_destroy_window(info->mlx, info->win);
	exit(0);
}

void	set_image(t_info *info)
{
	info->img.img_ptr = mlx_new_image(info->mlx, 1920, 1080);
	info->img.addr = mlx_get_data_addr(info->img.img_ptr, \
	&info->img.bits_per_pixel, &info->img.size_line, &info->img.endian);
	// draw_image(&info->img, info->map);
	set_scene(info);
	mlx_put_image_to_window(info->mlx, info->win, \
	info->img.img_ptr, 0, 0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	// atexit(l);
	ft_bzero(&info, sizeof(t_info));
	info.mlx = mlx_init();
	win_init(info.mlx, &info.win);
	info.tex.tex_ptr = mlx_xpm_file_to_image(info.mlx, "earthmap1k.xpm", &info.tex.width, &info.tex.height);
	printf("width: %d height: %d\n", info.tex.width, info.tex.height);
	info.tex.addr = (int *)mlx_get_data_addr(info.tex.tex_ptr, &info.tex.bits_per_pixel, &info.tex.size_line, &info.tex.endian);
	parse(argc, argv, &info);
	// // print_parse_result(&info);	
	set_image(&info);
	mlx_hook(info.win, 2, 0, key_hook, &info);
	mlx_hook(info.win, 17, 0, exit_window, &info);
	mlx_loop(info.mlx);
	return (0);
}

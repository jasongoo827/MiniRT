/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:36:40 by yakim             #+#    #+#             */
/*   Updated: 2024/04/24 14:29:15 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt_bonus.h"
#include "object_bonus.h"
#include "scene_bonus.h"
#include "parse_bonus.h"

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
	parse(argc, argv, &info);
	set_image(&info);
	mlx_hook(info.win, 2, 0, key_hook, &info);
	mlx_hook(info.win, 17, 0, exit_window, &info);
	mlx_loop(info.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:36:40 by yakim             #+#    #+#             */
/*   Updated: 2024/04/03 17:01:32 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>
#include <object.h>

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

int	win_init(void *mlx, void **win)
{
	int	x_max;
	int	y_max;

	mlx_get_screen_size(mlx, &x_max, &y_max);
	*win = mlx_new_window(mlx, 500, 500, "win");
	mlx_clear_window(mlx, *win);
	return (0);
}

int	ft_close(t_vars *vars)
{
	(void)vars;
	exit(0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	(void)argc;
	(void)argv;
	vars.mlx = mlx_init();
	win_init(vars.mlx, &vars.win);
	t_camera	c = camera(point3(0, 0, 0), vec3(0, 0, 1), 90);
	int i = 500;
	while (i >= 0)
	{
		int j = 500;
		while (j >= 0)
		{
			mlx_pixel_put(vars.mlx, vars.win, i, j, 0x00FFFFFF);
			j--;
		}
		i--;
	}
	mlx_hook(vars.win, 17, 0, ft_close, &vars);
	mlx_loop(vars.mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:36:40 by yakim             #+#    #+#             */
/*   Updated: 2024/04/08 19:12:38 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"

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

	//parsing
	parse(argc, argv);


	
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

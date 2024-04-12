/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:36:40 by yakim             #+#    #+#             */
/*   Updated: 2024/04/12 15:06:38 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "object.h"
#include "scene.h"
#include "parse.h"

int	win_init(void *mlx, void **win)
{
	*win = mlx_new_window(mlx, 2560, 1440, "win");
	mlx_clear_window(mlx, *win);
	return (0);
}

int	ft_close(t_info *info)
{
	(void)info;
	exit(0);
}

void	l(void)
{
	system("leaks $PPID");
}

int	main(int argc, char **argv)
{
	t_info	info;

	// atexit(l);
	// info.mlx = mlx_init();
	// win_init(info.mlx, &info.win);

	//parsing start
	parse(argc, argv, &info);
	// print_parse_result(&info);
	//parsing end
	
	// set scene
	set_scene(&info);
	// mlx_hook(info.win, 17, 0, ft_close, &info);
	// mlx_loop(info.mlx);
}

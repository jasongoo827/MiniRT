/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:12:19 by yakim             #+#    #+#             */
/*   Updated: 2024/04/23 13:51:09 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "essential.h"
#include "object.h"
#include "parse.h"
#include "utils.h"

void	parse_object(char *line, t_info *info)
{
	char	**arr;

	arr = ft_split_rt(line);
	if (arr == NULL || arr[0] == NULL || arr[0][0] == 0)
	{
		free_split(arr);
		return ;
	}
	if (ft_strcmp(arr[0], "A") == 0)
		parse_ambient(arr, info);
	else if (ft_strcmp(arr[0], "C") == 0)
		parse_camera(arr, info);
	else if (ft_strcmp(arr[0], "L") == 0)
		parse_light(arr, info);
	else if (ft_strcmp(arr[0], "sp") == 0)
		parse_sphere(arr, info);
	else if (ft_strcmp(arr[0], "pl") == 0)
		parse_plane(arr, info);
	else if (ft_strcmp(arr[0], "cy") == 0)
		parse_cylinder(arr, info);
	else if (BONUS && ft_strcmp(arr[0], "co") == 0)
		parse_cone(arr, info);
	else
		cus_error("Error\nUnknown Identifier\n");
	free_split(arr);
}

void	print_parse_result(t_info *info)
{
	printf("camera:\n");
	printf("origin: %f, %f, %f\n", info->camera.origin.d[0], info->camera.origin.d[1], info->camera.origin.d[2]);
	printf("dir: %f, %f, %f\n", info->camera.dir.d[0], info->camera.dir.d[1], info->camera.dir.d[2]);
	printf("fov: %f\n\n", info->camera.fov);
	// printf("light:\n");
	// printf("origin: %f, %f, %f\n", info->light.origin.d[0], info->light.origin.d[1], info->light.origin.d[2]);
	// printf("color: %f, %f, %f\n", info->light.color.d[0], info->light.color.d[1], info->light.color.d[2]);
	// printf("ratio: %f\n\n", info->light.ratio);
	printf("ambient:\n");
	printf("ratio: %f\n", info->ambient.ratio);
	printf("color: %f, %f, %f\n\n", info->ambient.color.d[0], info->ambient.color.d[1], info->ambient.color.d[2]);
	int i = 0;
	while (i < info->objarr->size)
	{
		t_obj *temp = info->objarr->arr[i];
		if (temp->type == SPHERE)
		{
			printf("sphere:\n");
			printf("center: %f, %f, %f\n", ((t_sphere *)(temp->ptr))->center.d[0], ((t_sphere *)(temp->ptr))->center.d[1], ((t_sphere *)(temp->ptr))->center.d[2]);
			printf("diameter: %f\n", ((t_sphere *)(temp->ptr))->radius);
			printf("color: %f, %f, %f\n\n", ((t_sphere *)(temp->ptr))->color.d[0], ((t_sphere *)(temp->ptr))->color.d[1], ((t_sphere *)(temp->ptr))->color.d[2]);
		}
		else if (temp->type == PLANE)
		{
			printf("plane:\n");
			printf("point: %f, %f, %f\n", ((t_plane *)(temp->ptr))->point.d[0], ((t_plane *)(temp->ptr))->point.d[1], ((t_plane *)(temp->ptr))->point.d[2]);
			printf("normal: %f, %f, %f\n", ((t_plane *)(temp->ptr))->normal.d[0], ((t_plane *)(temp->ptr))->normal.d[1], ((t_plane *)(temp->ptr))->normal.d[2]);
			printf("color: %f, %f, %f\n\n", ((t_plane *)(temp->ptr))->color.d[0], ((t_plane *)(temp->ptr))->color.d[1], ((t_plane *)(temp->ptr))->color.d[2]);
		}
		else if (temp->type == CYLINDER)
		{
			printf("cylinder:\n");
			printf("center: %f, %f, %f\n", ((t_cylinder *)(temp->ptr))->center.d[0], ((t_cylinder *)(temp->ptr))->center.d[1], ((t_cylinder *)(temp->ptr))->center.d[2]);
			printf("normal: %f, %f, %f\n", ((t_cylinder *)(temp->ptr))->normal.d[0], ((t_cylinder *)(temp->ptr))->normal.d[1], ((t_cylinder *)(temp->ptr))->normal.d[2]);
			printf("diameter: %f\n", ((t_cylinder *)(temp->ptr))->diameter);
			printf("height: %f\n", ((t_cylinder *)(temp->ptr))->height);
			printf("color: %f, %f, %f\n\n", ((t_cylinder *)(temp->ptr))->color.d[0], ((t_cylinder *)(temp->ptr))->color.d[1], ((t_cylinder *)(temp->ptr))->color.d[2]);
		}
		i++;
	}
}

void	parse_name_check(int argc, char **argv)
{
	int		len_name;

	if (argc != 2)
		cus_error("Error\nToo many arguments\n");
	len_name = ft_strlen(argv[1]);
	if (len_name < 4)
		cus_error("Error\nMap name error\n");
	if (argv[1][len_name - 3] != '.' || argv[1][len_name - 2] != 'r' || \
		argv[1][len_name - 1] != 't')
		cus_error("Error\nMap name error\n");
}

void	parse(int argc, char **argv, t_info *info)
{
	int		fd;
	char	*line;

	parse_name_check(argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		cus_error("Error\nOpen error\n");
	info->objarr = init_array(0);
	info->lightarr = init_array(0);
	line = get_next_line(fd);
	while (line)
	{
		line = remove_nl(line);
		// printf("%s\n", newline);
		parse_object(line, info);
		free(line);
		line = get_next_line(fd);
	}
}

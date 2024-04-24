/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:12:19 by yakim             #+#    #+#             */
/*   Updated: 2024/04/24 11:03:27 by yakim            ###   ########.fr       */
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
		parse_object(line, info);
		free(line);
		line = get_next_line(fd);
	}
	if (info->count_ambient != 1 || info->count_camera != 1)
		cus_error("Error\nMore or less object\n");
	if (BONUS == 0 && info->count_light != 1 && info->count_light != 0)
		cus_error("Error\nMore or less object\n");
	if (BONUS && info->count_light < 0)
		cus_error("Error\nMore or less object\n");
}

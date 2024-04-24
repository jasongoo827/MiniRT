/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:12:19 by yakim             #+#    #+#             */
/*   Updated: 2024/04/24 14:31:44 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "essential_bonus.h"
#include "object_bonus.h"
#include "parse_bonus.h"
#include "utils_bonus.h"

t_vector	parse_vector(char **arr, int isnorm, int ispoint, int iscolor)
{
	t_vector	v;
	int			i;

	if (arr == NULL)
		cus_error("Error\nLess arguments in vector input\n");
	v = vec4(0, 0, 0, 0);
	i = -1;
	while (++i < 3)
	{
		v.d[i] = ft_strtod(arr[i]);
		if (iscolor)
		{
			if (v.d[i] < 0 || v.d[i] > 255)
				cus_error("Error\nColor input out of range\n");
			v.d[i] /= 255.999;
		}
	}
	if (ispoint)
		v.d[3] = 1;
	if (isnorm && (pow(v.d[0], 2) + pow(v.d[1], 2) + pow(v.d[2], 2) != 1))
		cus_error("Error\nNot normalized vector input\n");
	if (arr[i])
		cus_error("Error\nMore arguments in vector input\n");
	free_split(arr);
	return (v);
}

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

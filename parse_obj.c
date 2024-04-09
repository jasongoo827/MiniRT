/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:52:57 by yakim             #+#    #+#             */
/*   Updated: 2024/04/09 17:02:06 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	parse_vector(char **arr, int isnormalized, int ispoint)
{
	t_vector	v;
	int			i;

	if (arr == NULL)
		cus_error("Error\nLess arguments in vector input\n");
	i = 0;
	while (i < 3)
	{
		v.d[i] = ft_strtod(arr[i]);
		// printf("i: %f\n", v.d[i]);
		i++;
	}
	if (ispoint)
		v.d[3] = 1;
	else
		v.d[3] = 0;
	if (isnormalized && (pow(v.d[0], 2) + pow(v.d[1], 2)+ pow(v.d[2], 2) != 1))
	{
		// printf("%.90f\n", pow(v.d[0], 2) + pow(v.d[1], 2)+ pow(v.d[2], 2));
		cus_error("Error\nNot normalized vector input\n");
	}
	if (arr[i])
		cus_error("Error\nMore arguments in vector input\n");
	return (v);
}

void	parse_ambient(char **arr, t_info *info)
{
	char	**temp;

	if (arr[1] == NULL || arr[2] == NULL)
		cus_error("Error\nNot enough arguments\n");
	info->ambient.ratio = ft_strtod(arr[1]);
	if (info->ambient.ratio < 0 || info->ambient.ratio >1)
		cus_error("Error\nAmbient ratio out of range\n");
	temp = ft_split(arr[2], ',');
	info->ambient.color = parse_vector(temp, 0, 1);
	free_split(temp);
	if (arr[3] != NULL)
		cus_error("Error\nToo much arguments\n");
}

void	parse_camera(char **arr, t_info *info)
{
	char	**temp;

	if (arr[1] == NULL || arr[2] == NULL || arr[3] == NULL)
		cus_error("Error\nNot enough arguments\n");
	temp = ft_split(arr[1], ',');
	info->camera.origin = parse_vector(temp, 0, 1);
	free_split(temp);
	temp = ft_split(arr[2], ',');
	info->camera.dir = parse_vector(temp, 1, 0);
	free_split(temp);
	info->camera.fov = ft_strtod(arr[3]);
	if (info->camera.fov <= 0 || info->camera.fov >= 180)
		cus_error("Error\nFov out of range\n");
	if (arr[4] != NULL)
		cus_error("Error\nToo much arguments\n");
}

void	parse_light(char **arr, t_info *info)
{
	char	**temp;

	if (arr[1] == NULL || arr[2] == NULL || arr[3] == NULL)
		cus_error("Error\nNot enough arguments\n");
	temp = ft_split(arr[1], ',');
	info->light.origin = parse_vector(temp, 0, 1);
	free_split(temp);
	info->light.ratio = ft_strtod(arr[2]);
	if (info->light.ratio < 0 || info->light.ratio > 1)
		cus_error("Error\nLight ratio out of range\n");
	temp = ft_split(arr[3], ',');
	info->light.color = parse_vector(temp, 0, 0);
	free_split(temp);
	if (arr[4] != NULL)
		cus_error("Error\nToo much arguments\n");
}

void	parse_sphere(char **arr, t_info *info)
{
	(void)arr;
	(void)info;
}

void	parse_plane(char **arr, t_info *info)
{
	(void)arr;
	(void)info;
}

void	parse_cylinder(char **arr, t_info *info)
{
	(void)arr;
	(void)info;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:52:57 by yakim             #+#    #+#             */
/*   Updated: 2024/04/09 20:40:20 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "essential.h"

void	parse_ambient(char **arr, t_info *info)
{
	char	**temp;

	if (arr[1] == NULL || arr[2] == NULL)
		cus_error("Error\nNot enough arguments\n");
	info->ambient.ratio = ft_strtod(arr[1]);
	if (info->ambient.ratio < 0 || info->ambient.ratio > 1)
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
	t_obj		*obj;
	t_sphere	*sphere;
	char		**temp;

	obj = init_obj(SPHERE);
	sphere = (t_sphere *)obj->ptr;
	if (arr[1] == NULL || arr[2] == NULL || arr[3] == NULL)
		cus_error("Error\nNot enough arguments\n");
	temp = ft_split(arr[1], ',');
	sphere->center = parse_vector(temp, 0, 1);
	free_split(temp);
	sphere->radius = ft_strtod(arr[2]);
	temp = ft_split(arr[3], ',');
	sphere->color = parse_vector(temp, 0, 0);
	free_split(temp);
	if (arr[4] != NULL)
		cus_error("Error\nToo much arguments\n");
	push_back(info->objarr, obj);
}

void	parse_plane(char **arr, t_info *info)
{
	t_obj	*obj;
	t_plane	*plane;
	char	**temp;

	obj = init_obj(PLANE);
	plane = (t_plane *)obj->ptr;
	if (arr[1] == NULL || arr[2] == NULL || arr[3] == NULL)
		cus_error("Error\nNot enough arguments\n");
	temp = ft_split(arr[1], ',');
	plane->point = parse_vector(temp, 0, 1);
	free_split(temp);
	temp = ft_split(arr[2], ',');
	plane->normal = parse_vector(temp, 1, 0);
	free_split(temp);
	temp = ft_split(arr[3], ',');
	plane->color = parse_vector(temp, 0, 0);
	free_split(temp);
	if (arr[4] != NULL)
		cus_error("Error\nToo much arguments\n");
	push_back(info->objarr, obj);
}

void	parse_cylinder(char **arr, t_info *info)
{
	t_obj		*obj;
	t_cylinder	*cylinder;
	char		**temp;

	obj = init_obj(CYLINDER);
	cylinder = (t_cylinder *)obj->ptr;
	if (arr[1] == NULL || arr[2] == NULL || arr[3] == NULL || arr[4] == NULL || arr[5] == NULL)
		cus_error("Error\nNot enough arguments\n");
	temp = ft_split(arr[1], ',');
	cylinder->center = parse_vector(temp, 0, 1);
	free_split(temp);
	temp = ft_split(arr[2], ',');
	cylinder->normal = parse_vector(temp, 1, 0);
	free_split(temp);
	cylinder->diameter = ft_strtod(arr[3]);
	cylinder->height = ft_strtod(arr[4]);
	temp = ft_split(arr[5], ',');
	cylinder->color = parse_vector(temp, 0, 0);
	free_split(temp);
	if (arr[6] != NULL)
		cus_error("Error\nToo much arguments\n");
	push_back(info->objarr, obj);
}

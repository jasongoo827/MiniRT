/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:52:57 by yakim             #+#    #+#             */
/*   Updated: 2024/04/23 14:56:51 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "essential.h"
#include "mlx.h"
#include "object.h"
#include "parse.h"
#include "utils.h"

void	parse_ambient(char **arr, t_info *info)
{
	if (arr[1] == NULL || arr[2] == NULL)
		cus_error("Error\nNot enough arguments\n");
	info->ambient.ratio = ft_strtod(arr[1]);
	if (info->ambient.ratio < 0 || info->ambient.ratio > 1)
		cus_error("Error\nAmbient ratio out of range\n");
	info->ambient.color = parse_vector(ft_split(arr[2], ','), 0, 1, 1);
	if (arr[3] != NULL)
		cus_error("Error\nToo much arguments\n");
	info->count_ambient++;
}

void	parse_camera(char **arr, t_info *info)
{
	if (arr[1] == NULL || arr[2] == NULL || arr[3] == NULL)
		cus_error("Error\nNot enough arguments\n");
	info->camera.origin = parse_vector(ft_split(arr[1], ','), 0, 1, 0);
	info->camera.dir = parse_vector(ft_split(arr[2], ','), 1, 0, 0);
	info->camera.fov = ft_strtod(arr[3]);
	if (info->camera.fov <= 0 || info->camera.fov >= 180)
		cus_error("Error\nFov out of range\n");
	if (arr[4] != NULL)
		cus_error("Error\nToo much arguments\n");
	info->count_camera++;
}

void	parse_light(char **arr, t_info *info)
{
	t_obj	*obj;
	t_light	*light;

	obj = init_obj(LIGHT);
	light = (t_light *)obj->ptr;
	if (arr[1] == NULL || arr[2] == NULL || arr[3] == NULL)
		cus_error("Error\nNot enough arguments\n");
	light->origin = parse_vector(ft_split(arr[1], ','), 0, 1, 0);
	light->ratio = ft_strtod(arr[2]);
	if (light->ratio < 0 || light->ratio > 1)
		cus_error("Error\nLight ratio out of range\n");
	if (BONUS)
		light->color = parse_vector(ft_split(arr[3], ','), 0, 0, 1);
	else
		light->color = vec4(1, 1, 1, 0);
	if (arr[4] != NULL)
		cus_error("Error\nToo much arguments\n");
	push_back(info->lightarr, obj);
	info->count_light++;
}

void	parse_sphere(char **arr, t_info *info)
{
	t_obj		*obj;
	t_sphere	*sphere;

	obj = init_obj(SPHERE);
	sphere = (t_sphere *)obj->ptr;
	if (arr[1] == NULL || arr[2] == NULL || arr[3] == NULL)
		cus_error("Error\nNot enough arguments\n");
	sphere->center = parse_vector(ft_split(arr[1], ','), 0, 1, 0);
	sphere->radius = ft_strtod(arr[2]);
	sphere->color = parse_vector(ft_split(arr[3], ','), 0, 0, 1);
	if (arr[4] != NULL && BONUS)
	{
		if (ft_strcmp(arr[4], "ch") == 0)
			obj->checker = 1;
		else
			parse_bonus(arr[4], info, &obj->tex, &obj->bump);
	}
	else if (arr[4] != NULL)
		cus_error("Error\nToo much arguments\n");
	push_back(info->objarr, obj);
}

void	parse_plane(char **arr, t_info *info)
{
	t_obj	*obj;
	t_plane	*plane;

	obj = init_obj(PLANE);
	plane = (t_plane *)obj->ptr;
	if (arr[1] == NULL || arr[2] == NULL || arr[3] == NULL)
		cus_error("Error\nNot enough arguments\n");
	plane->point = parse_vector(ft_split(arr[1], ','), 0, 1, 0);
	plane->normal = parse_vector(ft_split(arr[2], ','), 1, 0, 0);
	plane->color = parse_vector(ft_split(arr[3], ','), 0, 0, 1);
	if (arr[4] != NULL && BONUS)
	{
		if (ft_strcmp(arr[4], "ch") == 0)
			obj->checker = 1;
		else
			parse_bonus(arr[4], info, &obj->tex, &obj->bump);
	}
	else if (arr[4] != NULL)
		cus_error("Error\nToo much arguments\n");
	push_back(info->objarr, obj);
}

void	parse_cylinder(char **arr, t_info *info)
{
	t_obj		*obj;
	t_cylinder	*cylinder;

	obj = init_obj(CYLINDER);
	cylinder = (t_cylinder *)obj->ptr;
	if (arr[1] == NULL || arr[2] == NULL || arr[3] == NULL || arr[4] == NULL || arr[5] == NULL)
		cus_error("Error\nNot enough arguments\n");
	cylinder->center = parse_vector(ft_split(arr[1], ','), 0, 1, 0);
	cylinder->normal = parse_vector(ft_split(arr[2], ','), 1, 0, 0);
	cylinder->diameter = ft_strtod(arr[3]);
	cylinder->height = ft_strtod(arr[4]);
	cylinder->color = parse_vector(ft_split(arr[5], ','), 0, 0, 1);
	if (arr[6] != NULL && BONUS)
	{
		if (ft_strcmp(arr[6], "ch") == 0)
			obj->checker = 1;
		else
			parse_bonus(arr[6], info, &obj->tex, &obj->bump);
	}
	else if (arr[6] != NULL)
		cus_error("Error\nToo much arguments\n");
	push_back(info->objarr, obj);
}

void	parse_cone(char **arr, t_info *info)
{
	t_obj	*obj;
	t_cone	*cone;

	obj = init_obj(CONE);
	cone = (t_cone *)obj->ptr;
	if (arr[1] == NULL || arr[2] == NULL || arr[3] == NULL || arr[4] == NULL)
		cus_error("Error\nNot enough arguments\n");
	cone->center = parse_vector(ft_split(arr[1], ','), 0, 1, 0);
	cone->normal = parse_vector(ft_split(arr[2], ','), 1, 0, 0);
	cone->height = ft_strtod(arr[3]);
	cone->color = parse_vector(ft_split(arr[4], ','), 0, 0, 1);
	if (arr[6] != NULL && BONUS)
	{
		if (ft_strcmp(arr[6], "ch") == 0)
			obj->checker = 1;
		else
			parse_bonus(arr[6], info, &obj->tex, &obj->bump);
	}
	else if (arr[6] != NULL)
		cus_error("Error\nToo much arguments\n");
	push_back(info->objarr, obj);
}

void	parse_bonus(char *str, t_info *info, t_texture *tex, t_texture *bump)
{
	char	**temp;

	temp = ft_split(str, ',');
	if (temp[0])
	{
		tex->tex_ptr = mlx_xpm_file_to_image(info->mlx, temp[0], &tex->width, &tex->height);
		tex->addr = (int *)mlx_get_data_addr(tex->tex_ptr, &tex->bits_per_pixel, &tex->size_line, &tex->endian);
	}
	if (temp[1])
	{
		bump->tex_ptr = mlx_xpm_file_to_image(info->mlx, temp[1], &bump->width, &bump->height);
		bump->addr = (int *)mlx_get_data_addr(bump->tex_ptr, &bump->bits_per_pixel, &bump->size_line, &bump->endian);
	}
	if (tex->tex_ptr == 0 || bump->tex_ptr == 0)
	{
		free_split(temp);
		cus_error("Error\nInvalid bonus argument input\n");
	}
	free_split(temp);
}

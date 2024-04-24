/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:41:50 by yakim             #+#    #+#             */
/*   Updated: 2024/04/24 14:19:49 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "essential.h"
#include "parse.h"
#include "utils.h"

void	parse_cylinder(char **arr, t_info *info)
{
	t_obj		*obj;
	t_cylinder	*cylinder;

	obj = init_obj(CYLINDER);
	cylinder = (t_cylinder *)obj->ptr;
	if (arr[1] == NULL || arr[2] == NULL || arr[3] == NULL \
	|| arr[4] == NULL || arr[5] == NULL)
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
		if (arr[7] != NULL)
			cus_error("Error\nToo much arguments\n");
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
	if (arr[5] != NULL && BONUS)
	{
		if (ft_strcmp(arr[5], "ch") == 0)
			obj->checker = 1;
		else
			parse_bonus(arr[5], info, &obj->tex, &obj->bump);
		if (arr[6] != NULL)
			cus_error("Error\nToo much arguments\n");
	}
	else if (arr[5] != NULL)
		cus_error("Error\nToo much arguments\n");
	push_back(info->objarr, obj);
}

void	parse_bonus(char *str, t_info *info, t_texture *tex, t_texture *bump)
{
	char	**temp;

	temp = ft_split(str, ',');
	if (temp[0])
	{
		tex->tex_ptr = mlx_xpm_file_to_image(info->mlx, temp[0], \
		&tex->width, &tex->height);
		if (tex->tex_ptr == 0)
			cus_error("Error\nInvalid bonus argument input\n");
		tex->addr = (int *)mlx_get_data_addr(tex->tex_ptr, \
		&tex->bits_per_pixel, &tex->size_line, &tex->endian);
	}
	if (temp[1])
	{
		bump->tex_ptr = mlx_xpm_file_to_image(info->mlx, temp[1], \
		&bump->width, &bump->height);
		if (bump->tex_ptr == 0)
			cus_error("Error\nInvalid bonus argument input\n");
		bump->addr = (int *)mlx_get_data_addr(bump->tex_ptr, \
		&bump->bits_per_pixel, &bump->size_line, &bump->endian);
	}
	free_split(temp);
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:12:19 by yakim             #+#    #+#             */
/*   Updated: 2024/04/09 17:02:10 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "stdio.h"//

int	ft_isspace(char c)
{
	if (c >= 9 && c <= 13)
		return (1);
	else if (c == 32)
		return (1);
	return (0);
}

double	ft_strtod(const char *str)
{
	double	d;
	char	sign;
	double	n;

	d = 0.0;
	sign = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' | *str == '+')
	{
		if (*str == '-')
			sign = 1;
		str++;
	}
	while (*str && *str != '.')
	{
		if (ft_isdigit(*str) == 0 && *str != '.')
		{
			cus_error("Error\nInput error\n");
		}
		d = (d * 10) + (double)(*str - '0');
		str++;
	}
	if (*str == '.')
		str++;
	n = 0.1;
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			cus_error("Error\nInput error\n");
		d += (*str - '0') * n;
		n /= 10;
		str++;
		//n에 의한 오차 발생 가능함.
	}
	if (sign)
		return (d * -1);
	return (d);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 == '\0' || *s2 == '\0')
			break ;
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	parse_object(char *line, t_info *info)
{
	char	**arr;

	arr = ft_split(line, ' ');
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
	printf("light:\n");
	printf("origin: %f, %f, %f\n", info->light.origin.d[0], info->light.origin.d[1], info->light.origin.d[2]);
	printf("color: %f, %f, %f\n", info->light.color.d[0], info->light.color.d[1], info->light.color.d[2]);
	printf("ratio: %f\n\n", info->light.ratio);
	printf("ambient:\n");
	printf("ratio: %f\n", info->ambient.ratio);
	printf("color: %f, %f, %f\n\n", info->ambient.color.d[0], info->ambient.color.d[1], info->ambient.color.d[2]);

}

void	parse(int argc, char **argv, t_info *info)
{
	int		len_name;
	int		fd;
	char	*line;

	if (argc != 2)
		cus_error("Error\nToo many arguments\n");
	len_name = ft_strlen(argv[1]);
	if (len_name < 4)
		cus_error("Error\nMap name error\n");
	if (argv[1][len_name - 3] != '.' || argv[1][len_name - 2] != 'r' || \
		argv[1][len_name - 1] != 't')
		cus_error("Error\nMap name error\n");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		cus_error("Error\nOpen error\n");
	line = get_next_line(fd);
	while (line)
	{
		char *nl = ft_strchr(line, '\n');
		char *newline;
		if (nl)
		{
			newline = malloc(ft_strlen(line));
			ft_strlcpy(newline, line, ft_strlen(line));
		}
		else
			newline = line;
		printf("%s\n", newline);
		parse_object(newline, info);
		free(newline);
		line = get_next_line(fd);
	}
}

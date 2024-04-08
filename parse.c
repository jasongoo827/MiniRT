/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:12:19 by yakim             #+#    #+#             */
/*   Updated: 2024/04/08 19:29:46 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_object(char *line)
{
	char	**arr;

	arr = ft_split(line, ' ');
	if (arr == NULL)
		return ;
	if (ft_strcpy(arr[0], "A") == 0)
		parse_ambient(arr);
	else if (ft_strlcpy(arr[0], "C") == 0)
		parse_camera(arr);
	else if (ft_strcpy(arr[0], "L") == 0)
		parse_light(arr);
	else if (ft_strcpy(arr[0], "sp") == 0)
		parse_sphere(arr);
	else if (ft_strcpy(arr[0], "pl") == 0)
		parse_plane(arr);
	else if (ft_strcpy(arr[0], "cy") == 0)
		parse_cylinder(arr);
}

void	parse(int argc, char **argv)
{
	int		len_name;
	int		fd;
	char	*line;

	if (argc != 2)
		cus_error(2, "Error\nToo many arguments\n");
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
		parse_object(line);
		free(line);
		line = get_next_line(fd);
	}
}

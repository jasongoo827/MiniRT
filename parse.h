/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:22:14 by yakim             #+#    #+#             */
/*   Updated: 2024/04/11 15:04:00 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "essential.h"
# include "object.h"

void		parse(int argc, char **argv, t_info *info);
void		parse_object(char *line, t_info *info);
t_vector	parse_vector(char **arr, int isnormalized, int ispoint);
void		parse_ambient(char ** arr, t_info *info);
void		parse_camera(char ** arr, t_info *info);
void		parse_light(char ** arr, t_info *info);
void		parse_sphere(char ** arr, t_info *info);
void		parse_plane(char ** arr, t_info *info);
void		parse_cylinder(char ** arr, t_info *info);
int			ft_isspace(char c);
double		ft_strtod(const char *str);
void		free_split(char **arr);
void		print_parse_result(t_info *info);//

#endif

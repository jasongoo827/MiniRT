/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:22:14 by yakim             #+#    #+#             */
/*   Updated: 2024/04/24 14:31:59 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_BONUS_H
# define PARSE_BONUS_H

# include "essential_bonus.h"
# include "object_bonus.h"

void		parse(int argc, char **argv, t_info *info);
void		parse_object(char *line, t_info *info);
t_vector	parse_vector(char **arr, int isnorm, int ispoint, int iscolor);
void		parse_ambient(char **arr, t_info *info);
void		parse_camera(char **arr, t_info *info);
void		parse_light(char **arr, t_info *info);
void		parse_sphere(char **arr, t_info *info);
void		parse_plane(char **arr, t_info *info);
void		parse_cylinder(char **arr, t_info *info);
void		parse_cone(char **arr, t_info *info);
void		parse_bonus(char *str, t_info *info, t_texture *tex, \
			t_texture *bump);

#endif

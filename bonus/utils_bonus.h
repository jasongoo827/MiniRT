/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:37:17 by yakim             #+#    #+#             */
/*   Updated: 2024/04/24 19:18:19 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include "essential_bonus.h"
# include "object_bonus.h"

int		ft_strcmp(const char *s1, const char *s2);
int		is_spacetab(const char c);
int		ft_isspace(char c);
double	ft_strtod(const char *str);
char	**ft_split_rt(char const *s);
void	free_split(char **arr);
char	*remove_nl(char *line);
void	free_info(t_info *info);
void	free_arr(void *mlx, t_darray *darray);

#endif

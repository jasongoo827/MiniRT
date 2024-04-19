/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:37:17 by yakim             #+#    #+#             */
/*   Updated: 2024/04/19 11:56:53 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "essential.h"

int		ft_strcmp(const char *s1, const char *s2);
int		is_spacetab(const char c);
int		ft_isspace(char c);
double	ft_strtod(const char *str);
char	**ft_split_rt(char const *s);
void	free_split(char **arr);
char	*remove_nl(char *line);

#endif

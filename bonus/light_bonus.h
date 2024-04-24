/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoo <jgoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:58:21 by yakim             #+#    #+#             */
/*   Updated: 2024/04/24 14:30:22 by jgoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_BONUS_H
# define LIGHT_BONUS_H

# include "essential_bonus.h"
# include "object_bonus.h"

# define DIFFUSE 1
# define SPECULAR 0.7
# define SHINE 16

t_vector	phong_lightning(t_info *info);

#endif
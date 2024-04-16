/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakim <yakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:58:21 by yakim             #+#    #+#             */
/*   Updated: 2024/04/16 17:33:54 by yakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "essential.h"
# include "object.h"

# define DIFFUSE 1
# define SPECULAR 0.7
# define SHINE 16

t_vector	phong_lightning(t_info *info);

#endif
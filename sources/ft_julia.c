/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mandelbrot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 14:13:17 by bede-fre          #+#    #+#             */
/*   Updated: 2018/03/08 16:15:00 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void ft_init_val1_julia(t_values *val)
{
	val->fract.x1 = -1.0;
	val->fract.x2 = 1.0;
	val->fract.y1 = -1.2;
	val->fract.y2 = 1.2;
	val->fract.i_max = 150.0;
	val->fract.x = -1.0;
	val->fract.img_x = (val->fract.x2 - val->fract.x1) * val->draw.zoom;
	val->fract.img_y = (val->fract.y2 - val->fract.y1) * val->draw.zoom;
}

static void ft_init_val2_julia(t_values *val)
{
	val->fract.c_r = 0.285;
    val->fract.c_i = 0.01;
	val->fract.i = -1;
	val->fract.z_r = (val->fract.x / val->draw.zoom) + val->fract.x1;
	val->fract.z_i = (val->fract.y / val->draw.zoom) + val->fract.y1;
}

void	ft_julia(t_values *val)
{
	ft_init_val1_julia(val);
    while (++(val->fract.x) < val->fract.img_x)
	{
		val->fract.y = -1;
		while (++(val->fract.y) < val->fract.img_y)
		{
	        ft_init_val2_julia(val);
			while (((val->fract.z_r * val->fract.z_r)
                + (val->fract.z_i * val->fract.z_i)) < 4.0
                && (++(val->fract.i) < (val->fract.i_max)))
			{
				val->fract.tp = val->fract.z_r;
				val->fract.z_r = (val->fract.z_r * val->fract.z_r)
                    - (val->fract.z_i * val->fract.z_i) + val->fract.c_r;
				val->fract.z_i = (2.0 * val->fract.z_i * val->fract.tp)
                    + val->fract.c_i;
			}
			if (val->fract.i == val->fract.i_max)
				ft_fill_px(val, (val->fract.x + val->draw.var_x), (val->fract.y + val->draw.var_y), 0);
			else
				ft_fill_px(val, (val->fract.x + val->draw.var_x), (val->fract.y + val->draw.var_y), (val->fract.i * 255) / val->fract.i_max);
		}
	}
}
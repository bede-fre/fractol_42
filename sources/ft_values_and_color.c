/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_values_and_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 17:23:23 by bede-fre          #+#    #+#             */
/*   Updated: 2019/01/24 16:32:24 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_values(t_values *val)
{
	if (val->choice == MANDELBROT || val->choice == TRICORN)
	{
		val->fct.x1 = -2.1;
		val->fct.x2 = 1.1;
		val->fct.y1 = -1.2;
		val->fct.y2 = 1.2;
		val->fct.i_max = 50.0;
	}
	if (val->choice == JULIA)
	{
		val->fct.x1 = -1.6;
		val->fct.x2 = 1.6;
		val->fct.y1 = -1.2;
		val->fct.y2 = 1.2;
		val->fct.i_max = 150.0;
	}
	if (val->choice == BURNING_SHIP)
	{
		val->fct.x1 = -2.0;
		val->fct.x2 = 1.2;
		val->fct.y1 = -1.7;
		val->fct.y2 = 0.7;
		val->fct.i_max = 50.0;
	}
	val->draw.zoom = 250.0;
}

int			ft_color(t_values *val)
{
	val->red = 0;
	val->green = 0;
	val->blue = 0;
	if (val->set == BLACK_AND_WHITE)
	{
		val->red = (255 - (int)(val->fct.i * 255.0 / val->fct.i_max));
		val->green = (255 - (int)(val->fct.i * 255.0 / val->fct.i_max));
		val->blue = (255 - (int)(val->fct.i * 255.0 / val->fct.i_max));
	}
	if (val->set == RED)
		val->red = (int)(val->fct.i * 255.0 / val->fct.i_max);
	if (val->set == GREEN)
		val->green = (int)(val->fct.i * 255.0 / val->fct.i_max);
	if (val->set == BLUE)
		val->blue = (int)(val->fct.i * 255.0 / val->fct.i_max);
	if (val->set == PSYCHEDELIC)
		val->blue = (int)(val->fct.i * 255.0) * (val->fct.i_max);
	if (val->set == WHITE_AND_BLACK)
	{
		val->red = (int)(val->fct.i * 255.0 / val->fct.i_max);
		val->green = (int)(val->fct.i * 255.0 / val->fct.i_max);
		val->blue = (int)(val->fct.i * 255.0 / val->fct.i_max);
	}
	return (val->red << 16 | val->green << 8 | val->blue);
}

void		ft_fill_px(t_values *val, int x, int y, int color)
{
	int		px;

	px = (x * (val->draw.bpp) / 8) + (y * val->draw.sz_ln_px);
	if (px < 0 || x >= (val->draw.w_win) || y >= (val->draw.l_win) ||
	x < 0 || y < 0)
		return ;
	val->draw.s_px[px] = (unsigned char)(color);
	val->draw.s_px[px + 1] = (unsigned char)(color >> 8);
	val->draw.s_px[px + 2] = (unsigned char)(color >> 16);
	val->draw.s_px[px + 3] = (unsigned char)(color >> 24);
}

void		ft_str_fct(t_values *val)
{
	if (val->choice == MANDELBROT)
		mlx_string_put(val->draw.mlx, val->draw.win, 685, 10, 0xFF0000,
		"Mandelbrot");
	if (val->choice == JULIA)
		mlx_string_put(val->draw.mlx, val->draw.win, 735, 10, 0xFF0000,
		"Julia");
	if (val->choice == BURNING_SHIP)
		mlx_string_put(val->draw.mlx, val->draw.win, 665, 10, 0xFF0000,
		"Burning_ship");
	if (val->choice == TRICORN)
		mlx_string_put(val->draw.mlx, val->draw.win, 715, 10, 0xFF0000,
		"Tricorn");
}

void		ft_choice_fct(t_values *val)
{
	if (val->choice == MANDELBROT)
		ft_mandelbrot(val);
	if (val->choice == JULIA)
		ft_julia(val);
	if (val->choice == BURNING_SHIP)
		ft_burning_ship(val);
	if (val->choice == TRICORN)
		ft_tricorn(val);
	mlx_put_image_to_window(val->draw.mlx, val->draw.win, val->draw.img, 0, 0);
	ft_str_fct(val);
}

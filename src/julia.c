/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 14:10:41 by ngrasset          #+#    #+#             */
/*   Updated: 2017/07/30 16:17:20 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

static void		draw_pixel(t_app *app, int x, int y, int iter)
{
	int		color;

	if (iter == (int)app->ctx.max_iter)
		color = 0xFF;
	else
		color = iter * 255 / app->ctx.max_iter;
	*(app->image.data + (x + (WIN_WIDTH * y))) = (int)mlx_get_color_value(app->mlx, color);
	/* int		color; */

	/* if (iter == (int)app->ctx.max_iter) */
	/* 	color = 0x0000FF; */
	/* else */
	/* 	color = 0; */ 
	/* *(app->image.data + (x + (WIN_WIDTH * y))) = (int)mlx_get_color_value(app->mlx, color); */
}

void			julia(t_app *app, int x, int y)
{
	double		c_re = 0.285;
	double		c_im = 0.01;
	double		z_re = (x / app->ctx.zoom) + app->ctx.min_re;
	double 		z_im = (y / app->ctx.zoom) + app->ctx.min_im;
	int			n = 0;

	while (n < app->ctx.max_iter)
	{
		double		tmp = z_re;
		z_re = (z_re * z_re) - (z_im * z_im) + c_re;
		z_im = 2 * z_im * tmp + c_im;
		n++;
		if ((z_re * z_re) + (z_im * z_im) >= 4)
			break ;
	}
	draw_pixel(app, x, y, n);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 14:10:41 by ngrasset          #+#    #+#             */
/*   Updated: 2017/11/11 14:05:49 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

static void		draw_pixel(t_app *app, int x, int y, int iter)
{
	int		color;

	if (iter == (int)app->ctx.max_iter)
		color = 0xFF;
	else if (app->ctx.palette == BLUE)
		color = iter * 0xFF / app->ctx.max_iter;
	else if (app->ctx.palette == PSYCHO)
		color = iter * 0xFFFFFF / app->ctx.max_iter;
	else
		color = 0;
	*(app->image.data + (x + (WIN_WIDTH * y))) = (int)mlx_get_color_value(app->mlx, color);
}

void			julia(t_app *app)
{
	double		c_re = app->ctx.julia_params.x;
	double		c_im = app->ctx.julia_params.y;

	int		x;
	int		y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			/* double		z_re = (x / app->ctx.zoom) + app->ctx.min_re; */
			/* double 		z_im = (y / app->ctx.zoom) + app->ctx.min_im; */
			double z_re = 1.5 * (double)(x - WIN_WIDTH / 2.0f) / (double)(0.5f * app->ctx.zoom * WIN_WIDTH) + app->ctx.offset.x;
    		double z_im = (y - WIN_HEIGHT / 2.0f) / (0.5f * app->ctx.zoom * WIN_HEIGHT) + app->ctx.offset.y;
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
			x++;
		}
		y++;
	}
}

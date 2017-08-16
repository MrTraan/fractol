/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mendeleiev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 16:36:40 by ngrasset          #+#    #+#             */
/*   Updated: 2017/08/16 16:03:04 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

static void		draw_pixel(t_app *app, int x, int y, int iter)
{
	int		color;

	if (iter == (int)app->ctx.max_iter)
		color = 0;
	else
		color = iter * 255 / app->ctx.max_iter;
	*(app->image.data + (x + (WIN_WIDTH * y))) = (int)mlx_get_color_value(app->mlx, color);
}

void		mendeleiev_iter(double *cur_im, double *cur_re,
					double c_re, double c_im)
{
	double tmp_im;

	tmp_im = *cur_im;

	*cur_im = 2 * *cur_re * *cur_im + c_im;
	*cur_re = (*cur_re * *cur_re) - (tmp_im * tmp_im) + c_re;
}

void			mendeleiev(t_app *app, int x, int y)
{
	double			c_re;
	double			c_im;
	int				n;
	
	c_re = app->ctx.min_re + x * app->ctx.re_factor;
	c_im = app->ctx.max_im - y * app->ctx.im_factor;

	double Z_re = c_re, Z_im = c_im;
	n = 0;
	while (n < app->ctx.max_iter)
	{
		double Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
		if(Z_re2 + Z_im2 > 4)
			break ;
		Z_im = 2*Z_re*Z_im + c_im;
		Z_re = Z_re2 - Z_im2 + c_re;
		n++;
	}
	draw_pixel(app, x, y, n);
}

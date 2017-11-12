/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 14:13:11 by ngrasset          #+#    #+#             */
/*   Updated: 2017/11/12 17:17:03 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <math.h>

t_dv2		map_point_in_plan(t_app *app, t_iv2 point)
{
	t_dv2	res;

	res.x = 1.5 * (double)(point.x - WIN_WIDTH / 2.0f) /
		(double)(0.5f * app->ctx.zoom * WIN_WIDTH) + app->ctx.offset.x;
	res.y = (double)(point.y - WIN_HEIGHT / 2.0f) /
		(0.5f * app->ctx.zoom * WIN_HEIGHT) + app->ctx.offset.y;
	return (res);
}

void		draw_pixel(t_app *app, t_iv2 point, int iter)
{
	int		color;

	if (iter == (int)app->ctx.max_iter && app->drawing_func == &mandelbrot)
		color = 0;
	else if (app->ctx.palette == BLUE)
		color = 0xFF * pow(((double)iter / app->ctx.max_iter), 0.8);
	else if (app->ctx.palette == GREEN)
		color = (iter * 0xFF / app->ctx.max_iter) << 8;
	else if (app->ctx.palette == RED)
		color = (iter * 0xFF / app->ctx.max_iter) << 16;
	else if (app->ctx.palette == PSYCHO)
		color = iter * 0xFFFFFF / app->ctx.max_iter;
	else
		color = 0;
	*(app->image.data + (point.x + (WIN_WIDTH * point.y))) =
		(int)mlx_get_color_value(app->mlx, color);
}

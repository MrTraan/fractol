/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 16:59:02 by ngrasset          #+#    #+#             */
/*   Updated: 2017/11/12 20:13:46 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <math.h>

void	julia(t_app *app, t_iv2 coord)
{
	t_dv2		z;
	int			n;
	double		tmp;

	z = map_point_in_plan(app, coord);
	n = 0;
	while (n < app->ctx.max_iter)
	{
		tmp = z.x;
		z.x = (z.x * z.x) - (z.y * z.y) + app->ctx.julia_params.x;
		z.y = 2 * z.y * tmp + app->ctx.julia_params.y;
		n++;
		if ((z.x * z.x) + (z.y * z.y) >= 4)
			break ;
	}
	draw_pixel(app, coord, n);
}

void	mandelbrot(t_app *app, t_iv2 coord)
{
	t_dv2			point;
	t_dv2			new;
	t_dv2			old;
	int				n;

	point = map_point_in_plan(app, coord);
	new = (t_dv2) { .x = 0.0f, .y = 0.0f };
	old = (t_dv2) { .x = 0.0f, .y = 0.0f };
	n = 0;
	while (n < app->ctx.max_iter)
	{
		old.x = new.x;
		old.y = new.y;
		new.x = old.x * old.x - old.y * old.y + point.x;
		new.y = 2 * old.x * old.y + point.y;
		if ((new.x * new.x + new.y * new.y) > 4)
			break ;
		n++;
	}
	draw_pixel(app, coord, n);
}

void	burning_ship(t_app *app, t_iv2 coord)
{

    int      n;
    t_dv2 c;
	t_dv2 old;
    t_dv2 new;

	old.x = 0;
	old.y = 0;
	c.x = app->ctx.offset.x + 2 * 1 / app->ctx.zoom * (coord.x / (double)WIN_WIDTH - 0.5);
	c.y = app->ctx.offset.y + 2 * 1 / app->ctx.zoom * (coord.y / (double)WIN_HEIGHT - 0.5);
    n = 0;
	while (n < app->ctx.max_iter)
    {
		new.x = old.x*old.x - old.y*old.y + c.x;
		new.y = 2 * fabs(old.x*old.y) + c.y;
		old.x = new.x;
		old.y = new.y;
		if (new.x*new.x + new.y*new.y > 10)
			break;
        n++;
	}
	draw_pixel(app, coord, n);
}

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

void	julia(t_app *app, t_iv2 point)
{
	t_dv2		z;
	int			n;
	double		tmp;

	z = map_point_in_plan(app, point);
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
	draw_pixel(app, point, n);
}

void	mandelbrot(t_app *app, t_iv2 iter)
{
	t_dv2			point;
	t_dv2			new;
	t_dv2			old;
	int				n;

	point = map_point_in_plan(app, iter);
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
	draw_pixel(app, iter, n);
}

void	burning_ship(t_app *app, t_iv2 iter)
{
	t_dv2 midpoint = { .x = app->ctx.offset.x, .y = app->ctx.offset.y };
	double range = 1 / app->ctx.zoom;
	int itermax = app->ctx.max_iter;

	t_dv2 p0, c, p;
	p0.x = 0;
	p0.y = 0;
	c.x = midpoint.x + 2 * range * (iter.x / (double)WIN_WIDTH - 0.5);
	c.y = midpoint.y + 2 * range * (iter.y / (double)WIN_HEIGHT - 0.5);
	int k;
	for (k=0;k<itermax;k++) {
		p.x = p0.x*p0.x - p0.y*p0.y + c.x;
		p.y = 2 * fabs(p0.x*p0.y) + c.y;
		p0.x = p.x;
		p0.y = p.y;
		if (p.x*p.x + p.y*p.y > 10)
			break;
	}
	/* while (n < app->ctx.max_iter) */
	/* { */
	/* 	old.x = new.x; */
	/* 	old.y = new.y; */
	/* 	new.x = old.x * old.x - old.y * old.y + point.x; */
	/* 	new.y = 2 * old.x * old.y + point.y; */
	/* 	if ((new.x * new.x + new.y * new.y) > 4) */
	/* 		break ; */
	/* 	n++; */
	/* } */
	draw_pixel(app, iter, k);
}

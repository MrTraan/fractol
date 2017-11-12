/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 14:10:41 by ngrasset          #+#    #+#             */
/*   Updated: 2017/11/12 16:36:31 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

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

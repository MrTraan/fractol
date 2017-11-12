/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mendeleiev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 16:36:40 by ngrasset          #+#    #+#             */
/*   Updated: 2017/11/12 16:22:21 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void			mendeleiev(t_app *app, t_iv2 iter)
{
	t_dv2			point;

	point = map_point_in_plan(app, iter);

	double newRe, newIm, oldRe, oldIm;
	newRe = newIm = oldRe = oldIm = 0;
	int n = 0;
	while (n < app->ctx.max_iter)
	{
		oldRe = newRe;
		oldIm = newIm;
		newRe = oldRe * oldRe - oldIm * oldIm + point.x;
		newIm = 2 * oldRe * oldIm + point.y;
		//if the point is outside the circle with radius 2: stop
		if((newRe * newRe + newIm * newIm) > 4) break;
		n++;
	}
	draw_pixel(app, iter, n);
}

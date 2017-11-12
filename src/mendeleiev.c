/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mendeleiev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 16:36:40 by ngrasset          #+#    #+#             */
/*   Updated: 2017/11/12 16:39:33 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void			mendeleiev(t_app *app, t_iv2 iter)
{
	t_dv2			point;
	int				n;
	t_dv2			new;
	t_dv2			old;

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

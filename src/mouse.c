/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 16:26:40 by ngrasset          #+#    #+#             */
/*   Updated: 2017/11/12 16:34:10 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int			mouse_down(int button, int x, int y, t_app *app)
{
	if (button == 1 && x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_WIDTH)
		app->mouse_down = 1;
	return (0);
}

int			mouse_up(int button, int x, int y, t_app *app)
{
	(void)button;
	(void)x;
	(void)y;
	app->mouse_down = 0;
	return (0);
}

int			motion_notify(int x, int y, t_app *app)
{
	app->cursor_pos = (t_iv2) { .x = x, .y = y };
	if (app->drawing_func != &julia)
		return (0);
	if (app->lock_julia == 0)
	{
		app->ctx.julia_params = (t_dv2) {
			.x = (double)(x % WIN_WIDTH) / WIN_WIDTH * 2.0f - 1.0f,
			.y = (double)(y % WIN_HEIGHT) / WIN_HEIGHT * 2.0f - 1.0f
		};
	}
	main_draw_loop(app);
	return (0);
}

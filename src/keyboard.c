/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 18:22:27 by ngrasset          #+#    #+#             */
/*   Updated: 2017/07/29 18:32:48 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

static void		handle_zoom(int keycode, t_app *app)
{
	(void)keycode;
	(void)app;
}


static void		handle_movement(int keycode, t_app *app)
{
	if (keycode == KEY_UP)
	{
		app->ctx.max_im -= 0.1;
		app->ctx.min_im -= 0.1;
	}
	if (keycode == KEY_DOWN)
	{
		app->ctx.max_im += 0.1;
		app->ctx.min_im += 0.1;
	}
	if (keycode == KEY_RIGHT)
	{
		app->ctx.max_re -= 0.1;
		app->ctx.min_re -= 0.1;
	}
	if (keycode == KEY_LEFT)
	{
		app->ctx.max_re += 0.1;
		app->ctx.min_re += 0.1;
	}
}
#include <stdio.h>
int				keyhook(int keycode, t_app *app)
{
	printf("Keycode is: %d\n", keycode);
	if (keycode == 53)
		exit(0);
	handle_zoom(keycode, app);
	handle_movement(keycode, app);
	app->ctx.re_factor = (app->ctx.max_re - app->ctx.min_re) * app->ctx.zoom / (WIN_WIDTH - 1);
	app->ctx.im_factor = (app->ctx.max_im - app->ctx.min_im) * app->ctx.zoom / (WIN_HEIGHT - 1);
	main_draw_loop(app);
	return (0);
}


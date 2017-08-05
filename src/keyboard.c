/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 18:22:27 by ngrasset          #+#    #+#             */
/*   Updated: 2017/07/30 17:19:57 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

static void		handle_zoom(int keycode, t_app *app)
{
	if (keycode == KEY_MINUS && app->ctx.max_iter > 5)
		app->ctx.max_iter -= 5;
	if (keycode == KEY_PLUS)
		app->ctx.max_iter += 5;
	if (keycode == KEY_ZOOM_OUT && app->ctx.zoom >= 2)
		app->ctx.zoom /= 2;
	if (keycode == KEY_ZOOM_IN)
		app->ctx.zoom *= 2;
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

static void		switch_fractol(int keycode, t_app *app)
{
	if (keycode == KEY_1)
	{
		app->drawing_func = &mendeleiev;
		init_drawing_ctx(app);
	}
	if (keycode == KEY_2)
	{
		app->drawing_func = &julia;
		init_drawing_ctx(app);
	}
}

#include <stdio.h>
int				keyhook(int keycode, t_app *app)
{
	printf("Keycode is: %d\n", keycode);
	if (keycode == 53)
		exit(0);
	if (keycode == KEY_RESET)
		init_drawing_ctx(app);
	handle_zoom(keycode, app);
	handle_movement(keycode, app);
	switch_fractol(keycode, app);
	app->ctx.re_factor = (app->ctx.max_re - app->ctx.min_re) * app->ctx.zoom / (WIN_WIDTH - 1);
	app->ctx.im_factor = (app->ctx.max_im - app->ctx.min_im) * app->ctx.zoom / (WIN_HEIGHT - 1);
	main_draw_loop(app);
	return (0);
}

int			mouse_hook(int button, int x, int y, t_app *app)
{
	(void)app;
	printf("x: %d\ty: %d\tbutton: %d\n", x, y, button);
	return (0);
}

int         motion_notify(int x, int y, t_app *app)
{
    app->ctx.cursor_pos_x = x;
    app->ctx.cursor_pos_y = y;
    main_draw_loop(app);
    return (0);
}

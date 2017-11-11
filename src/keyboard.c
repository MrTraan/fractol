/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 18:22:27 by ngrasset          #+#    #+#             */
/*   Updated: 2017/11/11 14:21:04 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <stdio.h>
static void		handle_zoom(int keycode, t_app *app)
{
	t_iv2	screen_middle;

	if (keycode == KEY_MINUS && app->ctx.max_iter > 5)
		app->ctx.max_iter -= 5;
	if (keycode == KEY_PLUS)
		app->ctx.max_iter += 5;
	if (keycode == KEY_ZOOM_OUT && app->ctx.zoom >= 0.0001)
		app->ctx.zoom /= 1.05f;
	if (keycode == KEY_ZOOM_IN)
		app->ctx.zoom *= 1.05f;
	if (keycode == KEY_ZOOM_OUT || keycode == KEY_ZOOM_IN)
	{
		screen_middle = (t_iv2) { .x = WIN_WIDTH / 2, .y = WIN_HEIGHT / 2 };
		t_dv2 point_under_cursor = map_point_in_plan(app, app->cursor_pos);
		t_dv2 point_in_middle = map_point_in_plan(app, screen_middle);

		app->ctx.offset.x -= point_in_middle.x - point_under_cursor.x;
		app->ctx.offset.y -= point_in_middle.y - point_under_cursor.y;
	}
}


static void		handle_movement(int keycode, t_app *app)
{
	if (keycode == KEY_UP)
		app->ctx.offset.y += 0.1f / app->ctx.zoom;
	if (keycode == KEY_DOWN)
		app->ctx.offset.y -= 0.1 / app->ctx.zoom;
	if (keycode == KEY_LEFT)
		app->ctx.offset.x += 0.1 / app->ctx.zoom;
	if (keycode == KEY_RIGHT)
		app->ctx.offset.x -= 0.1 / app->ctx.zoom;
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
	if (keycode == KEY_Q)
		app->ctx.palette = BLUE;
	if (keycode == KEY_W)
		app->ctx.palette = PSYCHO;
}

#include <stdio.h>
int				keyhook(int keycode, t_app *app)
{
	printf("Keycode is: %d\n", keycode);
	if (keycode == 53)
		exit(0);
	if (keycode == KEY_RESET)
		init_drawing_ctx(app);
	if (keycode == KEY_SPACE)
		app->lock_julia = app->lock_julia ? 0 : 1;
	handle_zoom(keycode, app);
	handle_movement(keycode, app);
	switch_fractol(keycode, app);
	main_draw_loop(app);
	return (0);
}

int			mouse_hook(int button, int x, int y, t_app *app)
{
	(void)app;
	printf("x: %d\ty: %d\tbutton: %d\n", x, y, button);
	/* if (button == 1) */
	/* 	app->mouse_infos[0] = !app->mouse_infos[0]; */
	return (0);
}

int         motion_notify(int x, int y, t_app *app)
{
		app->cursor_pos.x = x;
		app->cursor_pos.y = y;

		if (app->lock_julia == 0)
		{
			app->ctx.julia_params.x = (double)(x % WIN_WIDTH) / WIN_WIDTH * 2.0f - 1.0f;
			app->ctx.julia_params.y = (double)(y % WIN_HEIGHT) / WIN_HEIGHT * 2.0f - 1.0f;
		}

		main_draw_loop(app);
	return (0);
}

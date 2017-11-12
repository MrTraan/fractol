/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 14:05:43 by ngrasset          #+#    #+#             */
/*   Updated: 2017/11/12 19:07:27 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

t_ctx		g_default_ctx[3] = {
	{
		{-0.75, 0},
		{0, 0},
		1.0,
		30,
		BLUE
	},
	{
		{0, 0},
		{0, 0},
		1.0,
		40,
		RED
	},
	{
		{0, 0},
		{0, 0},
		1.0,
		50,
		GREEN
	},
};

int		main_draw_loop(t_app *app)
{
	mt_draw_fractal(app);
	mlx_put_image_to_window(app->mlx, app->win, app->image.ptr, 0, 0);
	return (0);
}

void	init_drawing_ctx(t_app *app)
{
	if (app->drawing_func == &mandelbrot)
		ft_memcpy(&(app->ctx), &(g_default_ctx[0]), sizeof(t_ctx));
	else if (app->drawing_func == &julia)
		ft_memcpy(&(app->ctx), &(g_default_ctx[1]), sizeof(t_ctx));
	else if (app->drawing_func == &burning_ship)
		ft_memcpy(&(app->ctx), &(g_default_ctx[2]), sizeof(t_ctx));
	else
		ft_memset(&(app->ctx), 0, sizeof(t_ctx));
}

int		loop_hook(t_app *app)
{
	if (app->mouse_down)
	{
		app->ctx.zoom *= 1.05f;
		zoom(app);
		main_draw_loop(app);
	}
	return (0);
}

int		main(void)
{
	t_app		app;

	ft_memset(&app, 0, sizeof(t_app));
	app.drawing_func = &mandelbrot;
	app.mlx = mlx_init();
	app.win = mlx_new_window(app.mlx, WIN_WIDTH, WIN_HEIGHT, "fractol");
	mlx_expose_hook(app.win, main_draw_loop, &app);
	app.image.ptr = mlx_new_image(app.mlx, WIN_WIDTH, WIN_HEIGHT);
	app.image.data = (int *)mlx_get_data_addr(app.image.ptr, app.image.infos,
			app.image.infos + 1, app.image.infos + 2);
	init_drawing_ctx(&app);
	mlx_key_hook(app.win, keyhook, &app);
	mlx_hook(app.win, MOTION_NOTIFY, PTR_MOTION_MASK, motion_notify, &app);
	mlx_hook(app.win, BUTTON_PRESS, BUTTON1_MOTION_MASK, mouse_down, &app);
	mlx_hook(app.win, BUTTON_RELEASE, BUTTON1_MOTION_MASK, mouse_up, &app);
	mlx_loop_hook(app.mlx, loop_hook, &app);
	main_draw_loop(&app);
	mlx_loop(app.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 14:05:43 by ngrasset          #+#    #+#             */
/*   Updated: 2017/11/04 15:50:33 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

t_ctx		g_default_ctx[2] = {
	{
		-2.0,
		1.0,
		-1.2,
		1.2,
		1,
		30,
		BLUE
	},
	{
		-1.5,
		0.5,
		-1.2,
		1.2,
		256,
		75,
		BLUE
	}
};

void	put_settings(t_app *app)
{
	char	*max_iter;
	char	*zoom;
	char	buffer[100];

	ft_memset(buffer, 0, 100);
	max_iter = ft_itoa(app->ctx.max_iter);
	ft_strlcat(buffer, "max iter: ", 100);
	ft_strlcat(buffer, max_iter, 100);
	mlx_string_put(app->mlx, app->win, 0, 0, 0xFFFFFF, buffer);
	free(max_iter);
	ft_memset(buffer, 0, 100);
	zoom = ft_itoa(app->ctx.zoom);
	ft_strlcat(buffer, "zoom: ", 100);
	ft_strlcat(buffer, zoom, 100);
	mlx_string_put(app->mlx, app->win, 0, 12, 0xFFFFFF, buffer);
	free(zoom);
}

int		main_draw_loop(t_app *app)
{
	int		x;
	int		y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			app->drawing_func(app, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(app->mlx, app->win, app->image.ptr, 0, 0);
	put_settings(app);
	ft_putstr("Image displayed\n");
	return (0);
}

void	init_drawing_ctx(t_app *app)
{
	if (app->drawing_func == &mendeleiev)
		ft_memcpy(&(app->ctx), &(g_default_ctx[0]), sizeof(t_ctx));
	else if (app->drawing_func == &julia)
		ft_memcpy(&(app->ctx), &(g_default_ctx[1]), sizeof(t_ctx));
	else
		ft_memset(&(app->ctx), 0, sizeof(t_ctx));
}

int		main(void)
{
	t_app		app;

	ft_memset(&app, 0, sizeof(t_app));
	app.drawing_func = &mendeleiev;

	app.mlx = mlx_init();
	app.win = mlx_new_window(app.mlx, WIN_WIDTH, WIN_HEIGHT, "fractol");
	mlx_expose_hook(app.win, main_draw_loop, &app);
	app.image.ptr = mlx_new_image(app.mlx, WIN_WIDTH, WIN_HEIGHT);
	app.image.data = (int *)mlx_get_data_addr(app.image.ptr, app.image.infos,
			app.image.infos + 1, app.image.infos + 2);
	init_drawing_ctx(&app);
	mlx_key_hook(app.win, keyhook, &app);
	mlx_mouse_hook(app.win, mouse_hook, &app);
	mlx_hook(app.win, MOTION_NOTIFY, PTR_MOTION_MASK, motion_notify, &app);
	main_draw_loop(&app);
	mlx_loop(app.mlx);
	return (0);
}

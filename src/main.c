/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 14:05:43 by ngrasset          #+#    #+#             */
/*   Updated: 2017/07/30 17:20:42 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

t_ctx		g_default_ctx[2] = {
	{
		-2.0,
		1.0,
		-1.2,
		1.2,
		0,
		0,
		1,
		30
	},
	{
		-1.5,
		0.5,
		-1.2,
		1.2,
		0,
		0,
		256,
		150
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
	app->ctx.re_factor = (app->ctx.max_re - app->ctx.min_re) * app->ctx.zoom / (WIN_WIDTH - 1);
	app->ctx.im_factor = (app->ctx.max_im - app->ctx.min_im) * app->ctx.zoom / (WIN_HEIGHT - 1);
}

int		main(void)
{
	t_app		app;

	app.drawing_func = &mendeleiev;

	app.mlx = mlx_init();
	app.win = mlx_new_window(app.mlx, WIN_WIDTH, WIN_HEIGHT, "fractol");
	app.image.ptr = mlx_new_image(app.win, WIN_WIDTH, WIN_HEIGHT);
	app.image.data = (int *)mlx_get_data_addr(app.image.ptr, app.image.infos,
			app.image.infos + 1, app.image.infos + 2);
	init_drawing_ctx(&app);
	main_draw_loop(&app);
	mlx_key_hook(app.win, keyhook, &app);
	mlx_mouse_hook(app.win, mouse_hook, &app);
	mlx_expose_hook(app.win, main_draw_loop, &app);
	mlx_loop(app.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 14:05:43 by ngrasset          #+#    #+#             */
/*   Updated: 2017/07/29 18:31:16 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	draw_pixel(t_app *app, int x, int y, int iter)
{
	int		color;

	if (iter == (int)app->ctx.max_iter)
		color = 0;
	else
		color = iter * 255 / app->ctx.max_iter;
	*(app->image.data + (x + (WIN_WIDTH * y))) = (int)mlx_get_color_value(app->mlx, color);
}

int		main_draw_loop(t_app *app)
{
	int		x;
	int		y;
	int		iter;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			iter = app->ctx.drawing_func(app->ctx, x, y);
			draw_pixel(app, x, y, iter);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(app->mlx, app->win, app->image.ptr, 0, 0);
	ft_putstr("Image displayed\n");
	return (0);
}

void	init_drawing_ctx(t_ctx *ctx)
{
	ctx->min_re = -2.0;
	ctx->max_re = 1.0;
	ctx->min_im = -1.2;
	ctx->max_im = 1.2;
	ctx->zoom = 1;
	ctx->re_factor = (ctx->max_re - ctx->min_re) * ctx->zoom / (WIN_WIDTH - 1);
	ctx->im_factor = (ctx->max_im - ctx->min_im) * ctx->zoom / (WIN_HEIGHT - 1);
	ctx->drawing_func = &mendeleiev;
	ctx->max_iter = 30;
}

int		main(void)
{
	t_app		app;

	app.mlx = mlx_init();
	app.win = mlx_new_window(app.mlx, WIN_WIDTH, WIN_HEIGHT, "fractol");
	app.image.ptr = mlx_new_image(app.win, WIN_WIDTH, WIN_HEIGHT);
	app.image.data = (int *)mlx_get_data_addr(app.image.ptr, app.image.infos,
			app.image.infos + 1, app.image.infos + 2);
	init_drawing_ctx(&(app.ctx));
	main_draw_loop(&app);
	mlx_key_hook(app.win, keyhook, &app);
	mlx_expose_hook(app.win, main_draw_loop, &app);
	mlx_loop(app.mlx);
	return (0);
}

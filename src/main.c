/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 14:05:43 by ngrasset          #+#    #+#             */
/*   Updated: 2017/11/05 17:29:34 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

t_ctx		g_default_ctx[2] = {
	{
		-2.0,
		1.0,
		-1.2,
		1.2,
		1.0,
		30,
		0,
		0,
		BLUE
	},
	{
		-1.5,
		0.5,
		-1.2,
		1.2,
		1,
		75,
		0,
		0,
		BLUE
	}
};
#include<stdio.h>
void	put_settings(t_app *app)
{
	char	*max_iter;
	char	buffer[100];
		
	t_iv2 cursor = {
			app->mouse_infos[1],
			app->mouse_infos[2]
		};
		t_dv2 point_under_cursor = {
			1.5 * (double)(cursor.x - WIN_WIDTH / 2.0f) / (double)(0.5f * app->ctx.zoom * WIN_WIDTH) + app->ctx.offset_x,
			(cursor.y - WIN_HEIGHT / 2.0f) / (0.5f * app->ctx.zoom * WIN_HEIGHT) + app->ctx.offset_y
		};
		t_dv2 point_in_middle = {
			1.5 * (double)(WIN_WIDTH / 2.0f - WIN_WIDTH / 2.0f) / (double)(0.5f * app->ctx.zoom * WIN_WIDTH) + app->ctx.offset_x,
			(WIN_HEIGHT / 2.0f - WIN_HEIGHT / 2.0f) / (0.5f * app->ctx.zoom * WIN_HEIGHT) + app->ctx.offset_y
		};

	ft_memset(buffer, 0, 100);
	max_iter = ft_itoa(app->ctx.max_iter);
	ft_strlcat(buffer, "max iter: ", 100);
	ft_strlcat(buffer, max_iter, 100);
	mlx_string_put(app->mlx, app->win, 0, 0, 0xFFFFFF, buffer);
	free(max_iter);
	ft_memset(buffer, 0, 100);
	sprintf(buffer, "zoom: %f\n", app->ctx.zoom);
	mlx_string_put(app->mlx, app->win, 0, 12, 0xFFFFFF, buffer);

	sprintf(buffer, "Mouse: %d %d\n", cursor.x, cursor.y);
	mlx_string_put(app->mlx, app->win, 0, 24, 0xFFFFFF, buffer);

	sprintf(buffer, "Point under cursor: %f %f\n", point_under_cursor.x, point_under_cursor.y);
	mlx_string_put(app->mlx, app->win, 0, 36, 0xFFFFFF, buffer);
	
	sprintf(buffer, "Point in middle: %f %f\n", point_in_middle.x, point_in_middle.y);
	mlx_string_put(app->mlx, app->win, 0, 48, 0xFFFFFF, buffer);

	sprintf(buffer, "Offset: %f %f\n", app->ctx.offset_x, app->ctx.offset_y);
	mlx_string_put(app->mlx, app->win, 0, 60, 0xFFFFFF, buffer);
}

int		main_draw_loop(t_app *app)
{
	app->drawing_func(app);
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

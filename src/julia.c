/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 14:10:41 by ngrasset          #+#    #+#             */
/*   Updated: 2017/11/11 17:23:55 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

static void		draw_pixel(t_app *app, int x, int y, int iter)
{
	int		color;

	if (iter == (int)app->ctx.max_iter)
		color = 0xFF;
	else if (app->ctx.palette == BLUE)
		color = iter * 0xFF / app->ctx.max_iter;
	else if (app->ctx.palette == PSYCHO)
		color = iter * 0xFFFFFF / app->ctx.max_iter;
	else
		color = 0;
	*(app->image.data + (x + (WIN_WIDTH * y))) = (int)mlx_get_color_value(app->mlx, color);
}

static void iter(t_app *app, int x, int y)
{
	double		c_re = app->ctx.julia_params.x;
	double		c_im = app->ctx.julia_params.y;
	double z_re = 1.5 * (double)(x - WIN_WIDTH / 2.0f) / (double)(0.5f * app->ctx.zoom * WIN_WIDTH) + app->ctx.offset.x;
	double z_im = (y - WIN_HEIGHT / 2.0f) / (0.5f * app->ctx.zoom * WIN_HEIGHT) + app->ctx.offset.y;
	int			n = 0;
	while (n < app->ctx.max_iter)
	{
		double		tmp = z_re;
		z_re = (z_re * z_re) - (z_im * z_im) + c_re;
		z_im = 2 * z_im * tmp + c_im;
		n++;
		if ((z_re * z_re) + (z_im * z_im) >= 4)
			break ;
	}
	draw_pixel(app, x, y, n);
}

static void *first_quarter(void *v_app)
{
	int		x;
	int		y;

	t_app * app = (t_app *)v_app;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH / 2)
		{
			iter(app, x, y);
			x++;
		}
		y++;
	}
	return (NULL);
}

static void *second_quarter(void *v_app)
{
	int		x;
	int		y;
	t_app * app = (t_app *)v_app;

	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH / 2)
		{
			iter(app, x, y);
			x++;
		}
		y++;
	}
	return (NULL);
}

static void *third_quarter(void *v_app)
{
	int		x;
	int		y;
	t_app * app = (t_app *)v_app;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = WIN_WIDTH / 2;
		while (x < WIN_WIDTH)
		{
			iter(app, x, y);
			x++;
		}
		y++;
	}
	return (NULL);
}

static void *fourth_quarter(void *v_app)
{
	int		x;
	int		y;
	t_app * app = (t_app *)v_app;

	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		x = WIN_WIDTH / 2;
		while (x < WIN_WIDTH)
		{
			iter(app, x, y);
			x++;
		}
		y++;
	}
	return (NULL);
}

void			julia(t_app *app)
{
	struct timeval  tv1, tv2;
	gettimeofday(&tv1, NULL);
	pthread_t tid1;
	pthread_t tid2;
	pthread_t tid3;
    pthread_create(&tid1, NULL, first_quarter, app);
    pthread_create(&tid2, NULL, second_quarter, app);
    pthread_create(&tid3, NULL, third_quarter, app);
	fourth_quarter(app);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
	gettimeofday(&tv2, NULL);
	printf ("Total time = %f msec\n",
			 (double) (tv2.tv_usec - tv1.tv_usec) / 1000);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 16:14:42 by ngrasset          #+#    #+#             */
/*   Updated: 2017/11/12 18:56:04 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <pthread.h>

static void		*first_quarter(void *v_app)
{
	t_iv2	iter;
	t_app	*app;

	app = (t_app *)v_app;
	iter.y = 0;
	while (iter.y < WIN_HEIGHT / 2)
	{
		iter.x = 0;
		while (iter.x < WIN_WIDTH / 2)
		{
			app->drawing_func(app, iter);
			iter.x++;
		}
		iter.y++;
	}
	return (NULL);
}

static void		*second_quarter(void *v_app)
{
	t_iv2	iter;
	t_app	*app;

	app = (t_app *)v_app;
	iter.y = WIN_HEIGHT / 2;
	while (iter.y < WIN_HEIGHT)
	{
		iter.x = 0;
		while (iter.x < WIN_WIDTH / 2)
		{
			app->drawing_func(app, iter);
			iter.x++;
		}
		iter.y++;
	}
	return (NULL);
}

static void		*third_quarter(void *v_app)
{
	t_iv2	iter;
	t_app	*app;

	app = (t_app *)v_app;
	iter.y = 0;
	while (iter.y < WIN_HEIGHT / 2)
	{
		iter.x = WIN_WIDTH / 2;
		while (iter.x < WIN_WIDTH)
		{
			app->drawing_func(app, iter);
			iter.x++;
		}
		iter.y++;
	}
	return (NULL);
}

static void		*fourth_quarter(void *v_app)
{
	t_iv2	iter;
	t_app	*app;

	app = (t_app *)v_app;
	iter.y = WIN_HEIGHT / 2;
	while (iter.y < WIN_HEIGHT)
	{
		iter.x = WIN_WIDTH / 2;
		while (iter.x < WIN_WIDTH)
		{
			app->drawing_func(app, iter);
			iter.x++;
		}
		iter.y++;
	}
	return (NULL);
}

void			mt_draw_fractal(t_app *app)
{
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
}

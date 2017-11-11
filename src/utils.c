/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 14:13:11 by ngrasset          #+#    #+#             */
/*   Updated: 2017/11/11 14:16:56 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

t_dv2		map_point_in_plan(t_app *app, t_iv2 point)
{
	t_dv2	res;

	res.x = 1.5 * (double)(point.x - WIN_WIDTH / 2.0f) /
		(double)(0.5f * app->ctx.zoom * WIN_WIDTH) + app->ctx.offset.x;
	res.y = (double)(point.y - WIN_HEIGHT / 2.0f) /
		(0.5f * app->ctx.zoom * WIN_HEIGHT) + app->ctx.offset.y;
	return (res);
}

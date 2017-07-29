/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mendeleiev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 16:36:40 by ngrasset          #+#    #+#             */
/*   Updated: 2017/07/29 16:54:19 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	mendeleiev_iter(double *cur_im, double *cur_re, double c_re, double c_im)
{
	double tmp_im;

	tmp_im = *cur_im;

	*cur_im = 2 * *cur_re * *cur_im + c_im;
	*cur_re = (*cur_re * *cur_re) - (tmp_im * tmp_im) + c_re;
}

int		mendeleiev(t_ctx ctx, int x, int y)
{
	double			c_re;
	double			c_im;
	int				n;

	c_im = ctx.max_im - y * ctx.im_factor;
	c_re = ctx.min_re + x * ctx.re_factor;

	double Z_re = c_re, Z_im = c_im;
	n = 0;
	while (n < ctx.max_iter)
	{
		double Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
		if(Z_re2 + Z_im2 > 4)
			return (n);
		Z_im = 2*Z_re*Z_im + c_im;
		Z_re = Z_re2 - Z_im2 + c_re;
		n++;
	}
	return (n);
}

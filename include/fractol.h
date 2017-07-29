/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 14:10:55 by ngrasset          #+#    #+#             */
/*   Updated: 2017/07/29 18:32:01 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <libft.h>
# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>

# define WIN_HEIGHT 600
# define WIN_WIDTH 800

# define KEY_UP 126
# define KEY_DOWN 125 
# define KEY_RIGHT 124 
# define KEY_LEFT 123 

typedef struct		s_image
{
	void			*ptr;
	int				*data;
	int				infos[3];
}					t_image;

typedef struct		s_ctx
{
	double			min_re;
	double			max_re;
	double			min_im;
	double			max_im;
	double			re_factor;
	double			im_factor;
	double			zoom;
	int				max_iter;
	int				(*drawing_func)(struct s_ctx, int, int);
}					t_ctx;

typedef struct		s_app
{
	void			*mlx;
	void			*win;
	t_image			image;
	t_ctx			ctx;
}					t_app;

typedef int			(*t_drawing_func)(t_ctx, int, int);

int					main_draw_loop(t_app *app);

int					mendeleiev(t_ctx ctx, int x, int y);

int					keyhook(int keycode, t_app *app);

#endif

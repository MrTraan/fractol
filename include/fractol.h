/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 14:10:55 by ngrasset          #+#    #+#             */
/*   Updated: 2017/07/30 17:20:10 by ngrasset         ###   ########.fr       */
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
# define KEY_MINUS 27
# define KEY_PLUS 24
# define KEY_RESET 15
# define KEY_1 18
# define KEY_2 19
# define KEY_ZOOM_OUT 33
# define KEY_ZOOM_IN 30

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
}					t_ctx;

typedef struct		s_app
{
	void			*mlx;
	void			*win;
	t_image			image;
	t_ctx			ctx;
	void			(*drawing_func)(struct s_app *, int, int);
}					t_app;

typedef void		(*t_drawing_func)(t_app *, int, int);

int					main_draw_loop(t_app *app);
void				init_drawing_ctx(t_app *app);

void				mendeleiev(t_app *app, int x, int y);
void				julia(t_app *app, int x, int y);

int					keyhook(int keycode, t_app *app);
int					mouse_hook(int button, int x, int y, t_app *app);

#endif

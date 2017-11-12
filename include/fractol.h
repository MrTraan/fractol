/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */ /*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 14:10:55 by ngrasset          #+#    #+#             */
/*   Updated: 2017/11/04 15:50:03 by ngrasset         ###   ########.fr       */
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
# define KEY_RESET 51
# define KEY_1 18
# define KEY_2 19
# define KEY_ZOOM_OUT 33
# define KEY_ZOOM_IN 30
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_SPACE 49

# define PTR_MOTION_MASK (1L<<6)
# define BUTTON1_MOTION_MASK (1L<<8)
# define BUTTON_PRESS 4
# define BUTTON_RELEASE 5
# define MOTION_NOTIFY 6

# define MAX(x, y) x > y ? y : x

typedef enum		e_palette
{
	BLUE,
	GREEN,
	RED,
	PSYCHO
}					t_palette;

typedef struct 		s_iv2
{
	int				x;
	int				y;
}					t_iv2;

typedef struct 		s_dv2
{
	double			x;
	double			y;
}					t_dv2;


typedef struct		s_image
{
	void			*ptr;
	int				*data;
	int				infos[3];
}					t_image;

typedef struct		s_ctx
{
	t_dv2			re;
	t_dv2			im;
	t_dv2			offset;
	t_dv2			julia_params;
	double			zoom;
	int				max_iter;
	t_palette		palette;
}					t_ctx;

typedef struct		s_app
{
	void			*mlx;
	void			*win;
	t_image			image;
	t_ctx			ctx;
	void			(*drawing_func)(struct s_app *, t_iv2 coord);
	t_iv2			cursor_pos;
	char			lock_julia;
	char			mouse_down;
}					t_app;

typedef void		(*t_drawing_func)(t_app *, t_iv2 coord);

int					main_draw_loop(t_app *app);
void				init_drawing_ctx(t_app *app);

void				mt_draw_fractal(t_app *app);
void				mendeleiev(t_app *app, t_iv2 coord);
void				julia(t_app *app, t_iv2 coord);

int					keyhook(int keycode, t_app *app);
int					mouse_hook(int button, int x, int y, t_app *app);
int                 motion_notify(int x, int y, t_app *app);
void				zoom(t_app *app);
int					mouse_down(int button, int x, int y, t_app *app);
int					mouse_up(int button, int x, int y, t_app *app);

t_dv2				map_point_in_plan(t_app *app, t_iv2 point);
void				draw_pixel(t_app *app, t_iv2 point, int iter);

#endif

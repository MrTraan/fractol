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
# define KEY_RESET 15
# define KEY_1 18
# define KEY_2 19
# define KEY_ZOOM_OUT 33
# define KEY_ZOOM_IN 30
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15

# define PTR_MOTION_MASK (1L<<6)
# define MOTION_NOTIFY 6

typedef enum		e_palette
{
	BLUE,
	PSYCHO
}					t_palette;

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
	double			zoom;
	int				max_iter;
	double			offset_x;
	double			offset_y;
	t_palette		palette;
}					t_ctx;

typedef struct		s_app
{
	void			*mlx;
	void			*win;
	t_image			image;
	t_ctx			ctx;
	void			(*drawing_func)(struct s_app *);
	int 			mouse_infos[3];
}					t_app;

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

typedef void		(*t_drawing_func)(t_app *);

int					main_draw_loop(t_app *app);
void				init_drawing_ctx(t_app *app);

void				mendeleiev(t_app *app);
void				julia(t_app *app);

int					keyhook(int keycode, t_app *app);
int					mouse_hook(int button, int x, int y, t_app *app);
int                 motion_notify(int x, int y, t_app *app);

#endif

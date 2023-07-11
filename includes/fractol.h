/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:48:31 by lsalin            #+#    #+#             */
/*   Updated: 2022/10/27 10:53:58 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "libft.h"
# include "keys.h"
# include <stdio.h>
# include <math.h>

# define WIDTH 900
# define HEIGHT 900
# define MAX_ITERATIONS 60

# define MANDELBROT 1
# define JULIA 2
# define BURNING_SHIP 3

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*buffer;
	int		*palette;
	int		color_pattern;
	int		color;
	int		set;
	double	min_r;
	double	max_r;
	double	min_i;
	double	max_i;
	double	kr;
	double	ki;

}	t_data;

// Sets functions Mandelbrot & Burning ship functions 
int			mandelbrot(double cr, double ci);
int			burning_ship(double cr, double ci);
int			julia(t_data *f, double zr, double zi);
int			julia_shift(int x, int y, t_data *f);

// Fractals draw functions
void		draw_fractal(t_data *f);

// Initialisation functions
void		default_init(t_data *f);
void		define_dimensions_sides(t_data *f);
void		reinit_img(t_data *f);
void		init(t_data *f);

// Colors functions
void		mono_color_pattern(t_data *f, int color);
void		various_color_pattern(t_data *f, int colors[4], int n);
void		shift(t_data *f);

// Events functions
int			handle_key_events(int keycode, t_data *mlx);
int			handle_mouse_events(int keycode, int x, int y, t_data *mlx);

// Launch messages functions
void		print_fractal_options(void);
void		print_color_options(void);
void		print_controls(void);
void		helping_msg(t_data *f);

// Argcs functions
double		ft_atoi_float(char *str);
void		get_color(t_data *f, int argc, char **argv);

// Utils functions
void		free_and_exit(int exit_code, t_data *f);
int			exit_exe(t_data *mlx);
int			error_msg(char *str1, char *str2, int errno);
int			ft_isspace(int c);
int			ft_ishexdigit(int c);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:48:31 by lsalin            #+#    #+#             */
/*   Updated: 2022/10/27 11:17:04 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	default_init(t_data *f)
{
	f->mlx = NULL;
	f->win = NULL;
	f->img = NULL;
	f->buffer = NULL;
	f->set = -1;
	f->min_r = 0;
	f->max_r = 0;
	f->min_i = 0;
	f->max_i = 0;
	f->kr = 0;
	f->ki = 0;
	f->palette = NULL;
	f->color_pattern = -1;
	f->color = 0;
}

// Define complex scheme dimensions

void	define_dimensions_sides(t_data *f)
{
	if (f->set == JULIA)
	{
		f->min_r = -2.0;
		f->max_r = 2.0;
		f->min_i = -2.0;
		f->max_i = f->min_i + (f->max_r - f->min_r) * HEIGHT / WIDTH;
	}
	else
	{
		f->min_r = -2.0;
		f->max_r = 1.0;
		f->max_i = -1.5;
		f->min_i = f->max_i + (f->max_r - f->min_r) * HEIGHT / WIDTH;
	}
}

/*
	Initializes an image of the MLX as well as a color palette
	The color palette is an array where each element corresponds to a shade of color
	And each element is associated with an iteration number
	Each pixel color is stored in the image which is then displayed
*/

static void	init_img(t_data *f)
{
	char	*buffer;
	int		bits_per_pixels;
	int		line_length;
	int		endian;

	f->palette = ft_calloc((MAX_ITERATIONS + 1), sizeof(int));
	if (!(f->palette))
		free_and_exit(error_msg("error initializing color scheme.", "", 1), f);
	f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	if (!(f->img))
		free_and_exit(error_msg("image creation error.", "", 1), f);
	buffer = mlx_get_data_addr(f->img, &bits_per_pixels, &line_length, &endian);
	f->buffer = buffer;
}

/*
	Cleans up the MLX image if the color palette or
	the type of fractal is modified during execution
*/

void	reinit_img(t_data *f)
{
	if (f->mlx && f->img)
		mlx_destroy_image(f->mlx, f->img);
	if (f->palette)
		free(f->palette);
	if (f->buffer)
		f->buffer = NULL;
	init_img(f);
}

/*
	Init MLX and a window, build the complex scheme and shift colors
	shift() is called each time the user presses the space key
*/

void	init(t_data *f)
{
	f->mlx = mlx_init();
	if (!f->mlx)
		free_and_exit(error_msg("MLX: error connecting to mlx.", "", 1), f);
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "Fractol");
	if (!f->win)
		free_and_exit(error_msg("MLX: error creating window.", "", 1), f);
	define_dimensions_sides(f);
	shift(f);
}

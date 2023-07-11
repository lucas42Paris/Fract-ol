/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_fractals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:48:31 by lsalin            #+#    #+#             */
/*   Updated: 2022/10/26 15:36:52 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
	Fills a pixel of RGB
	The 4 bytes monopolized by a pixel are spread over an array
	The array is filled with the colors
*/

static void	set_pixel_color(t_data *f, int x, int y, int color)
{
		f->buffer[x * 4 + y * WIDTH * 4] = color;
		f->buffer[x * 4 + y * WIDTH * 4 + 1] = color >> 8;
		f->buffer[x * 4 + y * WIDTH * 4 + 2] = color >> 16;
		f->buffer[x * 4 + y * WIDTH * 4 + 3] = color >> 24;
}

/*
	Get the number of iterations of each set of fractals
	Then return this number
*/

static int	define_iter_sets(t_data *f, double pr, double pi)
{
	int	nb_iter;

	if (f->set == MANDELBROT)
		nb_iter = mandelbrot(pr, pi);
	else if (f->set == JULIA)
		nb_iter = julia(f, pr, pi);
	else if (f->set == BURNING_SHIP)
		nb_iter = burning_ship(pr, pi);
	return (nb_iter);
}

/*
	Iterate on the coordinates of each pixel in the window to calculate
	the complex number of each pixel
	The number of iterations this complex number goes through before 
	being rejected from the set determines the color applied to the pixel
	cr = real part of the complex number of a pixel
	ci = imaginary part of the complex number of a pixel
*/

void	draw_fractal(t_data *f)
{
	int		x;
	int		y;
	double	pr;
	double	pi;
	int		nb_iter;

	mlx_clear_window(f->mlx, f->win);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			pr = f->min_r + (double)x * (f->max_r - f->min_r) / WIDTH;
			pi = f->max_i + (double)y * (f->min_i - f->max_i) / HEIGHT;
			nb_iter = define_iter_sets(f, pr, pi);
			set_pixel_color(f, x, y, f->palette[nb_iter]);
		}
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}

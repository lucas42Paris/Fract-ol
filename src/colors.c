/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:48:31 by lsalin            #+#    #+#             */
/*   Updated: 2022/10/25 15:00:54 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
	Interpolation between two hexadecimal color codes
	Is used to obtain the intermediate color between two colors (gradient)
	rgb[0] = red, rgb[1] = green, rgb[2] = blue
	Return the hexa code of the interpolated color
*/

static int	interpolate(int startcolor, int endcolor, double fraction)
{
	int	start_rgb[3];
	int	end_rgb[3];

	start_rgb[0] = ((startcolor >> 16) & 0xFF);
	start_rgb[1] = ((startcolor >> 8) & 0xFF);
	start_rgb[2] = ((startcolor >> 0) & 0xFF);
	end_rgb[0] = ((endcolor >> 16) & 0xFF);
	end_rgb[1] = ((endcolor >> 8) & 0xFF);
	end_rgb[2] = ((endcolor >> 0) & 0xFF);
	start_rgb[0] = (end_rgb[0] - start_rgb[0]) * fraction + start_rgb[0];
	start_rgb[1] = (end_rgb[1] - start_rgb[1]) * fraction + start_rgb[1];
	start_rgb[2] = (end_rgb[2] - start_rgb[2]) * fraction + start_rgb[2];
	return (0xFF << 24 | start_rgb[0] << 16 | start_rgb[1] << 8 | start_rgb[2]);
}

/*
	Defines a monochrome color scheme
	Colors range from black to color supplied white near fractal border
*/

void	mono_color_pattern(t_data *f, int color)
{
	int		i;
	int		j;
	int		color1;
	int		color2;
	double	fraction;

	color1 = 0x000000;
	color2 = color;
	i = 0;
	while (i < MAX_ITERATIONS)
	{
		j = 0;
		while (j < MAX_ITERATIONS / 2)
		{
			fraction = (double)j / (MAX_ITERATIONS / 2);
			f->palette[i + j] = interpolate(color1, color2, fraction);
			j++;
		}
		color1 = color2;
		color2 = 0xFFFFFF;
		i += j;
	}
}

/*
	Defines a multicolored color scheme
	Colors range from the first color provided in the chart to the last
	color interpolation for a smooth transition between each
*/

void	various_color_pattern(t_data *f, int colors[4], int n)
{
	int		i;
	int		j;
	int		x;
	double	fraction;

	i = 0;
	x = 0;
	while (i < MAX_ITERATIONS)
	{
		j = 0;
		while ((i + j) < MAX_ITERATIONS && j < (MAX_ITERATIONS / (n - 1)))
		{
			fraction = (double)j / (MAX_ITERATIONS / (n - 1));
			f->palette[i + j] = interpolate(colors[x], colors[x + 1], fraction);
			j++;
		}
		x++;
		i += j;
	}
}

// Reset the MLX image and shift the color pattern

void	shift(t_data *f)
{
	int	alt_color;

	f->color_pattern = (f->color_pattern + 1) % 2;
	reinit_img(f);
	alt_color = f->color;
	if (f->color_pattern == 0)
		mono_color_pattern(f, alt_color);
	else if (f->color_pattern == 1)
		various_color_pattern(f, (int [4]){0x000000, 0xFFFFFF, \
										alt_color, 0x660033}, 4);
}

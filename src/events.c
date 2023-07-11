/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:48:31 by lsalin            #+#    #+#             */
/*   Updated: 2022/10/27 11:04:22 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
	Resizing the complex scheme by multiplying the real and imaginary axis 
	by the appropriate multiplier (x0.5 = zoom in ; x2.0 = zoom out)
	Then recalculate the fractal with the new dimensions
*/

static void	zoom(t_data *f, double zoom)
{
	double	center_r_axis;
	double	center_i_axis;

	center_r_axis = f->min_r - f->max_r;
	center_i_axis = f->max_i - f->min_i;
	f->max_r = f->max_r + (center_r_axis - zoom * center_r_axis) / 2;
	f->min_r = f->max_r + zoom * center_r_axis;
	f->min_i = f->min_i + (center_i_axis - zoom * center_i_axis) / 2;
	f->max_i = f->min_i + zoom * center_i_axis;
}

// Adjust real and imaginary axis values ​​for up/down/left/right movement

static void	move(t_data *f, double distance, char direction)
{
	double	center_r_axis;
	double	center_i_axis;

	center_r_axis = f->max_r - f->min_r;
	center_i_axis = f->max_i - f->min_i;
	if (direction == 'R')
	{
		f->min_r += center_r_axis * distance;
		f->max_r += center_r_axis * distance;
	}
	else if (direction == 'L')
	{
		f->min_r -= center_r_axis * distance;
		f->max_r -= center_r_axis * distance;
	}
	else if (direction == 'D')
	{
		f->min_i -= center_i_axis * distance;
		f->max_i -= center_i_axis * distance;
	}
	else if (direction == 'U')
	{
		f->min_i += center_i_axis * distance;
		f->max_i += center_i_axis * distance;
	}
}

/*
	Change fractal depending on the keyboard key pressed
	1 --> Mandelbrot
	2 --> Julia
	3--> Burning ship
	The parameters of the fractal are then adjusted and the set is redrawn
*/

static int	handle_key_events_extend(int keycode, t_data *mlx)
{
	if (keycode == KEY_ONE && mlx->set != MANDELBROT)
		mlx->set = MANDELBROT;
	else if (keycode == KEY_TWO && mlx->set != JULIA)
		mlx->set = JULIA;
	else if (keycode == KEY_THREE && mlx->set != BURNING_SHIP)
		mlx->set = BURNING_SHIP;
	else
		return (1);
	define_dimensions_sides(mlx);
	draw_fractal(mlx);
	return (0);
}

int	handle_key_events(int keycode, t_data *mlx)
{
	if (keycode == KEY_ESC)
	{
		exit_exe(mlx);
		return (0);
	}
	else if (keycode == KEY_PLUS)
		zoom(mlx, 0.5);
	else if (keycode == KEY_MINUS)
		zoom(mlx, 2);
	else if (keycode == KEY_UP)
		move(mlx, 0.2, 'U');
	else if (keycode == KEY_DOWN)
		move(mlx, 0.2, 'D');
	else if (keycode == KEY_LEFT)
		move(mlx, 0.2, 'L');
	else if (keycode == KEY_RIGHT)
		move(mlx, 0.2, 'R');
	else if (keycode == KEY_SPACE)
		shift(mlx);
	else if (!handle_key_events_extend(keycode, mlx))
		return (1);
	else
		return (1);
	draw_fractal(mlx);
	return (0);
}

int	handle_mouse_events(int keycode, int x, int y, t_data *mlx)
{
	if (keycode == MOUSE_WHEEL_UP)
	{
		zoom(mlx, 0.5);
		x -= WIDTH / 2;
		y -= HEIGHT / 2;
		if (x < 0)
			move(mlx, (double)x * -1 / WIDTH, 'L');
		else if (x > 0)
			move(mlx, (double)x / WIDTH, 'R');
		if (y < 0)
			move(mlx, (double)y * -1 / HEIGHT, 'U');
		else if (y > 0)
			move (mlx, (double)y / HEIGHT, 'D');
	}
	else if (keycode == MOUSE_WHEEL_DOWN)
		zoom(mlx, 2);
	else if (keycode == MOUSE_BTN)
	{
		if (mlx->set == JULIA)
			julia_shift(x, y, mlx);
	}
	else
		return (0);
	draw_fractal(mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_msgs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:48:31 by lsalin            #+#    #+#             */
/*   Updated: 2022/10/27 11:04:25 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_fractal_options(void)
{
	ft_putendl_fd("M - Mandelbrot", 1);
	ft_putendl_fd("J - Julia", 1);
	ft_putendl_fd("B - Burning Ship", 1);
	ft_putendl_fd("\e[36m./fractol <type>\n./fractol M\e[0m", 1);
	ft_putstr_fd("\nFor Julia set : specify starting values", 1);
	ft_putstr_fd("\nValues must be between -2.0 & 2.0 ('.')\n", 1);
	ft_putendl_fd("\e[36m./fractol J", 1);
	ft_putendl_fd("./fractol J 0.285 0.01\n\e[0m", 1);
}

void	print_color_options(void)
{
	ft_putendl_fd("Customize the fractal by specifying a color code", 1);
	ft_putendl_fd("The hex color code must be formatted as RRGGBB", 1);
	ft_putstr_fd("\e[36m./fractol <type> <color>\n", 1);
	ft_putendl_fd("./fractol M 0066FF\e[0m", 1);
	ft_putendl_fd("\nFor Julia, you can only specify colors after", 1);
	ft_putendl_fd("the starting values", 1);
	ft_putendl_fd("\e[36m./fractol J 0.285 0.01 CC6600\e[0m", 1);
}

void	print_controls(void)
{
	ft_putendl_fd("WASD OR arrow keys\t\t= move", 1);
	ft_putendl_fd("+/- OR scroll wheel\t\t= zoom", 1);
	ft_putendl_fd("Spacebar\t\t\t= shift color", 1);
	ft_putendl_fd("Left click\t\t\t= shift Julia set", 1);
	ft_putendl_fd("1, 2, 3\t\t\t\t= switch fractal set", 1);
	ft_putendl_fd("ESC OR close window\t\t= exit program", 1);
}

void	helping_msg(t_data *f)
{
	print_fractal_options();
	print_color_options();
	free_and_exit(EXIT_FAILURE, f);
}

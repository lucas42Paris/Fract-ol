/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <lsalin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:48:31 by lsalin            #+#    #+#             */
/*   Updated: 2023/07/11 11:49:23 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
	Convert argcs to lowercase if entered in uppercase
	Returns true if the argument matches the expected syntax, otherwise false
*/

static int	parse_argcs(char *argv, char *str, char c, char n)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		argv[i] = ft_tolower(argv[i]);
		i++;
	}
	if (!ft_strncmp(argv, str, ft_strlen(str) + 1))
		return (1);
	else if (argv[1] == '\0' && (argv[0] == c || argv[0] == n))
		return (1);
	return (0);
}

static void	attribute_set(t_data *f, char **argv)
{
	if (parse_argcs(argv[1], "mandelbrot", 'm', '1'))
		f->set = MANDELBROT;
	else if (parse_argcs(argv[1], "julia", 'j', '2'))
		f->set = JULIA;
	else if (parse_argcs(argv[1], "burning ship", 'b', '3'))
		f->set = BURNING_SHIP;
	else
		helping_msg(f);
}

/*
	Assign values ​​to kr and ki for Julia if they were omitted by the user
	Then parse the provided values: check if ".", convert the argc to float 
	and if between -2.0 and 2.0
*/

static void	starting_values_julia(t_data *f, int argc, char **argv)
{
	if (f->set != JULIA || argc == 2)
	{
		f->kr = -0.766667;
		f->ki = -0.090000;
		return ;
	}
	if (argc == 3)
		helping_msg(f);
	if (!ft_strchr(argv[2], '.'))
		helping_msg(f);
	if (!ft_strchr(argv[3], '.'))
		helping_msg(f);
	f->kr = ft_atoi_float(argv[2]);
	f->ki = ft_atoi_float(argv[3]);
	if (f->kr > 2.0 || f->kr < -2.0)
		helping_msg(f);
	if (f->ki >= 2.0 || f->ki <= -2.0)
		helping_msg(f);
}

// Get set, julia's seed values ​​and color from provided arguments

static void	handle_args(t_data *f, int argc, char **argv)
{
	attribute_set(f, argv);
	if (f->set != JULIA && argc > 3)
		helping_msg(f);
	else if (f->set == JULIA && argc > 5)
		helping_msg(f);
	starting_values_julia(f, argc, argv);
	get_color(f, argc, argv);
}

int	main(int argc, char **argv)
{
	t_data	f;

	if (argc < 2)
		helping_msg(&f);
	default_init(&f);
	handle_args(&f, argc, argv);
	init(&f);
	draw_fractal(&f);
	print_controls();
	mlx_hook(f.win, EVENT_CLOSE_BTN, 0, exit_exe, &f);
	mlx_key_hook(f.win, handle_key_events, &f);
	mlx_mouse_hook(f.win, handle_mouse_events, &f);
	mlx_loop(f.mlx);
}

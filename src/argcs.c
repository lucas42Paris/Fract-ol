/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalin <lsalin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:48:31 by lsalin            #+#    #+#             */
/*   Updated: 2023/07/11 11:48:55 by lsalin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
	Increment whil the char is a space, "+" or "-"
	Modifies the value of is_neg when a "-" sign is detected
	Use to parse strings of floats for Julia
*/

static int	skip_space_sign(char *str, int *is_neg)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*is_neg *= -1;
		i++;
	}
	return (i);
}

/*
	Increment while char is a space, "+", "0x" or "0X" 
	Returns hexadecimal code size
*/

static int	skip_space_sign_0x(char *color)
{
	int	i;

	i = 0;
	while (ft_isspace(color[i]))
		i++;
	if (color[i] == '+')
		i++;
	if (color[i] == '0' && (color[i + 1]
			&& (color[i + 1] == 'x' || color[i] == 'X')))
		i = i + 2;
	return (i);
}

/*
	Converts a string (hex color code) to an int
	Valid format: "RRGGBB", "OXRRGGBB", "rrggbb", "+rrggbb"
	Invalid format: "-RRGGBB", "RRGGBB-", RR GG BB"
*/

static int	ft_atoi_hexa(t_data *f, char *color)
{
	int	i;
	int	x;
	int	n;

	n = 0;
	i = 0;
	i = skip_space_sign_0x(color);
	x = 0;
	while (color[i] && ft_ishexdigit(color[i]))
	{
		if (ft_isdigit(color[i]))
			n = (n * 16) + (color[i] - '0');
		else
			n = (n * 16) + (ft_toupper(color[i]) - 'A' + 10);
		i++;
		x++;
	}
	if (x == 6 && !color[i])
		return (n);
	else
		helping_msg(f);
	return (-1);
}

/*
	Convert a string to a float 
	Used to parse the start value given to Julia on launch 
	Returns (-42) on error (Julia accepts values ​​between 2.0 and -2.0)
*/

double	ft_atoi_float(char *str)
{
	int		i;
	double	nb;
	int		is_neg;
	double	div;

	nb = 0;
	div = 0.1;
	is_neg = 1;
	i = skip_space_sign(str, &is_neg);
	while (str[i] && ft_isdigit(str[i]) && str[i] != '.')
	{
		nb = (nb * 10.0) + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		nb = nb + ((str[i] - '0') * div);
		div *= 0.1;
		i++;
	}
	if (str[i] && !ft_isdigit(str[i]))
		return (-42);
	return (nb * is_neg);
}

/*
	Retrieve the provided color option and convert the hex color code to int 
	A default value is set if the user does not specify any color
*/

void	get_color(t_data *f, int argc, char **argv)
{
	if (f->set == JULIA && argc == 5)
		f->color = ft_atoi_hexa(f, argv[4]);
	else if (f->set != JULIA && argc == 3)
		f->color = ft_atoi_hexa(f, argv[2]);
	if (argc == 2 || (f->set == JULIA && argc == 4))
		f->color = 0xFFCCE5;
}

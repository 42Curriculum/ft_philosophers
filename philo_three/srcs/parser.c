/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 14:43:19 by jjosephi          #+#    #+#             */
/*   Updated: 2020/04/22 14:43:20 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void num_check(char **arg)
{
	long long number;
	int i;

	i = 2;
	if ((__INT_MAX__ - ft_atol(arg[1])) < 0)
	{
		write(2, ERR_NMAX1, 41);
		exit(0);
	}
	while (arg[i])
	{
		number = ft_atol(arg[i]);
		if (number < 0)
		{
			write(2, ERR_NMAX2, 44);
			exit(0);
		}
		i++;
	}
}

void error_check(char **arg)
{
	int i;
	int n;

	i = 1;
	while (arg[i])
	{
		n = 0;
		if (arg[i][0] == '-')
		{
			write(1, ERR_NEG, 29);
			exit(0);
		}
		while (arg[i][n])
		{
			if (arg[i][n] < '0' || arg[i][n] > '9')
			{
				write(1, ERR_NONUM, 26);
				exit(0);
			}
			n++;
		}
		i++;
	}
}

void	parser(char **arg, int (*iargs)[], int argc)
{
	int i;

	i = 1;
	if (argc > 6 || argc < 5)
	{
		write(2, ERR_ARGC, 28);
		exit(0);
	}
	error_check(arg);
	while (arg[i])
	{
		(*iargs)[i -1] = ft_atol(arg[i]);
		i++;
	}
	if (i < 6)
		(*iargs)[4] = -1;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 14:42:53 by jjosephi          #+#    #+#             */
/*   Updated: 2020/05/06 05:12:14 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <sys/stat.h>   

int main(int argc, char **argv)
{
	int args[6];
	int i;
	int death;

	parser(argv, &args, argc);
	sem_close(sem_open("SEM_TWO", O_CREAT , S_IRWXO, args[0]));
	i = args[0];
	death = args[0];
	if (i == 0)
		exit(0);
	while (i > 0)
	{
		Spawn(args, &args[0], &death);
		i--;
	}
}
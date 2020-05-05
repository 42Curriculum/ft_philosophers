/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 14:42:53 by jjosephi          #+#    #+#             */
/*   Updated: 2020/05/05 03:58:45 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <sys/stat.h>   

int main(int argc, char **argv)
{
	pthread_t thread;
	sem_t *sem;
	int args[6];
	int i;
	int death;
	long time;

	parser(argv, &args, argc);
	sem = sem_open("SEM_TWO", O_CREAT , S_IRWXO, args[0]);
	i = 0;
	time = 0;
	pthread_create(&thread, NULL,time_ct, &time);
	i = args[0];
	death = args[0];
	sem_close(sem);
	while (i > 0)
	{
		Spawn(args, &time, &args[0], &death);
		i--;
	}
	while (death > 0);
}
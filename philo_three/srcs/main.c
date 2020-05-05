/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 14:42:53 by jjosephi          #+#    #+#             */
/*   Updated: 2020/05/05 02:07:21 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <sys/stat.h>   

int main(int argc, char **argv)
{
	sem_t *sem;
	pthread_t thread;
	int args[6];
	int i;
	long time;

	parser(argv, &args, argc);
	sem = sem_open("SEM_TWO", O_CREAT , S_IRWXO, args[0]);
	i = 0;
	time = 0;
	pthread_create(&thread, NULL,time_ct, &time);
	sem_close(sem);
	i = args[0];
	args[5] = args[0];
	while (i > 0)
	{
		Spawn(args, &time, &args[0], &args[5]);
		i--;
	}
	while (args[6] > 0);
}
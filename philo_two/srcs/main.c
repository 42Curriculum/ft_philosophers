/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 14:42:53 by jjosephi          #+#    #+#             */
/*   Updated: 2020/05/04 18:07:18 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <sys/stat.h>   

int main(int argc, char **argv)
{
	sem_t *sem;
	pthread_t thread;
	int args[6];
	int i;
	long time;

	i = 0;
	time = 0;
	parser(argv, &args, argc);
	pthread_create(&thread, NULL,time_ct, &time);
	sem = sem_open("SEM_TWO", O_CREAT , S_IRWXO, args[0]);
	//sem_close(sem);
	i = args[0];
	args[6] = args[0];
	while (i > 0)
	{
		Spawn(args, &time, sem, &args[0]);
		i--;
	}
	pthread_exit(NULL);
}
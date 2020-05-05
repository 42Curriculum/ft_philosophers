/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 14:42:53 by jjosephi          #+#    #+#             */
/*   Updated: 2020/05/04 21:25:43 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int main(int argc, char **argv)
{
	pthread_t thread;
	sem_t *sem;
	int args[6];
	int i;
	long time;

	i = 0;
	time = 0;
	parser(argv, &args, argc);
	sem = sem_open(SEM_NAME, O_CREAT, 0x0002, args[0]);
	sem_close(sem);
	pthread_create(&thread, NULL,time_ct, &time);
	i = args[0];
	args[6] = args[0];
	while (i > 0)
	{
		Spawn(args, &time, &args[0]);
		i--;
	}
	pthread_exit(NULL);
}
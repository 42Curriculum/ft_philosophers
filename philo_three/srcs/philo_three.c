/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 03:05:50 by jjosephi          #+#    #+#             */
/*   Updated: 2020/05/05 22:37:22 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int ask_nicely(t_philosphers *phil)
{
	if (*phil->sem_val < 2)
		return (STARVE_PEASANT);
	*phil->sem_val -= 2;
	return (EAT_SIR);
}

void eat(t_philosphers *phil)
{
	pthread_t thread;
	sem_t *sem;

	sem = sem_open(SEM_NAME, O_RDWR);
	while (!ask_nicely(phil));
	sem_wait(sem);
	sem_wait(sem);
	phil->printvars[1] = -1;
	set_and_print(phil);
	set_and_print(phil);
	phil->printvars[1] = 0;
	do_stuff(phil, 2);
	pthread_create(&thread, NULL, life_cycle, phil);
	sem_post(sem);
	sem_post(sem);
	sem_close(sem);
	*phil->sem_val += 2;
	phil->printvars[1] = 2;
}

void philosopher(t_philosphers *phil, int *death)
{
	int i;
	pthread_t thread;

	i = 0;
	pthread_create(&thread, NULL, life_cycle, phil);
	pthread_create(&thread, NULL,time_ct, &phil->time);
	while (*phil->death > 0)
	{
		set_and_print(phil);
		eat(phil);
		if (phil->args[4] > 0)
		{
			i++;
			if (i >= phil->args[4])
			{
				printf("PHIL %d exited\n",phil->printvars[0]);
				*death -= 1;
				printf("Death %d exited\n",*death);
				exit(0);
			}
		}
		do_stuff(phil, 3);
		phil->printvars[1] = 1;
	}
	*phil->death = -1;
	exit(0);
}

void 	Spawn(int args[], int *sem_c, int *death)
{
	t_philosphers *phil;
	static int i;

	phil = (t_philosphers *)malloc(sizeof(t_philosphers));
	phil->printvars[0] = i;
	i++;
	phil->printvars[1] = 1;
	phil->death = death;
	phil->args = args;
	phil->time = 0;
	phil->sem_val = sem_c;
	if (fork() == 0)
		philosopher(phil, death);
}

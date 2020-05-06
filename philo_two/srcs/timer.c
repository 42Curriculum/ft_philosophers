/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 22:10:05 by jjosephi          #+#    #+#             */
/*   Updated: 2020/05/05 22:34:52 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <sys/time.h>

void *time_ct(void *var)
{
	struct timeval time;
	struct timeval time2;
	long *elapsed;

	elapsed = var;
	gettimeofday(&time, NULL);
	while (1)
	{
		gettimeofday(&time2, NULL);
		*elapsed = (((time2.tv_sec - time.tv_sec) * 1000) + ((time2.tv_usec - time.tv_usec) / 1000));
	}
}

void *life_cycle(void *arg)
{
	t_philosphers *phil;
	struct timeval time;
	struct timeval time2;
	long long elapsed;

	phil = arg;
	gettimeofday(&time, NULL);
	elapsed = 0;
	while (1)
	{
		gettimeofday(&time2, NULL);
		elapsed = (((time2.tv_sec - time.tv_sec) * 1000) + ((time2.tv_usec - time.tv_usec) / 1000));
		if (phil->args[1] <= elapsed)
		{
			phil->current = *phil->time;
			phil->printvars[1] = 3;
			set_and_print(phil);
			exit(0);
		}
		if (phil->printvars[1] == 0)
			pthread_exit(NULL);
	}
}

void do_stuff(t_philosphers *phil, int stuff)
{
	set_and_print(phil);
	usleep(phil->args[stuff] * 1000);
}

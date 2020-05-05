/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 14:43:15 by jjosephi          #+#    #+#             */
/*   Updated: 2020/05/05 02:05:25 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int main(int argc, char **argv)
{
	pthread_mutex_t	*mu;
	pthread_t thread;
	int args[6];
	int i;
	long time;

	i = 0;
	time = 0;
	parser(argv, &args, argc);
	pthread_create(&thread, NULL,time_ct, &time);
	mu = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t) * args[0]);
	args[5] = args[0];
	while (i < args[0])
	{
		pthread_mutex_init(&mu[i], NULL);
		Spawn(args, &time, &mu, i);
		i++;
	}
	pthread_exit(NULL);
}
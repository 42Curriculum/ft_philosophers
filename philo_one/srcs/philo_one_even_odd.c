#include "philo_one.h"

void grab_even(t_philosphers *phil)
{
	if (phil->printvars[0] % 2 == 0)
	{
		pthread_mutex_lock(&(phil->mu[phil->printvars[0]]));
		phil->printvars[1] = -1;
		set_and_print(phil);
		if (phil->printvars[0] == phil->args[0] - 1)
			pthread_mutex_lock(&(phil->mu[0]));
		else
			pthread_mutex_lock(&(phil->mu[phil->printvars[0] + 1]));
		set_and_print(phil);
	}
	else
	{
		if (phil->printvars[0] == phil->args[0] - 1)
			pthread_mutex_lock(&(phil->mu[0]));
		else
			pthread_mutex_lock(&(phil->mu[phil->printvars[0] + 1]));
		phil->printvars[1] = -1;
		set_and_print(phil);
		pthread_mutex_lock(&(phil->mu[phil->printvars[0]]));
		set_and_print(phil);
	}
}

void grab_odd(t_philosphers *phil)
{
	if (phil->printvars[0] % 2 != 0)
	{
		pthread_mutex_lock(&(phil->mu[phil->printvars[0]]));
		phil->printvars[1] = -1;
		set_and_print(phil);
		if (phil->printvars[0] == phil->args[0] - 1)
			pthread_mutex_lock(&(phil->mu[0]));
		else
			pthread_mutex_lock(&(phil->mu[phil->printvars[0] + 1]));
		set_and_print(phil);
	}
	else
	{
		if (phil->printvars[0] == phil->args[0] - 1)
			pthread_mutex_lock(&(phil->mu[0]));
		else
			pthread_mutex_lock(&(phil->mu[phil->printvars[0] + 1]));
		phil->printvars[1] = -1;
		set_and_print(phil);
		pthread_mutex_lock(&(phil->mu[phil->printvars[0]]));
		set_and_print(phil);
	}	
}

void eat_pair(t_philosphers *phil)
{
	if (phil->args[0]  % 2 == 0)
		grab_even(phil);
	else
		grab_odd(phil);
	phil->printvars[1] = 0;
	do_stuff(phil, 2);
	if (phil->printvars[0] == phil->args[0] - 1)
		pthread_mutex_unlock(&(phil->mu[0]));
	else
		pthread_mutex_unlock(&(phil->mu[phil->printvars[0] + 1]));
	pthread_mutex_unlock(&(phil->mu[phil->printvars[0]]));
	phil->printvars[1] = 2;
}

void *philosopher(void *arg)
{
	t_philosphers *phil;

	phil = arg;
	while (42)
	{
		set_and_print(phil);
		eat_pair(phil);
		do_stuff(phil, 3);
		phil->printvars[1] = 1;
	}
}

void 	Spawn(int args[], long *time, pthread_mutex_t **mu, int i)
{
	t_philosphers *phil;
	pthread_t thread;

	phil = (t_philosphers *)malloc(sizeof(t_philosphers));
	phil->printvars[0] = i;
	phil->printvars[1] = 1;
	phil->mu = *mu;
	phil->args = args;
	phil->time = time;
	phil->unlock[0] = i + 1;
	phil->unlock[1] = i;
	if (i == args[0] - 1)
	{
		phil->unlock[0] = i;
		phil->unlock[1] = 0;
	}
	pthread_create(&thread, NULL, philosopher, phil);
}

#include "philo_one.h"

void grab_fork(t_philosphers *phil)
{
	pthread_mutex_lock(&(phil->mu[phil->unlock[0]]));
	phil->printvars[1] = -1;
	set_and_print(phil);
	pthread_mutex_lock(&(phil->mu[phil->unlock[1]]));
	set_and_print(phil);
}

void eat(t_philosphers *phil)
{
	pthread_t thread;

	grab_fork(phil);
	phil->printvars[1] = 0;
	do_stuff(phil, 2);
	pthread_create(&thread, NULL, life_cycle, phil);
	pthread_mutex_unlock(&(phil->mu[phil->unlock[1]]));
	pthread_mutex_unlock(&(phil->mu[phil->unlock[0]]));
	phil->printvars[1] = 2;
}

void *philosopher(void *arg)
{
	int i;
	t_philosphers *phil;
	pthread_t thread;

	i = 0;
	phil = arg;
	pthread_create(&thread, NULL, life_cycle, phil);
	while (i != phil->args[4])
	{
		set_and_print(phil);
		eat(phil);
		pthread_create(&thread, NULL, life_cycle, phil);
		if (phil->args[4] > 0)
		{
			if (++i >= phil->args[4])
				break ;
		}
		do_stuff(phil, 3);
		phil->printvars[1] = 1;
	}
	if (++*phil->death >= phil->args[5])
		exit(0);
	pthread_exit(0);
}

void 	Spawn(int args[], long *time, pthread_mutex_t **mu, int i)
{
	t_philosphers *phil;
	pthread_t thread;
	static int death;

	phil = (t_philosphers *)malloc(sizeof(t_philosphers));
	phil->printvars[0] = i;
	phil->printvars[1] = 1;
	phil->mu = *mu;
	phil->args = args;
	phil->death = &death;
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

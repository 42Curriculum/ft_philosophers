#include "philo_one.h"

void grab_fork(t_philosphers *phil)
{
	pthread_mutex_lock(&(phil->mu[phil->unlock[0]]));
	phil->printvars[1] = -1;
	set_and_print(phil);
	pthread_mutex_lock(&(phil->mu[phil->unlock[1]]));
	set_and_print(phil);
}

// void grab_pairs(t_philosphers *phil)
// {
// 	if (phil->args[0]  % 2 == 0)
// 	{
// 		if (phil->printvars[0] % 2 == 0)
// 		{
// 			pthread_mutex_lock(&(phil->mu[phil->unlock[0]]));
// 			phil->printvars[1] = -1;
// 			set_and_print(phil);
// 			pthread_mutex_lock(&(phil->mu[phil->unlock[1]]));
// 			set_and_print(phil);
// 		}
// 	}
// }

void eat(t_philosphers *phil)
{
	grab_fork(phil);
	phil->printvars[1] = 0;
	do_stuff(phil, 2);
	pthread_mutex_unlock(&(phil->mu[phil->unlock[1]]));
	pthread_mutex_unlock(&(phil->mu[phil->unlock[0]]));
	phil->printvars[1] = 2;
}

void *philosopher(void *arg)
{
	t_philosphers *phil;

	phil = arg;
	printf("I am %d I unlock : %d\n", phil->printvars[0], phil->unlock[0]);
	while (42)
	{
		set_and_print(phil);
		eat(phil);
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

// // Pair take highest
// 1 - 2 - 1
// 2 
// 3 - 4 - 3
// 4 

// 1
// 2 - 2
// 3 
// 4 - 4
#include "philo_three.h"
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
		*elapsed = (((time2.tv_sec - time.tv_sec) * 1000000 - (time2.tv_usec - time.tv_usec))/ 1000);
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
		elapsed = (((time2.tv_sec - time.tv_sec) * 1000000 - (time2.tv_usec - time.tv_usec))/ 1000);
		if (phil->args[1] <= elapsed)
		{
			phil->current = *phil->time;
			phil->printvars[1] = 3;
			set_and_print(phil);
		}
		if (phil->printvars[1] == 0)
			pthread_exit(NULL);
	}
}

void do_stuff(t_philosphers *phil, int stuff)
{
	long i;
	
	i = 0;
	set_and_print(phil);
	while (i < phil->args[stuff])
	{
		usleep(1);
		i++;
	}
}
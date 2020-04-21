#include "philo_one.h"

int eat(t_philosphers *phil, int number, int *state)
{
	int next;
	pthread_t thread0;
	pthread_t thread1;

	next = 0;
	if (number < 1)
		next = number + 1;
	if (next == 0)
	{
		pthread_mutex_lock(&(phil->mu[next]));
		phil->current = *phil->time;
		pthread_create(&thread1, NULL, print_status, phil);
		pthread_create(&thread1, NULL, print_status, phil);
		pthread_mutex_lock(&(phil->mu[number]));
		phil->current = *phil->time;
		pthread_create(&thread1, NULL, print_status, phil);
	}
	else
	{	
		pthread_mutex_lock(&(phil->mu[number]));
		phil->current = *phil->time;
		pthread_create(&thread1, NULL, print_status, phil);
		pthread_create(&thread1, NULL, print_status, phil);
		pthread_mutex_lock(&(phil->mu[next]));
		phil->current = *phil->time;
		pthread_create(&thread0, NULL, print_status, phil);
	}
	*state = 0;
	do_stuff(phil, 2);
	pthread_mutex_unlock(&(phil->mu[next]));
	return (0);
}

void *phi_loop(void *arg)
{
	int state;//0 = sleeping, 1 = eating, 2 = thinking 3 = dead
	t_philosphers *phil;
	long elapsed;
	pthread_t cycle;

	state = -1;
	elapsed = 0;
	phil = arg;
	phil->state = &state;
	pthread_create(&cycle, NULL, life_cycle, phil);
	while (state != 3)
	{
		if (state == -1)
		{
			if (!eat(phil, phil->number, &state))
			{
				pthread_mutex_unlock(&(phil->mu[phil->number]));
				state = 2;
				elapsed = 0;
				pthread_create(&cycle, NULL, life_cycle, phil);
			}
		}
		else if (state == 2)
		{
			phil->current = *phil->time;
			pthread_create(&cycle, NULL, print_status, phil);
			do_stuff(phil, 3);
			state = -1;
		}
	}
	exit(0);
}

void 	Spawn(int args[], long *time, pthread_mutex_t **mu, int i)
{
	t_philosphers *phil;
	pthread_t thread;
	int number;

	phil = (t_philosphers *)malloc(sizeof(t_philosphers));
	phil->number = i;
	phil->mu = *mu;
	phil->pno = args[0];
	phil->args = args;
	phil->state = 0;
	phil->time = time;
	pthread_create(&thread, NULL, phi_loop, phil);
}

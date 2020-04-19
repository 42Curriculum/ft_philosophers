#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include "philosphers.h"

// Make print function (1 print statement)
// Parsing (# of phil, ttd, tteat, ttsleep, ttthink, # time to eat)

void *print_status(void *var)
{
	char *print;
	t_status *status;

	status = var;
	
	
}

void *life_cycle(void *arg)
{
	t_lifetime *life;
	struct timeval time;
	struct timeval time2;


	life = arg;
	gettimeofday(&time, NULL);
	//printf("Time is : %d", life->ttd);
	while (1)
	{
		if (life->ttd <= *life->elapsed)
		{
			*life->state = 3;
			pthread_exit(NULL);
		}
		else if (*life->state == 0)
			pthread_exit(NULL);
		gettimeofday(&time2, NULL);
		*life->elapsed = (((time2.tv_sec - time.tv_sec) * 1000000 - (time2.tv_usec - time.tv_usec))/ 1000);
	}
}

int eat(t_philosphers *phil, int number, int *state)
{
	int next;

	next = 0;
	if (number < 1)
		next = number + 1;
	if (next == 0)
	{
		pthread_mutex_lock(&(phil->mu[next]));
		printf("Philospher %d has grabbed a fork %d next\n", number, next);
		pthread_mutex_lock(&(phil->mu[number]));
		printf("Philospher %d has grabbed another fork\n", number);
	}
	else
	{	
		pthread_mutex_lock(&(phil->mu[number]));
		printf("Philospher %d has grabbed a fork\n", number);
		pthread_mutex_lock(&(phil->mu[next]));
		printf("Philospher %d has grabbed another fork\n", number);
	}
	*state = 0;
	sleep(1);
	pthread_mutex_unlock(&(phil->mu[next]));
	return (0);
}

void phi_loop(t_philosphers *phil, int number)
{
	int state;//0 = sleeping, 1 = eating, 2 = thinking 3 = dead
	t_lifetime life;
	long elapsed;
	pthread_t cycle;

	life.state = &state;
	state = -1;
	life.ttd = 3000;
	life.elapsed = &elapsed;
	elapsed = 0;
	pthread_create(&cycle, NULL, life_cycle, &life);
	while (state != 3)
	{
		if (state == -1)
		{
			if (!eat(phil, number, &state))
			{
				pthread_mutex_unlock(&(phil->mu[number]));
				printf("Philospher %d has stopped eating\n", number);
				state = 1;
				elapsed = 0;
				pthread_create(&cycle, NULL, life_cycle, &life);
				printf("Philospher %d has stopped eating at : %ld\n", number, elapsed);
			}
		}
		else if (state == 1)
		{
			printf("Philospher %d has started thinking at : %ld\n", number, elapsed);
			sleep(1);
			state++;
			printf("Philospher %d has stopped thinking at : %ld\n", number, elapsed);
		}
		else if (state == 2)
		{
			printf("Philospher %d has started sleeping at : %ld\n", number, elapsed);
			sleep(1);
			state = -1;
			printf("Philospher %d has stopped sleeping at : %ld\n", number, elapsed);
		}
	}
	printf("Philospher %d has died at : %ld\n", number, elapsed);
	exit(0);
}

void *test(void *ph)
{
	t_philosphers *phil;
	int number;
	phil = ph;

	pthread_mutex_lock(&phil->num);
	number = phil->number;
	phil->number++;
	pthread_mutex_unlock(&phil->num);
	phi_loop(phil, number);

	pthread_exit(NULL);
}

void *time_ct(void *var)
{
	struct timeval time;
	struct timeval time2;
	long *elapsed;

	*elapsed = var;
	gettimeofday(&time, NULL);
	while (1)
	{
		gettimeofday(&time2, NULL);
		*elapsed = (((time2.tv_sec - time.tv_sec) * 1000000 - (time2.tv_usec - time.tv_usec))/ 1000);
	}
}

int main(int argc, char **argv)
{
	t_philosphers *philo;
	pthread_t thread;
	pthread_mutex_t m;
	int i;
	long time;

	i = 0;
	philo = (t_philosphers *)malloc(sizeof(t_philosphers));
	philo->number = i;
	philo->time = &time;
	time = 0;
	pthread_mutex_init(&philo->num, NULL);
	pthread_create(&thread, NULL,time_ct, &time);
	philo->mu = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t) * 2);
	while (i < 2)
	{
		m = philo->mu[i];
		pthread_mutex_init(&m, NULL);
		pthread_create(&thread, NULL,test, &(*philo));
		i++;
	}
	pthread_exit(NULL);
}
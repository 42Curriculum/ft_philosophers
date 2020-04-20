#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include "philosphers.h"

static void make_str(char *str, t_philosphers *phil, size_t len)
{
	ft_strlcat(str,phil->time_str, len);
	ft_strlcat(str," ms : Philosopher ", len);
	ft_strlcat(str, phil->num_str, len);
	if (*phil->state == -1)
		ft_strlcat(str," has taken a fork\n", len);
	else if (*phil->state == 3)
		ft_strlcat(str," died\n", len);
	else if (*phil->state == 2)
		ft_strlcat(str," is thinking\n", len);
	else if (*phil->state == 1)
		ft_strlcat(str," is sleeping\n", len);
	else if (*phil->state == 0)
		ft_strlcat(str," is eating\n", len);
	write(1, str, len);
}

void *print_status(void *var)
{
	char *print;
	long len;
	t_philosphers *phil;

	phil = var;
	phil->num_str = ft_ltoa_base(phil->number, 10);
	phil->time_str = ft_ltoa_base(*phil->time, 10);
	len = (ft_strlen(phil->time_str) + ft_strlen(phil->num_str) + 20);
	if (*phil->state == -1)
		len += 18;
	else if (*phil->state == 3)
		len += 4;
	else if (*phil->state == 2)
		len += 12;
	else if (*phil->state == 1)
		len += 12;
	else if (*phil->state == 0)
		len += 10;
	print = (char *)malloc(len + 1);
	memset(print, len,'\0');
	make_str(print, phil, len);
	free(print);
	pthread_exit(0);
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
	pthread_t thread;

	next = 0;
	if (number < 1)
		next = number + 1;
	if (next == 0)
	{
		pthread_mutex_lock(&(phil->mu[next]));
		phil->current = *phil->time;
		pthread_create(&thread, NULL, print_status, phil);
		pthread_mutex_lock(&(phil->mu[number]));
		pthread_create(&thread, NULL, print_status, phil);

	}
	else
	{	
		pthread_mutex_lock(&(phil->mu[number]));
		pthread_create(&thread, NULL, print_status, phil);
		pthread_mutex_lock(&(phil->mu[next]));
		pthread_create(&thread, NULL, print_status, phil);
	}
	*state = 0;
	sleep(1);
	pthread_mutex_unlock(&(phil->mu[next]));
	return (0);
}

void *phi_loop(void *arg)
{
	int state;//0 = sleeping, 1 = eating, 2 = thinking 3 = dead
	t_lifetime life;
	t_philosphers *phil;
	long elapsed;
	pthread_t cycle;

	state = -1;
	elapsed = 0;
	life.elapsed = &elapsed;
	phil = arg;
	life.state = &state;
	life.ttd = 3000;
	printf("End \n");
	phil->state = &state;
	pthread_create(&cycle, NULL, life_cycle, &life);
	while (state != 3)
	{
		if (state == -1)
		{
			if (!eat(phil, phil->number, &state))
			{
				pthread_mutex_unlock(&(phil->mu[phil->number]));
				state = 1;
				elapsed = 0;
				pthread_create(&cycle, NULL, life_cycle, &life);
			}
		}
		else if (state == 1)
		{
			phil->current = *phil->time;
			pthread_create(&cycle, NULL, print_status, phil);
			sleep(1);
			state++;
		}
		else if (state == 2)
		{
			phil->current = *phil->time;
			pthread_create(&cycle, NULL, print_status, phil);
			sleep(1);
			state = -1;
		}
	}
	phil->current = *phil->time;
	pthread_create(&cycle, NULL, print_status, phil);
	exit(0);
}

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

void 	Spawn(char *args, long *time, pthread_mutex_t **mu, int i)
{
	t_philosphers *phil;
	pthread_t thread;
	int number;

	phil = (t_philosphers *)malloc(sizeof(t_philosphers));
	phil->number = i;
	phil->mu = *mu;
	// phil.tt_die = times[0];
	// phil.tt_sleep = times[1];
	// phil.tt_eat = times[2];
	// phil.tt_think = times[0];
	phil->time = time;
	phil->state = 0;
	pthread_create(&thread, NULL, phi_loop, phil);
}

int main(int argc, char **argv)
{
	pthread_mutex_t	*mu;
	pthread_t thread;
	pthread_mutex_t m;
	int i;
	long time;

	i = 0;
	time = 0;
	pthread_create(&thread, NULL,time_ct, &time);
	mu = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t) * 2);
	while (i < 2)
	{
		m = mu[i];
		pthread_mutex_init(&m, NULL);
		printf("Start \n");
		Spawn(argv[1], &time, &mu, i);
		i++;
	}
	pthread_exit(NULL);
}
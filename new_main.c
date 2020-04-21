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
	phil->time_str = ft_ltoa_base(phil->current, 10);
	len = (ft_strlen(phil->time_str) + ft_strlen(phil->num_str) + 20);
	if (*phil->state == -1)
		len += 18;
	else if (*phil->state == 3)
		len += 5;
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
	if (*phil->state == 3)
		exit(0);
	pthread_exit(0);
}

void *life_cycle(void *arg)
{
	t_philosphers *phil;
	struct timeval time;
	struct timeval time2;
	long long elapsed;
	pthread_t thread;

	phil = arg;
	gettimeofday(&time, NULL);
	elapsed = 0;
	while (1)
	{
		if (phil->args[1] <= elapsed)
		{
			*phil->state = 3;
			pthread_create(&thread, NULL, print_status, phil);
			exit(0);
		}
		else if (phil->state == 0)
			pthread_exit(NULL);
		gettimeofday(&time2, NULL);
		elapsed = (((time2.tv_sec - time.tv_sec) * 1000000 - (time2.tv_usec - time.tv_usec))/ 1000);
	}
}
void do_stuff(t_philosphers *phil, int stuff)
{
	long i;
	
	i = 0;
	while (i < phil->args[stuff])
	{
		usleep(1);
		i++;
	}
}

int eat(t_philosphers *phil, int number, int *state)
{
	int next;
	pthread_t thread0;
	pthread_t thread1;

	next = 0;
	if (number < 1)
		next = number + 1;
	printf("I am number : %d\n", number);
	if (next == 0)
	{
		pthread_mutex_lock(&(phil->mu[next]));
		phil->current = *phil->time;
		pthread_create(&thread1, NULL, print_status, phil);
		pthread_mutex_lock(&(phil->mu[number]));
		phil->current = *phil->time;
		pthread_create(&thread1, NULL, print_status, phil);

	}
	else
	{	
		pthread_mutex_lock(&(phil->mu[number]));
		phil->current = *phil->time;
		printf("STAUS REPORT  : %d\n", *phil->state);
		pthread_create(&thread1, NULL, print_status, phil);
		pthread_mutex_lock(&(phil->mu[next]));
		printf("STAUS REPORT : %d\n", *phil->state);
		phil->current = *phil->time;
		pthread_create(&thread0, NULL, print_status, phil);
	}
	*state = 0;
	//do_stuff(phil, 2);
	sleep(1);
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
			sleep(3);
			state = -1;
		}
	}
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

void num_check(char **arg)
{
	long long number;
	int i;

	i = 2;
	if ((__INT_MAX__ - ft_atol(arg[1])) < 0)
	{
		write(2, ERR_NMAX1, 41);
		exit(0);
	}
	while (arg[i])
	{
		number = ft_atol(arg[i]);
		if (number < 0)
		{
			write(2, ERR_NMAX2, 44);
			exit(0);
		}
		i++;
	}
}

void error_check(char **arg)
{
	int i;
	int n;

	i = 1;
	while (arg[i])
	{
		n = 0;
		if (arg[i][0] == '-')
		{
			write(1, ERR_NEG, 29);
			exit(0);
		}
		while (arg[i][n])
		{
			if (arg[i][n] < '0' || arg[i][n] > '9')
			{
				write(1, ERR_NONUM, 26);
				exit(0);
			}
			n++;
		}
		i++;
	}
}

void	parser(char **arg, int (*iargs)[], int argc)
{
	int i;

	i = 1;
	if (argc > 5 || argc < 4)
	{
		write(2, ERR_ARGC, 28);
		exit(0);
	}
	error_check(arg);
	while (arg[i])
	{
		(*iargs)[i -1] = ft_atol(arg[i]);
		i++;
	}
	if (i <5)
	(*iargs)[5] = -1;
}

int main(int argc, char **argv)
{
	pthread_mutex_t	*mu;
	pthread_t thread;
	int args[5];
	int i;
	long time;

	i = 0;
	time = 0;
	parser(argv, &args, argc);
	pthread_create(&thread, NULL,time_ct, &time);
	mu = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t) * args[0]);
	while (i < args[0])
	{
		pthread_mutex_init(&mu[i], NULL);
		Spawn(args, &time, &mu, i);
		i++;
	}
	pthread_exit(NULL);
}
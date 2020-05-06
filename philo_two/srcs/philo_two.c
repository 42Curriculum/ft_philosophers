#include "philo_two.h"

int ask_nicely(t_philosphers *phil)
{
	if (*phil->sem_val < 2)
		return (STARVE_PEASANT);
	*phil->sem_val -= 2;
	return (EAT_SIR);
}

void eat(t_philosphers *phil)
{
	pthread_t thread;
	
	while (!ask_nicely(phil));
	printf("START\n");
	sem_wait(phil->sem);
	printf("END\n");
	sem_wait(phil->sem);
	phil->printvars[1] = -1;
	set_and_print(phil);
	set_and_print(phil);
	phil->printvars[1] = 0;
	do_stuff(phil, 2);
	pthread_create(&thread, NULL, life_cycle, phil);
	sem_post(phil->sem);
	sem_post(phil->sem);
	sem_close(phil->sem);
	*phil->sem_val += 2;
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
		if (phil->args[4] > 0)
			i++;
		do_stuff(phil, 3);
		phil->printvars[1] = 1;
	}
	if (++*phil->death >= phil->args[6])
		exit(0);
	pthread_exit(0);
}

void 	Spawn(int args[], long *time, sem_t *sem , int *sem_c)
{
	t_philosphers *phil;
	pthread_t thread;
	static int i;
	static int death;

	phil = (t_philosphers *)malloc(sizeof(t_philosphers));
	phil->printvars[0] = i;
	i++;
	phil->printvars[1] = 1;
	phil->sem = sem;
	phil->death = &death;
	phil->args = args;
	phil->time = time;
	phil->sem_val = sem_c;
	pthread_create(&thread, NULL, philosopher, phil);
}

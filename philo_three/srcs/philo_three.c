#include "philo_three.h"

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
	sem_wait(phil->sem);
	sem_wait(phil->sem);
	phil->printvars[1] = -1;
	set_and_print(phil);
	set_and_print(phil);
	phil->printvars[1] = 0;
	do_stuff(phil, 2);
	pthread_create(&thread, NULL, life_cycle, phil);
	sem_post(phil->sem);
	sem_post(phil->sem);
	*phil->sem_val += 2;
	phil->printvars[1] = 2;
}

void philosopher(t_philosphers *phil)
{
	int i;
	pthread_t thread;

	i = 0;
	phil->sem = sem_open(SEM_NAME, O_RDWR);
	pthread_create(&thread, NULL, life_cycle, phil);
	while (i != phil->args[4])
	{
		set_and_print(phil);
		eat(phil);
		if (phil->args[4] > 0)
			if (i == phil->args[4])
				break ;
		do_stuff(phil, 3);
		phil->printvars[1] = 1;
	}
	exit(0);
}

void 	Spawn(int args[], long *time,int *sem_c)
{
	t_philosphers *phil;
	pthread_t thread;
	static int i;

	phil = (t_philosphers *)malloc(sizeof(t_philosphers));
	phil->printvars[0] = i;
	i++;
	phil->printvars[1] = 1;
	phil->args = args;
	phil->time = time;
	phil->sem_val = sem_c;
	if (fork() == 0)
		philosopher(phil);
}

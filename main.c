#include "philo_one.h"

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
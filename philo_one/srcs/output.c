#include "philo_one.h"

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
	else if (*phil->state == 0)
		len += 10;
	print = (char *)malloc(len + 1);
	memset(print,'\0', len);
	make_str(print, phil, len);
	free(print);
	if (*phil->state == 3)
		exit(0);
	pthread_exit(0);
}
#include "philo_one.h"

static void make_str(t_print *print)
{
	ft_strlcat(print->print, print->time, print->len);
	ft_strlcat(print->print, " ms : Philosopher ", print->len);
	ft_strlcat(print->print,  print->num, print->len);
	if (print->args[1] == -1)
		ft_strlcat(print->print, " has taken a fork\n", print->len);
	else if (print->args[1] == 3)
		ft_strlcat(print->print, " died\n", print->len);
	else if (print->args[1] == 2)
		ft_strlcat(print->print, " is sleeping\n", print->len);
	else if (print->args[1] == 0)
		ft_strlcat(print->print, " is eating\n", print->len);
	else if (print->args[1] == 1)
		ft_strlcat(print->print, " is thinking\n", print->len);
	write(1, print->print,  print->len);
}


void free_prints(t_print *print)
{
	free(print->num);
	free(print->time);
	free(print->print);
	if (print->args[2] == 3)
	{
		free(print);
		exit(0);
	}
	free(print);
}

void *print_status(void *var)
{
	t_print	*print;

	print = var;
	print->len = (ft_strlen(print->num) + ft_strlen(print->time) + 20);
	if (print->args[1] == -1)
		print->len  += 18;
	else if (print->args[1] == 3)
		print->len  += 5;
	else if (print->args[1] == 2)
		print->len  += 12;
	else if (print->args[1] == 0)
		print->len  += 10;
	else if (print->args[1] == 1)
		print->len  += 13;
	print->print = (char *)malloc(print->len  + 1);
	memset(print->print,'\0', print->len );
	make_str(print);
	pthread_exit(0);
}

void set_and_print(t_philosphers *phil)
{
	pthread_t print_thread;
	t_print *print;

	print = (t_print *)malloc(sizeof(t_print));
	print->args[0] = phil->printvars[0];
	print->args[1] = phil->printvars[1];
	print->args[2] = phil->printvars[2];
	print->time = ft_ltoa_base(*phil->time, 10);
	print->num = ft_ltoa_base(print->args[0], 10);
	pthread_create(&print_thread, NULL, print_status, print);
}
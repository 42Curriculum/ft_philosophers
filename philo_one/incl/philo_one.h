#ifndef PHILO_ONE_H
#define PHILO_ONE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "philo_one_struct.h"


char		*ft_ltoa_base(long long value, int base);
size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dst, char *src, size_t destsize);
long long	ft_atol(char *str);
char	*ft_ltoa_base(long long value, int base);

void set_and_print(t_philosphers *phil);

void	parser(char **arg, int (*iargs)[], int argc);

void 	Spawn(int args[], long *time, pthread_mutex_t **mu, int i);

void *time_ct(void *var);
void *life_cycle(void *arg);
void do_stuff(t_philosphers *phil, int stuff);

#endif
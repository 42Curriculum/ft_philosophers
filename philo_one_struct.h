#ifndef PHILO_ONE_STRUCT_H
#define PHILO_ONE_STRUCT_H

#include <pthread.h>

# define ERR_ARGC "Invalid number of arguments\n"
# define ERR_NEG "Arguments cannot be negative\n"
# define ERR_NONUM "Arguments must be numbers\n"
 
# define ERR_NMAX1 "Argument 1 must be betwwen 0 and INT_MAX\n"
# define ERR_NMAX2 "Argument 2-6 must be betwwen 0 and LONG_MAX\n"

typedef struct		s_philosphers
{
	int				number;
	int				pno;
	long			eat_time;
	int				*args;
	int				*state;
	long			*time;
	long			current;
	char			*num_str;
	char			*time_str;
	pthread_mutex_t	*mu;
}					t_philosphers;

#endif
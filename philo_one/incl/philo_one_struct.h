#ifndef PHILO_ONE_STRUCT_H
#define PHILO_ONE_STRUCT_H

#include <pthread.h>

# define ERR_ARGC "Invalid number of arguments\n"\
"Usage p_one [number_of_philosophers] [time_to_die]"\
" [time_to_eat] [time_to_sleep] [eat_count]\n"
# define ERR_NEG "Arguments cannot be negative\n"
# define ERR_NONUM "Arguments must be numbers\n"
 
# define ERR_NMAX1 "Argument 1 must be betwwen 0 and INT_MAX\n"
# define ERR_NMAX2 "Argument 2-6 must be betwwen 0 and LONG_MAX\n"

typedef struct		s_philosphers
{
	int				*args;
	long			*time;
	long			current;
	int				printvars[3];//number, state, time
	int				unlock[2];
	pthread_mutex_t	*mu;
}					t_philosphers;

typedef struct		s_print
{
	int				args[3];
	long			len;
	long			elapsed;
	char 			*num;
	char			*time;
	char			*print;
}					t_print;

#endif
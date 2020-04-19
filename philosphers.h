#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>

typedef struct		s_philosphers
{
	int				number;
	int				tt_die;
	int				tt_sleep;
	int				tt_eat;
	int				state;
	long			*time;
	pthread_mutex_t	*mu;
	pthread_mutex_t	num;
}					t_philosphers;

typedef struct		s_lifetime
{
	int 			*state;
	int				ttd;
	long			start_time;
	long			*elapsed;
}					t_lifetime;

typedef struct		s_status
{
	int *number;
	int *status;
	long *time;
}					t_status;


char		*ft_ltoa_base(long long value, int base);
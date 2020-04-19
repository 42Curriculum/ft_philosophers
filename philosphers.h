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
	int				*state;
	long			*time;
	long			current;
	char			*num_str;
	char			*time_str;
	pthread_mutex_t	*mu;
	pthread_mutex_t	num;
}					t_philosphers;

typedef struct		s_lifetime
{
	int 			*state;// -2 grabbed fork, -1 waiting to eat, 0 eating, 1 sleeping, 2 thinking, 3 dead
	int				ttd;
	long			start_time;
	long			*elapsed;
}					t_lifetime;

typedef struct		s_status
{
	long number;
	long *status;
	long *time;
}					t_status;


char		*ft_ltoa_base(long long value, int base);
size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dst, char *src, size_t destsize);
long long	ft_atol(char *str);
char	*ft_ltoa_base(long long value, int base);
void *print_status(void *var);
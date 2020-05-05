/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 14:43:06 by jjosephi          #+#    #+#             */
/*   Updated: 2020/05/05 01:29:33 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_STRUCT_H
#define PHILO_TWO_STRUCT_H

#include <pthread.h>
#include <semaphore.h>

# define ERR_ARGC "Invalid number of arguments\n"\
"Usage p_one [number_of_philosophers] [time_to_die]"\
" [time_to_eat] [time_to_sleep] [eat_count]\n"
# define ERR_NEG "Arguments cannot be negative or null\n"
# define ERR_NONUM "Arguments must be numbers\n"
 
# define ERR_NMAX1 "Argument 1 must be betwwen 0 and INT_MAX\n"
# define ERR_NMAX2 "Argument 2-6 must be betwwen 0 and LONG_MAX\n"
# define EAT_SIR 1
# define STARVE_PEASANT 0
# define SEM_NAME "SEM_THREE"

typedef struct		s_philosphers
{
	int				*args;
	long			*time;
	long			current;
	int				printvars[3];//number, state, time
	int				*sem_val;
	int 			*death;
	sem_t			*sem;
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
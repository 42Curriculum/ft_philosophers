P_ONE_FILES = main output parser philo_one timer utils
P_ONE_INCL = /philo_one/incl/philo_one.h /philo_one/incl/philo_one_struct.h

P_ONE_SRCS = $(addprefix /philo_one/srcs, $(addsuffix .c , $(P_ONE_FILES)))
P_ONE_OBJS = $(addprefix /philo_one/srcs, $(addsuffix .o , $(P_ONE_FILES)))

FLAGS = -Wall -Wextra -Werror

all:
	@echo "Usage : Make p_[one - three]"



p_one:


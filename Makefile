P_ONE_PAIR_FILES = main output parser philo_one_even_odd timer utils
P_OFILES = main output parser philo_one timer utils
P_TFILES = main output parser philo_two timer utils
P_THFILES = main output parser philo_three timer utils

P_ONE_SRCS = $(addprefix philo_one/srcs/, $(addsuffix .c , $(P_OFILES)))
P_ONE_OBJS = $(addprefix philo_one/srcs/, $(addsuffix .o , $(P_OFILES)))
P_ONE_PAIR_SRCS = $(addprefix philo_one/srcs/, $(addsuffix .c , $(P_ONE_PAIR_FILES)))
P_ONE_PAIR_OBJS = $(addprefix philo_one/srcs/, $(addsuffix .o , $(P_ONE_PAIR_FILES)))

P_TWO_SRCS = $(addprefix philo_two/srcs/, $(addsuffix .c , $(P_TFILES)))
P_TWO_OBJS = $(addprefix philo_two/srcs/, $(addsuffix .o , $(P_TFILES)))


P_THREE_SRCS = $(addprefix philo_three/srcs/, $(addsuffix .c , $(P_THFILES)))
P_THREE_OBJS = $(addprefix philo_three/srcs/, $(addsuffix .o , $(P_THFILES)))

FLAGS = -g

all:
	@echo "Usage : Make p_[one - three]"



$(P_ONE_OBJS): %.o : %.c
		gcc $(FLAGS) -c -I  philo_one/incl/ $< -o $@
p_one: $(P_ONE_OBJS)
	gcc $(P_ONE_OBJS) -lpthread -o p_one



$(P_ONE_PAIR_OBJS): %.o : %.c
		gcc $(FLAGS) -c -I  philo_one/incl/ $< -o $@
p_one_pair: $(P_ONE_PAIR_OBJS)
	gcc $(P_ONE_PAIR_OBJS) -lpthread -o p_one


$(P_TWO_OBJS): %.o : %.c
		gcc $(FLAGS) -c -I philo_two/incl/ $< -o $@
p_two: $(P_TWO_OBJS)
	gcc $(P_TWO_OBJS) -lpthread -o p_two

$(P_THREE_OBJS): %.o : %.c
		gcc $(FLAGS) -c -I philo_three/incl/ $< -o $@
p_three: $(P_THREE_OBJS)
	gcc $(P_THREE_OBJS) -lpthread -o p_three

clean :
	@rm -f philo_one/srcs/*.o
	@rm -f philo_two/srcs/*.o
	@rm -f philo_three/srcs/*.o

fclean : clean
	@rm -f p_one
	@rm -f p_two
	@rm -f p_three

re : fclean p_one p_two p_three
	
.PHONY: clean fclean p_one p_two p_three
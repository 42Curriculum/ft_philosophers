P_ONE_PAIR_FILES = main output parser philo_one_even_odd timer utils
P_OFILES = main output parser philo_one timer utils
P_TLFILES = linux_main output parser philo_two timer utils
P_TMFILES = mac_main output parser philo_two timer utils
P_THFILES = main output parser philo_three timer utils

P_ONE_SRCS = $(addprefix philo_one/srcs/, $(addsuffix .c , $(P_OFILES)))
P_ONE_OBJS = $(addprefix philo_one/srcs/, $(addsuffix .o , $(P_OFILES)))
P_ONE_PAIR_SRCS = $(addprefix philo_one/srcs/, $(addsuffix .c , $(P_ONE_PAIR_FILES)))
P_ONE_PAIR_OBJS = $(addprefix philo_one/srcs/, $(addsuffix .o , $(P_ONE_PAIR_FILES)))

P_TWOL_SRCS = $(addprefix philo_two/srcs/, $(addsuffix .c , $(P_TLFILES)))
P_TWOL_OBJS = $(addprefix philo_two/srcs/, $(addsuffix .o , $(P_TLFILES)))

P_TWOM_SRCS = $(addprefix philo_two/srcs/, $(addsuffix .c , $(P_TMFILES)))
P_TWOM_OBJS = $(addprefix philo_two/srcs/, $(addsuffix .o , $(P_TMFILES)))

P_THREE_SRCS = $(addprefix philo_three/srcs/, $(addsuffix .c , $(P_THFILES)))
P_THREE_OBJS = $(addprefix philo_three/srcs/, $(addsuffix .o , $(P_THFILES)))

FLAGS = -Wall -Wextra -Werror

all:
	@echo "Usage : Make p_[one - three]"



$(P_ONE_OBJS): %.o : %.c
		@gcc $(FLAGS) -c -I  philo_one/incl/ $< -o $@
p_one: $(P_ONE_OBJS)
	@gcc $(P_ONE_OBJS) -lpthread -o p_one



$(P_ONE_PAIR_OBJS): %.o : %.c
		@gcc $(FLAGS) -c -I  philo_one/incl/ $< -o $@
p_one_pair: $(P_ONE_PAIR_OBJS)
	@gcc $(P_ONE_PAIR_OBJS) -lpthread -o p_one




$(P_TWOL_OBJS): %.o : %.c
		@gcc $(FLAGS) -c -I philo_two/incl/ $< -o $@
p_two_l: $(P_TWOL_OBJS)
	@gcc $(P_TWOL_OBJS) -lpthread -o p_two_l


$(P_TWOM_OBJS): %.o : %.c
		@gcc $(FLAGS) -c -I philo_two/incl/ $< -o $@
p_two_m: $(P_TWOM_OBJS)
	@gcc $(P_TWOM_OBJS) -lpthread -o p_two_m



$(P_THREE_OBJS): %.o : %.c
		@gcc $(FLAGS) -c -I philo_three/incl/ $< -o $@
p_three: $(P_THREE_OBJS)
	@gcc $(P_THREE_OBJS) -lpthread -o p_three

clean :
	@rm -f philo_one/srcs/*.o
	@rm -f philo_two/srcs/*.o
	@rm -f philo_three/srcs/*.o

fclean : clean
	@rm -f p_one
	@rm -f p_two
	@rm -f p_three

re : fclean p_one p_two_l p_two_m p_three

save :
	git add .
	git commit -m"automated push"
	git push git master

get :
	git add .
	git stash
	git pull

.PHONY: clean fclean p_one p_two_l p_two_m p_three save get
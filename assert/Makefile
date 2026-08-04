CC=cc
NAME=codexion_assert
CFLAGS=  -pthread -g
#CFLAGS= -Wall -Wextra -Werror -pthread

SRCS= $(wildcard ./*.c) $(filter-out ../srcs/codexion.c , $(wildcard ../srcs/*/*.c))	$(wildcard ../srcs/*/*/*.c)

SRCS_OBJS= $(SRCS:.c=.o)

%.o:%.c
	$(CC) $(CFLAGS) -c  $^ -o $@


$(NAME): $(SRCS_OBJS)
	$(CC) $(CFLAGS) $(SRCS_OBJS) -o $(NAME)

OS = $(shell uname)


# 	@valgrind \
# 	--log-file="valgrind.log" \
# 	--leak-check=full \
# 	--track-origins=yes \
# 	--show-leak-kinds=all \

run: $(NAME)
ifeq ($(OS), Darwin)
#MallocStackLogging=1 leaks -quiet -atExit -- ./$(NAME)
	./$(NAME)
else
	./$(NAME)
endif

asval:$(NAME)
	@valgrind \
 	--log-file="valgrind.log" \
 	--leak-check=full \
 	--track-origins=yes \
 	--show-leak-kinds=all \
	./$(NAME)

ashel: $(NAME)
	@valgrind --log-file="helgrind.log" --tool=helgrind ./$(NAME)


clean:
	rm -f $(SRCS_OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f valgrind.log helgrind.log

re: fclean $(NAME)

.PHONY: clean fclean $(NAME)


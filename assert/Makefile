CC=cc
NAME=codexion_assert
CFLAGS= -Wall -Wextra -Werror -pthread

SRCS= $(wildcard ./*.c) $(filter-out ../srcs/codexion.c , $(wildcard ../srcs/*.c))	

SRCS_OBJS= $(SRCS:.c=.o)

%.o:%.c
	$(CC) $(CFLAGS) -c  $^ -o $@


$(NAME): $(SRCS_OBJS)
	$(CC) $(CFLAGS) $(SRCS_OBJS) -o $(NAME)

run: $(NAME)
	./$(NAME)

clean:
	rm -f $(SRCS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean $(NAME)


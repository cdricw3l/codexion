CC=cc
NAME=codexion
#CFLAGS= -Wall -Wextra -Werror -g -pthread
CFLAGS=  -g -pthread
SHELL=/bin/bash
SRCS= srcs/codexion.c \
		srcs/parsing.c \
		srcs/utils.c \
		srcs/display.c \
		srcs/thread.c  \
		srcs/time.c \
		srcs/error.c \


SRCS_OBJS= ${SRCS:.c=.o}

%.o:%.c
	${CC} -c  ${CFLAGS} $^ -o $@

all= $(NAME)

$(NAME): $(SRCS_OBJS)
	@$(CC) $(CFLAG) $(SRCS_OBJS) -o $(NAME) -lpthread

ARG=10 200 100 100 100 10 100 fifo

run: $(NAME)
	./$(NAME) $(ARG)

valrun: $(NAME)
	@valgrind \
	--log-file="valgrind.log" \
	--leak-check=full \
	--track-origins=yes \
	--show-leak-kinds=all \
	./$(NAME) $(ARG)

helrun: $(NAME)
	valgrind --log-file="helgrind.log" --tool=helgrind ./$(NAME) 

clean:
	rm -f srcs/*.o

fclean: clean
	@make  -s -C  assert fclean
	rm -f $(NAME) *.log

re: fclean $(NAME)

# run assertion makefile -C -> target makefile folder
as:
	@make  -s -C  assert run

# recopile and run assertion makefile -C -> target makefile folder
ras:
	@make  -s -C  assert re
	@make  -s -C  assert run

COM="generic comment"
git: fclean
	git add .
	git commit -m $(COM)
	git push --all

.PHONY: codexion run valrun helrun clean fclean
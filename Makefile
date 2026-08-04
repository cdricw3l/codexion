CC=gcc
NAME=codexion
CFLAGS= -Wall -Wextra -Werror -g -pthread
#CFLAGS=  -g -pthread
SHELL=/bin/bash
SRCS= srcs/codexion.c \
		srcs/parsing/parsing.c \
		srcs/utils/utils.c \
		srcs/display/display.c \
		srcs/errors/error.c \
 		srcs/time/time.c \
		srcs/init/initialisation.c \
		srcs/clean/clean.c \
		srcs/heap/heap_bfs.c \
		srcs/heap/heap_pop_request.c \
		srcs/heap/request.c \
		srcs/heap/heap_push_request.c \
		srcs/heap/heap_utils.c \
		srcs/thread/thread.c \
		srcs/thread/coders/coder_thread.c \
		srcs/thread/coders/coder_actions.c \
		srcs/thread/monitoring/monitoring_thread.c \



SRCS_OBJS= ${SRCS:.c=.o}

%.o:%.c
	${CC} -c  ${CFLAGS} $^ -o $@

all= $(NAME)

$(NAME): $(SRCS_OBJS)
	@$(CC) $(CFLAG) $(SRCS_OBJS) -o $(NAME) -lpthread

ARG=4 500 300 100 100 2 10 fifo

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
	valgrind --log-file="helgrind.log" --tool=helgrind ./$(NAME)  $(ARG)

clean:
	rm -f $(SRCS_OBJS)

fclean: clean
	rm -f $(NAME) *.log

re: fclean $(NAME)

COM="generic comment"
git: fclean
	git add .
	git commit -m $(COM)
	git push --all


.PHONY: codexion run valrun helrun clean fclean test
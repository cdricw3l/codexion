CC=gcc
NAME=codexion
CFLAGS= -Wall -Wextra -Werror -g -pthread
#CFLAGS= -Wextra -Werror -Wall  -g -pthread
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
		srcs/thread/coder_thread.c \
		srcs/thread/monitoring_thread.c \



SRCS_OBJS= ${SRCS:.c=.o}

%.o:%.c
	${CC} -c  ${CFLAGS} $^ -o $@

all= $(NAME)

$(NAME): $(SRCS_OBJS)
	@$(CC) $(CFLAG) $(SRCS_OBJS) -o $(NAME) -lpthread

ARG=20 500 200 100 100 10 10 fifo

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
	@make  -s -C  assert fclean
	rm -f $(NAME) *.log

re: fclean $(NAME)

# run assertion makefile -C -> target makefile folder
as:
	@make  -s -C  assert run

ashel:
	@make  -s -C  assert ashel
asval:
	@make  -s -C  assert asval

# recopile and run assertion makefile -C -> target makefile folder
ras:
	@make  -s -C  assert re
	@make  -s -C  assert run

COM="generic comment"
git: fclean
	git add .
	git commit -m $(COM)
	git push --all

test:
	$(CC) -g -pthread pthread.c  -o pthread
	valgrind --log-file="helgrind.log" --tool=helgrind  ./pthread

.PHONY: codexion run valrun helrun clean fclean test
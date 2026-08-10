CC=gcc
NAME=codexion
CFLAGS= -Wall -Wextra -Werror -g -pthread
#CFLAGS= -Wextra -Werror -Wall  -g -pthread
#CFLAGS=  -g -pthread
SHELL=/bin/bash
SRCS= 	codexion.c \
		srcs/display.c \
		srcs/dongles.c \
		srcs/parsing/parsing.c \
		srcs/errors/error.c \
		srcs/init/init.c \
		srcs/utils/utils_1.c \
		srcs/utils/utils_clean_pthread.c \
		srcs/utils/utils_init_pthread.c
	
OS_NAME = $(shell uname)

SRCS_OBJS= ${SRCS:.c=.o}

%.o:%.c
	${CC} -c  ${CFLAGS} $^ -o $@

all= $(NAME)

$(NAME): $(SRCS_OBJS)
	@$(CC) $(CFLAG) $(SRCS_OBJS) -o $(NAME) -lpthread

ARG=20 500 200 100 100 10 10 fifo

t: $(NAME)
ifeq ($(shell uname), "Darwin")
	echo $("OS_NAME")
#leaks -atExit -- ./$(NAME) $(ARG)
endif

run: $(NAME)

ifeq ($(OS_NAME), Darwin)
	leaks -atExit -- ./$(NAME) $(ARG)
endif

SRCS_DRAFT = draft.c \
			srcs/display.c \
			srcs/dongles.c \
			srcs/parsing/parsing.c \
			srcs/errors/error.c \
			srcs/utils/utils_1.c \
			srcs/utils/utils_clean_pthread.c \
			srcs/utils/utils_init_pthread.c

OBJS_DRAFT = ${SRCS_DRAFT:.c=.o}

draft: $(OBJS_DRAFT)
	$(CC) $(CFLAGS) srcs/*/*.c draft.c -o draft
	./draft

valrun: $(NAME)
	@valgrind \
	--log-file="valgrind.log" \
	--leak-check=full \
	--track-origins=                            yes \
	--show-leak-kinds=all \
	./$(NAME) $(ARG)

helrun: $(NAME)
	valgrind --log-file="helgrind.log" --tool=helgrind ./$(NAME)  $(ARG)

clean:
	rm -f $(SRCS_OBJS) $(OBJS_DRAFT)

fclean: clean
#@make  -s -C  assert fclean
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
SRCS	= all_actions.c init_all.c main.c parsing.c philo.c threading.c time_management.c

OBJS	= ${SRCS:.c=.o}

CC	= cc

RM	= rm -f

CFLAGS    = -Wall -Wextra -Werror

NAME    = philophers

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}:    ${OBJS}
				${CC} ${CFLAGS} ${OBJS} -o ${NAME}
clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY: clean fclean all re
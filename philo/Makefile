NAME = philo

INC = inc/

CC = cc -Wall -Werror -Wextra -fsanitize=address

FILES = src/dinner.c \
		src/get_set.c \
		src/init.c \
		src/main.c \
		src/parsing.c \
		src/safe_funcs.c \
		src/synchro.c \
		src/utils.c \
		src/write.c \
		src/monitor.c

SRCS = $(FILES)

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)
			@echo "$(NAME) created"

clean:
	@$(RM) $(OBJ)

fclean:		clean
				@$(RM) $(NAME)
				@echo "$(NAME) deleted"

re:			fclean all

.PHONY:			start all clean fclean re
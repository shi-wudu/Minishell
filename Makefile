NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lreadline

SRC = src/main.c \
	src/lexer.c \
	src/utils.c


OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

clean:
	rm -f src/*.o 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
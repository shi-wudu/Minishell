NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -lreadline

SRC = src/main.c \
	src/lexer_utils.c \
	src/lexer.c \
	src/utils.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LIBS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

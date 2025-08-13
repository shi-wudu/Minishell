SRCS			=	ft_hexa.c ft_printhelp.c ft_printf.c \

NAME			=	libftprintf.a

OBJS			=	$(SRCS:.c=.o)

CC				=	cc

CFLAGS			=	-Wall -Werror -Wextra

all:		$(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): 	$(OBJS)
					ar rcs $(NAME) $(OBJS)

clean:
					rm -f $(OBJS)

fclean: 	clean
					rm -f $(NAME)

re:			fclean all

.PHONY: all clean fclean re
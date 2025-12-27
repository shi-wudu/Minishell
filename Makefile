NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -Iinclude
RM          = rm -f
SRC_DIR     = src
OBJ_DIR     = obj
 
SRC_FILES := \
	main.c \
    builtin/builtin.c \
    builtin/echo_cd_pwd.c \
    builtin/exit_export.c \
    builtin/unset.c \
	parser/parser_redirects_pipe.c \
	parser/parser_utils.c \
	parser/parser_word.c \
	parser/parser.c \
	utils/utils.c \
	utils/check_error.c \
	expander/expander.c \
	expander/expander_utils.c \
	exec/executer.c \
	exec/exec_child.c \
	exec/exec_parent.c \
    exec/pathing.c \
    exec/redirections.c \
    exec/piping_1.c \
	exec/piping_2.c \
    exec/piping_utils.c \
	signal/signals_01.c \
	signal/signals_02.c \
	heredoc/heredoc.c \
	heredoc/heredoc_utils.c \
	heredoc/heredoc_write.c \
	lexer/lexer_identifier.c \
	lexer/lexer_separator.c \
	lexer/lexer_token.c \
	lexer/lexer_utils.c \
	lexer/lexer.c \
	env/env_copy.c \
	env/env_get.c \
	env/env_update.c 


SRC := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C libft --no-print-directory
	@$(CC) $(CFLAGS) $(OBJ) -Llibft -lft -lreadline -o $(NAME)
	@echo "Build complete: $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "Cleaned object files"

fclean: clean
	@$(MAKE) -C libft fclean --no-print-directory
	@$(RM) $(NAME)
	@echo "Full clean done"

re: fclean all

v:		$(NAME)
	clear && valgrind --show-leak-kinds=all --leak-check=full --track-fds=all --track-origins=yes --suppressions=readline.supp ./minishell

ch:		$(NAME)
	valgrind --show-leak-kinds=all --leak-check=full --track-fds=all --track-origins=yes --suppressions=readline.supp --trace-children=yes ./minishell

.PHONY: all clean fclean re

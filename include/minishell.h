#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
//#include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <ctype.h>
# include <sys/wait.h>
# include "../Libft/libft.h"
# include "../ft_printf/ft_printf.h" 


// LEXER
typedef enum e_token_type
{
    TOKEN_WORD,          // command or arg
    TOKEN_PIPE,          // |
    TOKEN_REDIRECT_IN,   // <
    TOKEN_REDIRECT_OUT,  // >
    TOKEN_APPEND,        // >>
    TOKEN_HEREDOC,       // <<
    TOKEN_STRING,        // "..." ou '...'
    TOKEN_END            // NULL
}   t_token_type;

typedef struct s_token
{
    char            *value;
    t_token_type    type;
    struct s_token  *next;
}   t_token;

t_token *tokenize(const char *input);
void    free_tokens(t_token *list);



// Utilis
int ft_is_space(char c);


#endif
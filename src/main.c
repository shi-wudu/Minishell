#include "../include/minishell.h"

static void print_tokens(t_token *list)
{
    while (list)
    {
        printf("Token: %-15s Tipo: %d\n", list->value, list->type);
        list = list->next;
    }
}

// Test
int main(void)
{
    char *input;
    
    input = readline("minishell> ");
    if (input)
    {
        t_token *tokens;
        
        tokens = tokenize(input);
        print_tokens(tokens);
        free_tokens(tokens);
        free(input);
    }
    return 0;
}


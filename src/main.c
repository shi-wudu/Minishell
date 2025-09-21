#include "../include/minishell.h"

/*static void print_tokens(t_token *list)
{
    while (list)
    {
        printf("Token: %-15s Tipo: %d\n", list->value, list->type);
        list = list->next;
    }
}*/

static void print_cmds(t_cmd *cmd)
{
    int i;
    while (cmd)
    {
        printf("CMD:\n");
        for (i = 0; i < cmd->argc; i++)
            printf("  argv[%d] = %s\n", i, cmd->argv[i]);
        if (cmd->infile)
            printf("  infile: %s\n", cmd->infile);
        if (cmd->outfile)
            printf("  outfile: %s\n", cmd->outfile);
        cmd = cmd->next;
    }
}


int main(void)
{
    char *input;

    input = readline("minishell> ");
    if (input)
    {
        t_token *tokens;
        t_cmd   *cmds;

        tokens = tokenize(input);
        print_tokens(tokens);

        cmds = parse_tokens(tokens);
        print_cmds(cmds);

        free_tokens(tokens);
        free_cmds(cmds);
        free(input);
    }
    return 0;
}


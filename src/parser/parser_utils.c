#include "../../include/minishell.h"

t_cmd *last_cmd(t_cmd *cmd)
{
    while (cmd && cmd->next)
        cmd = cmd->next;
    return cmd;
}

void free_commands(t_cmd *cmd)
{
    t_cmd *tmp;

    while (cmd)
    {
        tmp = cmd->next;
        free(cmd->command);
        free_str_tab(cmd->args);
        if (cmd->io.infile)
            free(cmd->io.infile);
        if (cmd->io.outfile)
            free(cmd->io.outfile);
        free(cmd);
        cmd = tmp;
    }
}

void free_str_tab(char **tab)
{
    int i = 0;

    if (!tab)
        return;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}
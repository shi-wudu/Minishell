#include "../../include/minishell.h"

t_cmd *cmd_new(void)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return NULL;
    cmd->argv = NULL;
    cmd->argc = 0;
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->next = NULL;
    return cmd;
}

void cmd_add_arg(t_cmd *cmd, char *str)
{
    char **new_argv;
    int i;

    new_argv = malloc(sizeof(char *) * (cmd->argc + 2));
    if (!new_argv)
        return;                                 //acrescentar eero
    i = 0;
    while (i < cmd->argc)
    {
        new_argv[i] = cmd->argv[i];
        i++;
    }
    new_argv[i] = ft_strdup(str);
    new_argv[i + 1] = NULL;
    free(cmd->argv);
    cmd->argv = new_argv;
    cmd->argc++;
}

void free_cmds(t_cmd *cmd)
{
    t_cmd *tmp;
    int i;

    while (cmd)
    {
        tmp = cmd;
        cmd = cmd->next;
        if (tmp->argv)
        {
            i = 0;
            while (tmp->argv[i])
            {
                free(tmp->argv[i]);
                i++;
            }
            free(tmp->argv);
        }
        free(tmp->infile);
        free(tmp->outfile);
        free(tmp);
    }
}
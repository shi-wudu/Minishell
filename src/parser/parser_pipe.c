#include "../../include/minishell.h"

t_cmd *parse_pipe(t_cmd *cmd, t_token **tk)
{
    t_cmd *new_cmd;

    cmd->pipe_output = true;
    new_cmd = calloc(1, sizeof(t_cmd));
    if (!new_cmd)
        return (NULL);
    init_cmd(new_cmd);
    cmd->next = new_cmd;
    new_cmd->prev = cmd;
    *tk = (*tk)->next;
    return (new_cmd);
}

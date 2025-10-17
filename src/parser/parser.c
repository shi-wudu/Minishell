#include "../../include/minishell.h"

void	init_cmd(t_cmd *cmd)
{
	if (!cmd)
		return;
	cmd->command = NULL;
	cmd->args = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->pipe_output = false;
	cmd->io.fd_in = -1;
	cmd->io.fd_out = -1;
	cmd->io.infile = NULL;
	cmd->io.outfile = NULL;
	cmd->io.heredoc_delimiter = NULL;
	cmd->io.append = false;
	cmd->io.heredoc = false;
}


t_cmd *parser(t_token *tokens)
{
    t_cmd *head = NULL;
    t_cmd *current = NULL;
    t_token *tk = tokens;

    while (tk && tk->type != END)
    {
        if (!current)
        {
            current = calloc(1, sizeof(t_cmd));
            if (!current)
                return (NULL);
            init_cmd(current);
            head = current;
        }

        if (tk->type == WORD)
            parse_word(current, &tk);
        else if (tk->type == PIPE)
            current = parse_pipe(current, &tk);
        else if (tk->type == INPUT || tk->type == TRUNC ||
                 tk->type == APPEND || tk->type == HEREDOC)
            parse_redirect(current, &tk);
        else
            tk = tk->next;
    }

    return (head);
}

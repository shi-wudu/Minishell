#include "../../include/minishell.h"

static void	set_command(t_cmd *cmd, t_token **tk)
{
	if (!cmd->command)
	{
		if ((*tk)->value)
			cmd->command = ft_strdup((*tk)->value);
		else
			cmd->command = ft_strdup("");
		*tk = (*tk)->next;
	}
}

static int	count_args(t_token *tk)
{
	int	count = 0;

	while (tk && (tk->type == WORD || tk->type == STRING))
	{
		count++;
		tk = tk->next;
	}
	return (count);
}

void	parse_word(t_cmd *cmd, t_token **tk)
{
	int		i;
	int		argc;

	if (!cmd || !tk || !*tk)
		return;
	set_command(cmd, tk);
	argc = count_args(*tk);
	cmd->args = malloc(sizeof(char *) * (argc + 2));
	if (!cmd->args)
		return;
	if (cmd->command)
		cmd->args[0] = ft_strdup(cmd->command);
	else
		cmd->args[0] = ft_strdup("");

	i = 1;
	while (*tk && ((*tk)->type == WORD || (*tk)->type == STRING))
	{
		if ((*tk)->value)
			cmd->args[i++] = ft_strdup((*tk)->value);
		else
			cmd->args[i++] = ft_strdup("");
		*tk = (*tk)->next;
	}
	cmd->args[i] = NULL;
}


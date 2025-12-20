/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:04 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/20 13:19:04 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_command(t_cmd *cmd, t_token **tk)
{
	if (!cmd->command)
	{
		if ((*tk)->value)
			cmd->command = ft_strdup((*tk)->value); // free
		else
			cmd->command = ft_strdup(""); // free
		*tk = (*tk)->next;
	}
}

static int	count_args(t_token *tk)
{
	int	count;

	count = 0;
	while (tk && tk->type != PIPE && tk->type != INPUT && tk->type != TRUNC
		&& tk->type != APPEND && tk->type != HEREDOC && tk->type != END)
	{
		if (tk->type == WORD)
			count++;
		tk = tk->next;
	}
	return (count);
}

static void	init_args_zero(t_cmd *cmd)
{
	if (cmd->command)
		cmd->args[0] = ft_strdup(cmd->command);
	else
		cmd->args[0] = ft_strdup("");
}

static void	fill_args(t_cmd *cmd, t_token **tk)
{
	int	i;

	i = 1;
	while (*tk && (*tk)->type != PIPE && (*tk)->type != INPUT
		&& (*tk)->type != TRUNC && (*tk)->type != APPEND
		&& (*tk)->type != HEREDOC && (*tk)->type != END)
	{
		if ((*tk)->type == WORD)
		{
			cmd->args[i++] = ft_strdup((*tk)->value);
			*tk = (*tk)->next;
		}
		else
			break ;
	}
	cmd->args[i] = NULL;
}

void	parse_word(t_cmd *cmd, t_token **tk)
{
	int	argc;

	if (!cmd || !tk || !*tk)
		return ;
	set_command(cmd, tk);
	argc = count_args(*tk);
	cmd->args = malloc(sizeof(char *) * (argc + 2));
	if (!cmd->args)
		return ;
	init_args_zero(cmd);
	fill_args(cmd, tk);
}

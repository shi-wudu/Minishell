/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:13 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/20 13:19:13 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Aplica uma redireção de saída ao comando.

static void	set_outfile(t_cmd *cmd, char *filename, bool append)
{
	if (cmd->io.outfile)
		free(cmd->io.outfile);
	cmd->io.outfile = ft_strdup(filename);
	cmd->io.append = append;
}

// Valida se um operador de redireção tem um token válido a seguir.

static bool	validate_redirect(t_token *tk, t_data *data)
{
	if (!tk->next || tk->next->type != WORD)
	{
		ft_putendl_fd(
			"minishell: syntax error near unexpected token `newline'", 2);
		data->parse_error = true;
		return (false);
	}
	return (true);
}

// Aplica a redireção ao comando (input, output ou heredoc).

static void	apply_redirect(t_cmd *cmd, t_token *tk)
{
	char	*filename;

	filename = tk->next->value;
	if (tk->type == INPUT)
	{
		free(cmd->io.infile);
		cmd->io.infile = ft_strdup(filename);
	}
	else if (tk->type == TRUNC)
		set_outfile(cmd, filename, false);
	else if (tk->type == APPEND)
		set_outfile(cmd, filename, true);
	else if (tk->type == HEREDOC)
	{
		free(cmd->io.heredoc_delimiter);
		cmd->io.heredoc_expand = !tk->next->no_expand;
		cmd->io.heredoc_delimiter = ft_strdup(filename);
		cmd->io.heredoc = true;
	}
}

void	parse_redirect(t_cmd *cmd, t_token **tk, t_data *data)
{
	if (!validate_redirect(*tk, data))
	{
		*tk = NULL;
		return ;
	}
	apply_redirect(cmd, *tk);
	*tk = (*tk)->next->next;
}

// Processa um pipe e cria um novo comando ligado ao anterior.

t_cmd	*parse_pipe(t_cmd *cmd, t_token **tk)
{
	t_cmd	*new_cmd;

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

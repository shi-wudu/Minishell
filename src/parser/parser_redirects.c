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

static void	touch_outfile(char *filename, bool append)
{
	int	fd;

	if (append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd >= 0)
		close(fd);
}

static char	*strip_quotes(const char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (len >= 2 && ((s[0] == '\'' && s[len - 1] == '\'')
		|| (s[0] == '"' && s[len - 1] == '"')))
		return (ft_substr(s, 1, len - 2));
	return (ft_strdup(s));
}

static void	apply_redirect(t_cmd *cmd, t_token *op, t_token *arg)
{
	if (op->type == INPUT)
	{
		free(cmd->io.infile);
		cmd->io.infile = ft_strdup(arg->value);
	}
	else if (op->type == HEREDOC)
	{
		cmd->io.heredoc = true;
		cmd->io.heredoc_expand = !arg->quoted;
		free(cmd->io.heredoc_delimiter);
		cmd->io.heredoc_delimiter = strip_quotes(arg->value);
	}
	else
	{
		touch_outfile(arg->value, op->type == APPEND);
		free(cmd->io.outfile);
		cmd->io.outfile = ft_strdup(arg->value);
		cmd->io.append = (op->type == APPEND);
		//cmd->pipe_output = false;
	}
}

bool	parse_redirect_token(t_cmd *cmd, t_token **tk, t_data *data)
{
	t_token	*op;
	t_token	*arg;

	op = *tk;
	arg = op->next;
	if (!arg || arg->type != WORD)
	{
		syntax_error("newline");
		data->parse_error = true;
		return (false);
	}
	apply_redirect(cmd, op, arg);
	*tk = arg->next;
	return (true);
}

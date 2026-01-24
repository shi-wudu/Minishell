/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:13 by seilkiv           #+#    #+#             */
/*   Updated: 2026/01/23 13:38:01 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// adiciona uma string ao fim de um array NULL-terminated de strings
// cria um novo array
// liberta o array antigo (mas não o conteúdo)
// retorna o novo array ou NULL em erro

char	**append_str_array(char **old, char *value)
{
	char	**new;
	int		i;

	i = 0;
	while (old && old[i])
		i++;
	new = ft_calloc(i + 2, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (old && old[i])
	{
		new[i] = old[i];
		i++;
	}
	new[i] = value;
	new[i + 1] = NULL;
	free(old);
	return (new);
}

// Aplica uma redirection ao comando atual,
// INPUT → infile
// OUTPUT → outfile
// HEREDOC → guarda delimitador

static void	apply_redirect(t_cmd *cmd, t_token *op, char *filename)
{
	if (op->type == INPUT)
	{
		free(cmd->io.infile);
		cmd->io.infile = ft_strdup(filename);
		cmd->io.infile_is_heredoc = false;
	}
	else if (op->type == HEREDOC)
	{
		cmd->heredoc_delimiters = append_str_array(cmd->heredoc_delimiters,
				ft_strdup(filename));
		cmd->heredoc_count++;
	}
	else
	{
		free(cmd->io.outfile);
		cmd->io.outfile = ft_strdup(filename);
		cmd->io.append = (op->type == APPEND);
	}
}

// Verifica se o delimitador do heredoc contém aspas.
// Se tiver aspas, não há expansão de variáveis.

static bool	heredoc_is_quoted(t_token *arg)
{
	t_segment	*seg;

	seg = arg->segments;
	while (seg)
	{
		if (seg->type != UNQUOTED)
			return (true);
		seg = seg->next;
	}
	return (false);
}

// Processa tokens de redirection (<, >, >>, <<).
// Valida a existência do argumento.

bool	parse_redirect_token(t_cmd *cmd, t_token **tk, t_data *data)
{
	t_token	*op;
	t_token	*arg;

	op = *tk;
	arg = op->next;
	if (!arg || arg->type != WORD || !arg->expanded || !arg->expanded[0])
	{
		syntax_error("newline");
		data->parse_error = true;
		return (false);
	}
	if (op->type == HEREDOC)
		cmd->io.heredoc_expand = !heredoc_is_quoted(arg);
	apply_redirect(cmd, op, arg->expanded[0]);
	*tk = arg->next;
	return (true);
}

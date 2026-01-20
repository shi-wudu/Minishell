/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:13 by seilkiv           #+#    #+#             */
/*   Updated: 2026/01/16 14:02:21 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// adiciona uma string ao fim de um array NULL-terminated de strings
// cria um novo array com +1 slot, reaproveita os pointers existentes
// NÃO duplica as strings: apenas move os pointers
// liberta o array antigo (mas não o conteúdo)
// retorna o novo array ou NULL em erro

static char	**append_str_array(char **old, char *value)
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

// Cria ou prepara um ficheiro de output para redirection (> ou >>).

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

// Aplica uma redirection ao comando atual,
// configurando infile, outfile ou heredoc conforme o operador.

static void	apply_redirect(t_cmd *cmd, t_token *op, t_token *arg)
{
	if (op->type == INPUT)
	{
		free(cmd->io.infile);
		cmd->io.infile = ft_strdup(arg->value);
	}
	else if (op->type == HEREDOC)
	{
		cmd->io.heredoc_expand = !arg->quoted;
		cmd->heredoc_delimiters = append_str_array(cmd->heredoc_delimiters,strip_quotes(arg->value));
		cmd->heredoc_count++;
	}
	else
	{
		touch_outfile(arg->value, op->type == APPEND);
		free(cmd->io.outfile);
		cmd->io.outfile = ft_strdup(arg->value);
		cmd->io.append = (op->type == APPEND);
	}
}

// Processa um token de redirection.
// Valida sintaxe, aplica a redirection e avança o token.

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:18:52 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/20 13:18:52 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
}

static bool	is_redirect(t_token_type type)
{
	return (type == INPUT || type == TRUNC || type == APPEND
		|| type == HEREDOC);
}

// Valida regras de sintaxe relacionadas com pipes:
// - pipe no início
// - pipes consecutivos
// - pipe no fim da linha

static bool	check_pipes(t_token *tk)
{
	if (tk && tk->type == PIPE)
		return (syntax_error("|"), false);
	while (tk && tk->next)
	{
		if (tk->type == PIPE && tk->next->type == PIPE)
			return (syntax_error("|"), false);
		tk = tk->next;
	}
	if (tk && tk->type == PIPE)
		return (syntax_error("|"), false);
	return (true);
}

// Valida regras de sintaxe relacionadas com redireções:
// - redireção no fim
// - redireção seguida de pipe
// - redireções consecutivas

static bool	check_redirects(t_token *tk)
{
	while (tk)
	{
		if (is_redirect(tk->type))
		{
			if (!tk->next || tk->next->type == END)
			{
				syntax_error("redirect");
				return (false);
			}
			if (tk->next->type == PIPE)
			{
				syntax_error("|");
				return (false);
			}
			if (is_redirect(tk->next->type))
			{
				syntax_error("redirect");
				return (false);
			}
		}
		tk = tk->next;
	}
	return (true);
}

// Executa todas as verificações sintáticas da lista de tokens.
// Retorna false se algum erro for encontrado.

bool	check_syntax(t_token *tokens)
{
	if (!tokens)
		return (true);
	if (!check_pipes(tokens))
		return (false);
	if (!check_redirects(tokens))
		return (false);
	return (true);
}

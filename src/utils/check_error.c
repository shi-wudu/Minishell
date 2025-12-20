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

static bool	check_pipes(t_token *tk)
{
	/* pipe no início */
	if (tk && tk->type == PIPE)
		return (syntax_error("|"), false);
	while (tk && tk->next)
	{
		/* pipe seguido de pipe */
		if (tk->type == PIPE && tk->next->type == PIPE)
			return (syntax_error("|"), false);
		tk = tk->next;
	}
	/* pipe no fim */
	if (tk && tk->type == PIPE)
		return (syntax_error("|"), false);
	return (true);
}

static bool	check_redirects(t_token *tk)
{
	while (tk)
	{
		if (is_redirect(tk->type))
		{
			/* redirect no fim: echo > */
			if (!tk->next || tk->next->type == END)
			{
				syntax_error("redirect");
				return (false);
			}
			/* redirect seguido de pipe: echo > | */
			if (tk->next->type == PIPE)
			{
				syntax_error("|");
				return (false);
			}
			/* redirect seguido de outro redirect: echo > > */
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

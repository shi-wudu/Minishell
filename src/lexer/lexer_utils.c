/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:29 by seilkiv           #+#    #+#             */
/*   Updated: 2026/01/23 07:02:18 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_quote(char c)
{
	return (c == '\'' || c == '"');
}

void	ft_skip_spaces(char **line)
{
	while (**line && ft_is_space(**line))
		(*line)++;
}

void	ft_print_quote_err(char c)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
}

bool	is_word_char(char c)
{
	return (!ft_is_space(c) && c != '<' && c != '>' && c != '|');
}

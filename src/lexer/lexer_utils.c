/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:33 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/20 13:19:33 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_redirect(char c)
{
	return (c == '<' || c == '>');
}

int	skip_spaces(const char *str, int i)
{
	while (str[i] && ft_is_space(str[i]))
		i++;
	return (i);
}

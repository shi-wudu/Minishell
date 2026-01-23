/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:25 by seilkiv           #+#    #+#             */
/*   Updated: 2026/01/23 06:49:31 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Acrescenta um caractere a uma string, realocando-a.
char	*append_char(char *s, char c)
{
	char	tmp[2];
	char	*new;

	tmp[0] = c;
	tmp[1] = '\0';
	new = ft_strjoin(s, tmp);
	if (!new)
	{
		free(s);
		return (NULL);
	}
	free(s);
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:25 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/21 21:34:53 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_char(char *s, char c)
{
	char	tmp[2];
	char	*new;

	tmp[0] = c;
	tmp[1] = '\0';
	new = ft_strjoin(s, tmp);
	free(s);
	return (new);
}

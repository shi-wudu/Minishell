/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 06:13:18 by seilkiv           #+#    #+#             */
/*   Updated: 2026/01/23 06:38:00 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_exit_status(char **res, int *i, t_data *data)
{
	char	*num;

	num = ft_itoa(data->last_exit_status);
	*res = ft_strjoin_free(*res, num);
	free(num);
	*i += 2;
}

// Expande uma linha de heredoc
// Apenas $VAR e $? são suportados

char	*expand_heredoc_line(const char *s, t_data *data)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] == '?')
			expand_exit_status(&res, &i, data);
		else if (s[i] == '$'
			&& (ft_isalnum(s[i + 1]) || s[i + 1] == '_'))
			expand_env_var(s, &res, &i, data);
		else
			res = append_char(res, s[i++]);
	}
	return (res);
}

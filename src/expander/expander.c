/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:25 by seilkiv           #+#    #+#             */
/*   Updated: 2025/10/21 21:34:53 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Expande a variável $? com o último exit status.

static void	expand_exit_status(char **res, int last, int *i)
{
	char	*num;

	num = ft_itoa(last);
	*res = ft_strjoin_free(*res, num);
	free(num);
	*i += 2;
}

// Expande uma variável de ambiente e junta ao resultado.

static void	append_env_value(char **res, t_data *data, const char *str, int *i)
{
	int		start;
	char	*name;
	char	*val;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	name = ft_substr(str, start, *i - start);
	if (!name)
		return ;
	val = get_env_value(data->envp, name);
	if (val)
		*res = ft_strjoin_free(*res, val);
	else
		*res = ft_strjoin_free(*res, "");
	free(name);
}

// Trata a expansão iniciada por '$'.

static void	handle_dollar(const char *str, int *i, char **res, t_data *data)
{
	if (str[*i + 1] == '{')
	{
		handle_this(str, i, res, data);
		return ;
	}
	if (str[*i + 1] == '?')
	{
		expand_exit_status(res, data->last_exit_status, i);
		return ;
	}
	if (!str[*i + 1])
	{
		*res = ft_strjoin_free(*res, "$");
		(*i)++;
		return ;
	}
	(*i)++;
	if (!ft_isalnum(str[*i]) && str[*i] != '_')
	{
		*res = ft_strjoin_free(*res, "$");
		return ;
	}
	append_env_value(res, data, str, i);
}

// Expande apenas variáveis ('$') numa string.

char	*expand_dollar_only(const char *str, t_data *data)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (str && str[i])
	{
		if (str[i] == '$')
			handle_dollar(str, &i, &res, data);
		else
		{
			res = append_char(res, str[i]);
			i++;
		}
	}
	return (res);
}

// Aplica expansão a todos os tokens WORD que permitam expansão.

void	expand_tokens(t_token *tokens, t_data *data)
{
	char	*expanded;

	while (tokens)
	{
		if (tokens->type == HEREDOC && tokens->next)
		{
			tokens = tokens->next->next;
			continue ;
		}
		if (tokens->type == WORD && !tokens->no_expand)
		{
			expanded = expand_dollar_only(tokens->value, data);
			free(tokens->value);
			tokens->value = expanded;
		}
		tokens = tokens->next;
	}
}

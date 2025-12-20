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

static void	expand_exit_status(char **res, int last, int *i)
{
	char	*num;

	num = ft_itoa(last);
	*res = ft_strjoin_free(*res, num);
	free(num);
	*i += 2;
}

static void	append_env_value(char **res, char **envp,
		const char *str, int start, int end)
{
	char	*name;
	char	*val;

	name = ft_substr(str, start, end - start);
	if (!name)
		return ;
	val = get_env_value(envp, name);
	if (val)
		*res = ft_strjoin_free(*res, val);
	else
		*res = ft_strjoin_free(*res, "");
	free(name);
}

static void	handle_dollar(const char *str, char **envp,
		int *i, char **res, int last)
{
	int	start;

	if (str[*i + 1] == '?')
	{
		expand_exit_status(res, last, i);
		return ;
	}
	if (!str[*i + 1])
	{
		*res = ft_strjoin_free(*res, "$");
		(*i)++;
		return ;
	}
	start = ++(*i);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	if (start == *i)
	{
		*res = ft_strjoin_free(*res, "$");
		return ;
	}
	append_env_value(res, envp, str, start, *i);
}

char	*expand_dollar_only(const char *str, char **envp, int last)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (str && str[i])
	{
		if (str[i] == '$')
			handle_dollar(str, envp, &i, &res, last);
		else
		{
			res = append_char(res, str[i]);
			i++;
		}
	}
	return (res);
}

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
			expanded = expand_dollar_only(tokens->value, data->envp,
					data->last_exit_status);
			free(tokens->value);
			tokens->value = expanded;
		}
		tokens = tokens->next;
	}
}

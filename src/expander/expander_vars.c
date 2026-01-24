/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 06:24:05 by seilkiv           #+#    #+#             */
/*   Updated: 2026/01/23 06:47:40 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// $$ → PID do processo
// $? → último exit status

static void	expand_special_vars(const char *s, int *i, char **res, t_data *data)
{
	char	*tmp;

	if (s[*i + 1] == '$')
	{
		tmp = ft_itoa(getpid());
		*res = ft_strjoin_free(*res, tmp);
		free(tmp);
		*i += 2;
	}
	else if (s[*i + 1] == '?')
	{
		tmp = ft_itoa(data->last_exit_status);
		*res = ft_strjoin_free(*res, tmp);
		free(tmp);
		*i += 2;
	}
}

// Expande uma variável de ambiente simples ($VAR)
// Lê o nome da variável e busca em envp

void	expand_env_var(const char *s, char **res, int *i, t_data *data)
{
	int		start;
	char	*name;
	char	*val;

	start = ++(*i);
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
		(*i)++;
	name = ft_substr(s, start, *i - start);
	val = get_env_value(data->envp, name);
	if (val)
		*res = ft_strjoin_free(*res, val);
	free(name);
}

// Trata variáveis no formato ${VAR}
// Se não fechar }, mantém literal "${"

static void	handle_braced_var(const char *str, int *i, char **res, t_data *data)
{
	int		start;
	char	*name;
	char	*val;

	if (str[*i + 1] == '{')
	{
		*i += 2;
		start = *i;
		while (str[*i] && str[*i] != '}')
			(*i)++;
		if (str[*i] != '}')
		{
			*res = ft_strjoin_free(*res, "${");
			return ;
		}
		name = ft_substr(str, start, *i - start);
		val = get_env_value(data->envp, name);
		if (val)
			*res = ft_strjoin_free(*res, val);
		free(name);
		(*i)++;
		return ;
	}
}

// Percorre uma string e expande variáveis ($VAR, $?, $$, ${VAR})
// Retorna nova string expandida

char	*expand_vars(const char *s, t_data *data)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] == '{')
			handle_braced_var(s, &i, &res, data);
		else if (s[i] == '$' && (s[i + 1] == '$' || s[i + 1] == '?'))
			expand_special_vars(s, &i, &res, data);
		else if (s[i] == '$' && (ft_isalnum(s[i + 1]) || s[i + 1] == '_'))
			expand_env_var(s, &res, &i, data);
		else
			res = append_char(res, s[i++]);
	}
	return (res);
}

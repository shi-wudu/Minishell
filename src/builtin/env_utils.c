/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-02 18:22:48 by user              #+#    #+#             */
/*   Updated: 2025-11-02 18:22:48 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char *get_env_value(char **env, char *key)
{
	int i;
	int key_len;

	if (!key || !env)
		return (NULL);

	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
		{
			//return (&env[i][key_len + 1]);
			return (env[i] + key_len + 1);
		}
		i++;
	}
	return (NULL);
}
char	**expand_env(char **env, int *count)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(*count + 2, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < *count)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			while (i > 0)
			{
				i--;
				free(new_env[i]);
			}
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	var_exists(char **env, char *var, int *var_len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (var[j] && var[j] != '=')
		j++;
	*var_len = j;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, j) == 0 && env[i][j] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	update_or_add_var(char ***env, char *var, int *count)
{
	char	**new_env;
	int		var_len;

	if (var_exists(*env, var, &var_len))
		return (1);
	new_env = expand_env(*env, count);
	if (!new_env)
		return (0);
	new_env[*count] = ft_strdup(var);
	if (!new_env[*count])
	{
		while (*count > 0)
		{
			(*count)--;
			free(new_env[*count]);
		}
		free(new_env);
		return (0);
	}
	free(*env);
	*env = new_env;
	(*count)++;
	return (1);
}

int	builtin_env(char **env)
{
	int	i;

	if (!env)
		return (1);

	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
	return (0);
}
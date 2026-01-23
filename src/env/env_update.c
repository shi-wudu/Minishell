/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marleand <marleand@student42.lisboa.pt>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:02:08 by marleand          #+#    #+#             */
/*   Updated: 2025/09/03 18:57:11 by marleand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_env_var(char **env, char *var, int var_len)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, var_len) == 0 && env[i][var_len] == '=')
		{
			tmp = ft_strdup(var);
			if (!tmp)
				return (0);
			free(env[i]);
			env[i] = tmp;
			return (1);
		}
		i++;
	}
	return (0);
}

static char	**append_env_var(char **env, char *var, int count)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (free_environment(new_env), NULL);
		i++;
	}
	new_env[i] = ft_strdup(var);
	if (!new_env[i])
		return (free_environment(new_env), NULL);
	new_env[i + 1] = NULL;
	return (new_env);
}

int	update_or_add_var(char ***env, char *var, int *count)
{
	int		var_len;
	char	**new_env;

	if (!env || !var || !count)
		return (0);
	var_len = 0;
	while (var[var_len] && var[var_len] != '=')
		var_len++;
	if (replace_env_var(*env, var, var_len))
		return (1);
	new_env = append_env_var(*env, var, *count);
	if (!new_env)
		return (0);
	free_environment(*env);
	*env = new_env;
	(*count)++;
	return (1);
}

int	env_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

void	update_pwd_vars(char ***env, const char *oldpwd, const char *newpwd)
{
	int		count;
	char	*var;

	if (!env || !*env || !newpwd)
		return ;
	count = env_count(*env);
	if (oldpwd)
	{
		var = ft_strjoin("OLDPWD=", oldpwd);
		if (var)
			update_or_add_var(env, var, &count);
		free(var);
	}
	var = ft_strjoin("PWD=", newpwd);
	if (var)
		update_or_add_var(env, var, &count);
	free(var);
}

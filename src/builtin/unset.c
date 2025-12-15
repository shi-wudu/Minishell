/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-30 16:18:49 by user              #+#    #+#             */
/*   Updated: 2025-11-30 16:18:49 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 
void	free_environment(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

static int	does_env_exist(char *env_entry, char *var_name)
{
	int	i;

	if (!env_entry || !var_name)
		return (0);
	i = 0;
	while (var_name[i] && env_entry[i])
	{
		if (var_name[i] != env_entry[i])
			return (0);
		i++;
	}
	if (var_name[i] == '\0' && env_entry[i] == '=')
		return (1);
	return (0);
}

static int	count_remaining(char **env, char **unset_list)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (unset_list[j])
		{
			if (does_env_exist(env[i], unset_list[j]))
				break ;
			j++;
		}
		if (!unset_list[j])
			count++;
		i++;
	}
	return (count);
}

static char	**build_new_env(char **env, char **unset_list, int remaining_count)
{
	char	**new_env;
	int		i;
	int		j;
	int		k;

	new_env = ft_calloc(remaining_count + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = -1;
	k = 0;
	while (env[++i])
	{
		j = 0;
		while (unset_list[j] && !does_env_exist(env[i], unset_list[j]))
			j++;
		if (!unset_list[j] && (new_env[k] = ft_strdup(env[i])))
			k++;
		else if (!unset_list[j])
			return (free_environment(new_env), NULL);
	}
	new_env[k] = NULL;
	return (new_env);
}

int	builtin_unset(char **argv, char ***env)
{
	char	**new_env;
	char	**unset_list;
	int		remaining_count;

	if (!argv || !env || !*env)
		return (1);
	unset_list = argv + 1;
	if (!unset_list[0])
		return (0);
	remaining_count = count_remaining(*env, unset_list);
	new_env = build_new_env(*env, unset_list, remaining_count);
	if (!new_env)
		return (1);
	free_environment(*env);
	*env = new_env;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marleand <marleand@student42.lisboa.pt>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:02:08 by marleand          #+#    #+#             */
/*   Updated: 2025/09/03 18:57:11 by marleand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**dup_env(char **envp)
{
	int		i;
	char	**copy;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			free_environment(copy);
			return(NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

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

/*char	*find_env_value(char **env, char *key)
{
	int	i;
	int	key_len;

	if (!key || !env)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}*/
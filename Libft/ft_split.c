/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marleand <marleand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:59:43 by marleand          #+#    #+#             */
/*   Updated: 2024/11/29 14:59:43 by marleand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ftsplot(char *stri, char **split, const char *s, int c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == c)
		{
			if (stri != s)
			{
				*(split) = ft_substr(stri, 0, s - stri);
				if (!*split++)
				{
					while (split[i])
						free(split[i++]);
					free(split);
					return (NULL);
				}
			}
			stri = (char *)s + 1;
		}
		s++;
	}
	if (stri != s)
		*(split++) = ft_substr(stri, 0, s - stri);
	return (split);
}

static size_t	ft_count(char const *s, char c)
{
	unsigned int	i;
	int				count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && (s[i] != c))
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	char	*stri;
	size_t	num;

	if (!s)
		return (NULL);
	num = ft_count(s, c);
	split = malloc(sizeof(char *) * (num + 1));
	if (split == NULL)
		return (NULL);
	stri = (char *)s;
	split = ftsplot(stri, split, s, c);
	if (!split)
		return (NULL);
	*split = 0;
	return (split - num);
}
/*#include <stdio.h>
void	printefree(char **result)
{
    int i = 0;
    while (result[i] != NULL)
    {
        printf("String[%d]: %s\n", i, result[i]);
        free(result[i]);
        i++;
    }
    free(result);
} 

 int	main(void)
{
    char **result = NULL;
    result = ft_split("hello bom dia meow!",' ');
    if (result)
        printefree(result);
    return (0);
}*/

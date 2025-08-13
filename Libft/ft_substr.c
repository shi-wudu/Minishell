/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marleand <marleand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:00:55 by marleand          #+#    #+#             */
/*   Updated: 2024/11/29 15:00:55 by marleand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	szofs;
	size_t	sublen;
	char	*substring;

	if (!s)
		return (NULL);
	szofs = ft_strlen(s);
	if (start >= szofs)
		return (ft_strdup(""));
	sublen = szofs - start;
	if (sublen > len)
		sublen = len;
	substring = malloc(sizeof(char) * (sublen + 1));
	if (!substring)
		return (NULL);
	ft_strlcpy(substring, s + start, sublen + 1);
	return (substring);
}

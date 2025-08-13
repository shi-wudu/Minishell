/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marleand <marleand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:00:02 by marleand          #+#    #+#             */
/*   Updated: 2024/11/29 15:00:02 by marleand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	szofs1;
	size_t	szofs2;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	szofs1 = ft_strlen(s1);
	szofs2 = ft_strlen(s2);
	len = szofs1 + szofs2 + 1;
	str = (char *)malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	ft_memmove(str, s1, szofs1);
	ft_memmove(str + szofs1, s2, szofs2 + 1);
	return (str);
}

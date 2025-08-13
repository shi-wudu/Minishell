/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marleand <marleand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:00:25 by marleand          #+#    #+#             */
/*   Updated: 2024/11/29 15:00:25 by marleand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*final;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	final = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!final)
		return (NULL);
	i = -1;
	while (s[++i])
		final[i] = f(i, s[i]);
	final[i] = '\0';
	return (final);
}
/*#include "stdio.h"
char	ft_toolower(unsigned int c, char o)
{
	(void)o;
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
int main()
{
	char str[] = "oLa BoM dIa";
	// char(*f)(unsigned int, char) = ft_toolower;
	printf("Result: %s\n", ft_strmapi(str, ft_toolower));
}*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marleand <marleand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:13:45 by marleand          #+#    #+#             */
/*   Updated: 2024/11/17 15:33:56 by marleand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int filler, size_t n)
{
	size_t			i;
	unsigned char	*s1;

	i = 0;
	s1 = (unsigned char *)s;
	while (i < n)
		s1[i++] = (unsigned char)filler;
	return (s);
}

/* Uncomment the main function for testing
int	main(void)
{
	char	s[];
	char	s1[];

    s[] = "Hello Bom Dia";
    s1[] = "Hello Bom Dia";
    printf("String before memset: %s\n", s);
    ft_memset(s, 77, 4);
    printf("String after ft_memset: %s\n", s);
    memset(s1, 77, 4);
    printf("String after memset: %s\n", s1);
    return (0);
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seilkiv <seilkiv@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:11:22 by seilkiv           #+#    #+#             */
/*   Updated: 2024/11/11 12:19:15 by seilkiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	n;

	n = 0;
	while (lst)
	{
		lst = lst->next;
		n++;
	}
	return (n);
}
/*#include <stdio.h>
int	main(void)
{
	t_list *node1 = ft_lstnew("Primeiro");
	t_list *node2 = ft_lstnew("Segundo");
	t_list *node3 = ft_lstnew("Terceiro");

	node1->next = node2;
	node2->next = node3;

	int size = ft_lstsize(node1);

	printf("Tamanho da lista: %d\n", size);
	free(node1);
	free(node2);
	free(node3);

	return (0);
}*/
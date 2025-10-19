/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:15:43 by vpoka             #+#    #+#             */
/*   Updated: 2024/10/08 14:04:09 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*new;

	if (!lst || !f || !del)
		return (NULL);
	res = NULL;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		if (!res)
			res = new;
		else
			ft_lstadd_back(&res, new);
		lst = lst->next;
	}
	return (res);
}

/*#include <stdio.h>
void printContent(void *content)
{
	//int *c = (int *)content;
	//ft_putnbr_fd(*c, 2);
	char *c = (char *)content;
	ft_putstr_fd(c, 2);
	ft_putchar_fd(' ', 2);
}

void *printCopy(void *content)
{
	return (content);
}

void delete(void *content)
{
	free(content);
}

int main(void)
{
	char c[] = "hello";
	char cc[] = "2.2";
	t_list *one = ft_lstnew(&c);
	t_list *two = ft_lstnew(&cc);
	ft_lstadd_back(&one, two);
	printf("first: \n");
	ft_lstiter(one, printContent);
	printf("\nsecond: \n");
	ft_lstiter(two, printContent);
	printf("\nchanged second: \n");
	two = ft_lstmap(one, printCopy, delete);
	ft_lstiter(two, printContent);
}*/
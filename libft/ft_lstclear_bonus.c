/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:26:22 by sferrad           #+#    #+#             */
/*   Updated: 2024/11/19 20:40:11 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*deltmp;

	if (!lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		deltmp = tmp;
		tmp = tmp->next;
		ft_lstdelone(deltmp, del);
	}
	*lst = NULL;
}

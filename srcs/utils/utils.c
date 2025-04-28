/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:56:04 by sferrad           #+#    #+#             */
/*   Updated: 2025/04/23 04:59:47 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*ft_lstnew_mini(char *arg, int type, t_gc_list *gc)
{
	t_token	*new;

	new = gc_malloc(sizeof(t_token), gc);
	if (!new)
		return (NULL);
	new->str = gc_strdup(arg, gc);
	new->arg = new->str;
	new->type = type;
	new->next = NULL;
	return (new);
}

t_token	*ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!new)
		return (NULL);
	if (!*lst)
	{
		*lst = new;
		return (new);
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	return (new);
}

t_token	*create_token_by_type(char *arg, t_mini *shell, t_gc_list *gc)
{
	t_token	*token;

	if (!arg)
		return (NULL);
	token = gc_malloc(sizeof(t_token), gc);
	if (!token)
		return (NULL);
	token->str = gc_strdup(arg, gc);
	token->arg = token->str;
	token->next = NULL;
	if (is_builtin(&arg))
		token->type = BUILTIN;
	else if (is_redirect(arg))
		token->type = REDIRECT;
	else if (!ft_strcmp(arg, "|"))
		token->type = PIPE;
	else if (!shell->is_arg)
	{
		token->type = CMD;
		shell->is_arg = 1;
	}
	else
		token->type = STRING;
	return (token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:12:49 by moel-hal          #+#    #+#             */
/*   Updated: 2025/04/25 16:24:31 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_envclear(t_env **env)
{
	t_env	*tmp;

	while ((*env))
	{
		tmp = (*env)->next;
		free((*env)->key);
		free((*env)->content);
		free((*env));
		(*env) = tmp;
	}
}

void	ft_redirclear(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	ft_commandclear(t_command **cmd)
{
	t_command	*tmp;

	if (!cmd || !(*cmd))
		return ;
	while (*cmd)
	{
		tmp = (*cmd)->next;
		(*cmd) = tmp;
	}
}

void	ft_tokenclear(t_token *token)
{
	t_token	*tmp;

	if (!token || !token->type)
		return ;
	while (token)
	{
		tmp = token->next;
		if (token->type != PIPE && token->str != NULL)
			free(token->str);
		free(token);
		token = tmp;
	}
}

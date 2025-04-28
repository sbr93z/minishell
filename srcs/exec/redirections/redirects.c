/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:34:32 by moel-hal          #+#    #+#             */
/*   Updated: 2025/04/25 16:21:53 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_redir	*ft_redirnew(char *str, t_redir_type type, t_mini *shell)
{
	t_redir	*redir;

	if (!str)
		return (NULL);
	redir = gc_malloc(sizeof(t_redir), shell->gc);
	if (!redir)
		return (NULL);
	redir->heredoc_content = NULL;
	redir->type = type;
	redir->file = str;
	if (type == HEREDOC)
	{
		if (get_heredoc(redir, shell) == EXIT_FAILURE)
		{
			printf("Heredoc processing failed in ft_redirnew\n");
			free(redir);
			return (NULL);
		}
	}
	redir->next = NULL;
	return (redir);
}

t_redir_type	find_redir_type(char *str)
{
	if (!str)
		return (IN);
	if (!ft_strcmp(str, ">>"))
		return (APPEND);
	if (!ft_strcmp(str, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(str, ">"))
		return (OUT);
	else
		return (IN);
}

t_redir	*ft_redirlast(t_redir *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

void	ft_rediraddback(t_redir **head, t_redir *new)
{
	if (!head)
		return ;
	if (*head)
		ft_redirlast(*head)->next = new;
	else
		*head = new;
}

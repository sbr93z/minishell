/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:28:31 by moel-hal          #+#    #+#             */
/*   Updated: 2025/04/25 16:46:09 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	handle_token_redirection(t_token **token, t_command *cmd, t_mini *shell)
{
	t_redir	*redir;

	if (!(*token)->next)
	{
		printf("Error: redirection without target file\n");
		return (0);
	}
	if (find_redir_type((*token)->arg) == HEREDOC)
		redir = ft_redirnew(gc_strdup((*token)->next->arg, shell->gc),
				find_redir_type((*token)->arg), shell);
	else
		redir = ft_redirnew(expand((*token)->next->arg, shell),
				find_redir_type((*token)->arg), shell);
	if (!redir)
		return (0);
	ft_rediraddback(&(cmd->redir), redir);
	(*token) = (*token)->next->next;
	return (1);
}

bool	handle_token(t_token **token, t_command *cmd, t_mini *shell)
{
	if (is_argument_token(*token))
		return (handle_argument(token, cmd, shell));
	else if ((*token)->type == REDIRECT)
		return (handle_token_redirection(token, cmd, shell));
	else
	{
		printf("Error: unhandled token type\n");
		return (0);
	}
}

static int	handle_heredoc_signal(t_redir *redir, char *line, t_mini *shell)
{
	printf("Heredoc processing interrupted by signal\n");
	if (redir->heredoc_content)
		free_tab(redir->heredoc_content);
	free(line);
	shell->state = g_signal;
	g_signal = 0;
	return (EXIT_FAILURE);
}

int	get_heredoc(t_redir *redir, t_mini *shell)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			return (EXIT_SUCCESS);
		if (ft_strcmp(line, redir->file) == 0)
			return (free(line), EXIT_SUCCESS);
		if (g_signal != 0)
			return (handle_heredoc_signal(redir, line, shell));
		redir->heredoc_content = add_argument(redir->heredoc_content,
				expand(line, shell), shell->gc);
		if (!redir->heredoc_content)
			return (free(line),
				printf("Failed to add line to heredoc content\n"),
				EXIT_FAILURE);
		free(line);
	}
	return (EXIT_SUCCESS);
}

void	append_heredoc_node(t_mini *shell, t_heredoc *new_node)
{
	t_heredoc	*current;

	if (!shell->preprocessed_heredocs)
		shell->preprocessed_heredocs = new_node;
	else
	{
		current = shell->preprocessed_heredocs;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

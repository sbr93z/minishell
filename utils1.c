/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:55:57 by sferrad           #+#    #+#             */
/*   Updated: 2025/04/25 16:23:46 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	free_args(t_mini *shell)
{
	int	i;

	i = 0;
	while (shell->args[i])
	{
		free(shell->args[i]);
		i++;
	}
	free(shell->args);
	shell->args = NULL;
}

void	cleanup_states(t_mini *shell)
{
	int	i;

	if (shell->buffer)
	{
		free(shell->buffer);
		shell->buffer = NULL;
	}
	i = 0;
	if (shell->args)
	{
		while (shell->args[i])
		{
			free(shell->args[i]);
			i++;
		}
		free(shell->args);
		shell->args = NULL;
	}
	if (shell->token_list)
		shell->token_list = NULL;
}

void	init_states(t_mini *shell, char **envp)
{
	shell->buf_size = 2048;
	shell->args = NULL;
	shell->token_list = NULL;
	shell->envp = envp;
	shell->is_arg = 0;
	shell->in_command = 0;
	shell->pid = getpid();
}

void	free_env_list(t_env *env_list)
{
	t_env	*tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->content)
			free(tmp->content);
		if (tmp)
			free(tmp);
	}
}

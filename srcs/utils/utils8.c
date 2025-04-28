/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:40:34 by moel-hal          #+#    #+#             */
/*   Updated: 2025/04/25 16:25:33 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_variable_lookup(char *arg, t_env **env_list)
{
	t_env	*current;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->key, arg) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

void	ft_end(t_mini *shell)
{
	if (shell->env_list)
		ft_envclear(&shell->env_list);
	if (shell->envp != NULL)
	{
		free_tab(shell->envp);
		shell->envp = NULL;
	}
}

void	free_all_heredoc(t_command *cmd)
{
	t_redir	*current_redir;

	while (cmd)
	{
		current_redir = cmd->redir;
		while (current_redir)
		{
			if (current_redir && current_redir->type == HEREDOC
				&& current_redir->heredoc_content)
			{
				current_redir->heredoc_content = NULL;
			}
			current_redir = current_redir->next;
		}
		cmd = cmd->next;
	}
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	s3_len;
	char	*ret;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3_len = ft_strlen(s3);
	ret = malloc(s1_len + s2_len + s3_len + 1);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1, s1_len + 1);
	ft_strlcpy(ret + s1_len, s2, s2_len + 1);
	ft_strlcpy(ret + s1_len + s2_len, s3, s3_len + 1);
	return (ret);
}

void	ft_tabupdate(t_mini *shell)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	env = shell->env_list;
	tmp = env;
	i = 1;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	shell->envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env)
	{
		shell->envp[i] = ft_strjoin3(env->key, "=", env->content);
		i++;
		env = env->next;
	}
	shell->envp[i] = 0;
}

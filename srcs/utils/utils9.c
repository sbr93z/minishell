/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:39:11 by sferrad           #+#    #+#             */
/*   Updated: 2025/04/28 19:26:09 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	read_input(t_mini *shell)
{
	shell->buffer = readline("Minishell > ");
	if (!shell->buffer)
	{
		printf("exit\n");
		return (0);
	}
	if (*shell->buffer)
		add_history(shell->buffer);
	return (1);
}

void	clear_buffers(t_mini *shell)
{
	shell->is_arg = 0;
	if (shell->args)
		free_args(shell);
	if (shell->token_list)
		shell->token_list = NULL;
	if (shell->buffer)
		free(shell->buffer);
}

void	free_tab(char **tabl)
{
	int	i;

	if (!tabl)
		return ;
	i = 0;
	while (tabl[i])
	{
		if (tabl[i] != NULL)
			free(tabl[i]);
		i++;
	}
	free(tabl);
}

void	restore_tokens(t_token *token_list)
{
	t_token	*current;
	int		i;

	current = token_list;
	while (current)
	{
		i = 0;
		while (current->arg && current->arg[i])
		{
			if (current->arg[i] < 0)
				current->arg[i] *= -1;
			i++;
		}
		current = current->next;
	}
}

char	*strip_quotes(char *str, t_gc_list *gc)
{
	size_t	len;
	char	*res;

	(void)gc;
	if (!str)
		return (NULL);
	len = strlen(str);
	if (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '\"'
				&& str[len - 1] == '\"')))
	{
		res = ft_substr(str, 1, len - 2);
		return (res);
	}
	return (ft_strdup(str));
}

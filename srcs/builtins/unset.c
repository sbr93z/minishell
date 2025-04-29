/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:15:57 by moel-hal          #+#    #+#             */
/*   Updated: 2025/04/29 11:58:47 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(t_env **env, char *var, t_mini *shell)
{
	t_env	*prev;
	t_env	*curr;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, var) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->content);
			free(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	shell->state = 0;
	return (0);
}

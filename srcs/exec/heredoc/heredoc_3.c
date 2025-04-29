/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:38:32 by moel-hal          #+#    #+#             */
/*   Updated: 2025/04/29 11:57:21 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	var_update(t_env **env_list, char *key, char *content)
{
	t_env	*current;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->content);
			current->content = content;
			free(key);
			return ;
		}
		current = current->next;
	}
	env_add_back(env_list, env_new_node(key, content));
}

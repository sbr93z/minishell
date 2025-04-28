/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 02:12:17 by moel-hal          #+#    #+#             */
/*   Updated: 2025/04/22 21:45:16 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// char	**ft_tabdup(char **tabl)
// {
// 	char	**dup;
// 	int		i;
// 	int		size;

// 	if (!tabl)
// 		return (NULL);
// 	size = 0;
// 	while (tabl[size])
// 		size++;
// 	dup = (char **)malloc(sizeof(char *) * (size + 1));
// 	if (!dup)
// 		return (NULL);
// 	i = 0;
// 	while (i < size)
// 	{
// 		dup[i] = ft_strdup(tabl[i]);
// 		if (!dup[i])
// 		{
// 			while (--i >= 0)
// 				free(dup[i]);
// 			return (free(dup), NULL);
// 		}
// 		i++;
// 	}
// 	return (dup[size] = NULL, dup);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 03:26:19 by sferrad           #+#    #+#             */
/*   Updated: 2025/01/05 19:43:12 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_is_a_new_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_gnlstrlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_gnlstrjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s3;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	s3 = malloc((ft_gnlstrlen(s1) + ft_gnlstrlen(s2) + 1) * sizeof(char));
	if (!s3)
		return (free(s1), NULL);
	i = -1;
	while (s1[++i])
		s3[i] = s1[i];
	j = 0;
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\0';
	free(s1);
	return (s3);
}

char	*get_next_line(int fd, char **stash)
{
	char	*buffer;
	char	*line;
	int		readf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	readf = 1;
	*stash = ft_stash(buffer, readf, *stash, fd);
	if (!(*stash))
		return (NULL);
	line = ft_extract_line(*stash);
	*stash = ft_save(*stash);
	return (line);
}

// int	main(int argc, char **argv)
// {
// 	if (argc != 2)
// 	{
// 		fprintf(stderr, "Usage: %s <fichier>\n", argv[0]);
// 		return (1);
// 	}

// 	FILE *file = fopen(argv[1], "r");
// 	if (!file)
// 	{
// 		perror("Erreur d'ouverture du fichier");
// 		return (1);
// 	}

// 	// Conversion du FILE* en descripteur de fichier (int)
// 	int fd = fileno(file);
// 	char *line;

// 	// Lire ligne par ligne avec get_next_line
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line); // Affiche la ligne lue
// 		free(line);         // Libère la mémoire allouée pour la ligne
// 	}
// 	fclose(file); // Ferme le fichier
// 	return (0);
// }
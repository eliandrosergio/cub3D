/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:48:42 by efaustin          #+#    #+#             */
/*   Updated: 2025/03/26 13:39:21 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_grid(char **grid, int height)
{
	int		i;

	i = 0;
	while (i <= height)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
	grid = NULL;
	return ;
}

char	**allocate_grid(int width, int height)
{
	int		i;
	char	**grid;

	i = 0;
	grid = ft_calloc((height + 1), sizeof(char *));
	if (!grid)
	{
		perror("Erro ao alocar a grelha do mapa\n");
		free(grid);
		return (NULL);
	}
	while (i < height)
	{
		grid[i] = ft_calloc(width, sizeof(int));
		if (!grid[i])
		{
			perror("Erro ao alocar linha da grelha do mapa\n");
			free_grid(grid, i);
			return (NULL);
		}
		i++;
	}
	return (grid);
}

char	*trim_spaces(char *line, char *srch)
{
	char	*trimmed;

	trimmed = NULL;
	if (line)
	{
		trimmed = ft_strtrim(line, srch);
		free(line);
		if (!trimmed)
		{
			print_erro("Erro ao modificar uma linha do arquivo\n");
			return (NULL);
		}
	}
	return (trimmed);
}

int	is_only_spaces(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	get_line_file(t_game *game)
{
	int		fd;
	char	*line;

	fd = open(game->map.path_file, O_RDONLY);
	if (fd <= 0)
	{
		print_erro("Erro ao abrir o arquivo do mapa\n");
		close(fd);
		return (1);
	}
	line = NULL;
	while (1)
	{
		free(line);
		line = get_next_line(fd, 0);
		if (!line)
			break ;
		game->map.height_file++;
	}
	free(line);
	close(fd);
	return (0);
}

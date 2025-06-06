/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elian <elian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:48:47 by efaustin          #+#    #+#             */
/*   Updated: 2025/03/26 14:08:12 by elian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	get_map_init_line(t_game *game, int y)
{
	int		fd;
	char	*line;

	fd = open(game->map.path_file, O_RDONLY);
	if (fd <= 0)
	{
		print_erro("Erro ao ler o arquivo do mapa\n");
		return (-1);
	}
	line = get_next_line(fd, 0);
	while (--y)
	{
		free(line);
		line = get_next_line(fd, 0);
	}
	free(line);
	return (fd);
}

static int	get_map_tam(t_game *game, int fd2)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = get_next_line(fd2, 0);
		if (!line)
			break ;
		if (line[0] == '\n' || is_only_spaces(line))
			return (return_erro("O mapa não pode possuir linhas vazias "
					"ou apenas com espaços\n", 0, 0, line));
		if (((int)(ft_strlen(line))) > game->map.width)
			game->map.width = ((int)ft_strlen(line));
		free(line);
		game->map.height++;
	}
	game->map.height++;
	return (0);
}

static int	fill_helper(t_game *game, char *line, int *fd, int *i)
{
	int		y;
	int		status;

	y = 0;
	status = 0;
	while (*i)
	{
		if (line)
		{
			status = check_map_chars(game, line, y);
			free(line);
		}
		(*i)--;
		y++;
		if (status != 0)
			break ;
		line = get_next_line(*fd, 0);
	}
	return (status);
}

int	fill_map(t_game *game, char *line, int *fd, int *i)
{
	int		fd2;
	int		status;

	status = 0;
	fd2 = get_map_init_line(game, (*i));
	if (fd2 == -1)
	{
		free(line);
		return (1);
	}
	if (get_map_tam(game, fd2))
	{
		free(line);
		return (1);
	}
	close(fd2);
	game->map.grid = allocate_grid(game->map.width, game->map.height);
	(*i) = game->map.height;
	status = fill_helper(game, line, fd, i);
	if (status == 0)
		game->map.grid[game->map.height] = '\0';
	if (!game->player.dir && !status)
		return (return_erro("Posição e direção do player não encontrado"
				" no mapa\n", 0, 0, 0));
	return (status);
}

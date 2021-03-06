/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <ofedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 13:47:02 by ofedorov          #+#    #+#             */
/*   Updated: 2017/09/19 13:51:31 by sasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static bool		parse_room(t_map *map, char *line, int room_number)
{
	char	**input;
	int		index;

	input = ft_strsplit(line, ' ');
	if (!input)
		return (false);
	if (input[0] && !input[1])
	{
		map->rooms = ft_strlst_toarr(map->rooms_list);
		map->rooms_count = room_number;
		map->links = (bool**)ft_memalloc(sizeof(bool*) * room_number);
		index = -1;
		while (++index < map->rooms_count)
			map->links[index] = (bool*)ft_memalloc(sizeof(bool) * room_number);
	}
	else if (input[0] && input[1] && input[2])
		ft_lstaddend(&(map->rooms_list), ft_lstnew(input[0],
									ft_strlen(input[0]) + 1));
	else
	{
		ft_strsplit_free(input);
		free_and_exit(map, FAILURE);
	}
	ft_strsplit_free(input);
	return (map->rooms_count == -1) ? true : false;
}

static void		parse_link(t_map *map, char *line)
{
	char	**input;
	int		index1;
	int		index2;

	input = ft_strsplit(line, '-');
	if (!map->rooms || !map->links || !input[1])
	{
		ft_strsplit_free(input);
		free_and_exit(map, FAILURE);
	}
	index1 = get_index(map, input[0]);
	index2 = get_index(map, input[1]);
	map->links[index1][index2] = true;
	map->links[index2][index1] = true;
	ft_strsplit_free(input);
}

static void		parse_input(t_map *map, char *line)
{
	static int		room_number = 0;
	static bool		parse_links = false;

	if (ft_strequ(line, "##start"))
		map->start = room_number;
	else if (ft_strequ(line, "##end"))
		map->end = room_number;
	else if (line[0] != '#')
	{
		if (!parse_links)
			parse_links = !parse_room(map, line, room_number);
		if (parse_links)
			parse_link(map, line);
		else
			room_number++;
	}
}

static t_map	*init_map(void)
{
	t_map	*map;

	map = (t_map*)ft_memalloc(sizeof(t_map));
	map->ants_count = -1;
	map->start = -1;
	map->end = -1;
	map->rooms_count = -1;
	map->rooms_list = 0;
	map->rooms = 0;
	map->links = 0;
	map->path = 0;
	map->path_length = -1;
	map->input = 0;
	return (map);
}

t_map			*parse_file(void)
{
	char	*line;
	int		return_value;
	t_map	*map;

	map = init_map();
	if ((return_value = get_next_line(0, &line)) == 1)
	{
		map->ants_count = ft_atoi(line);
		ft_lstaddend(&(map->input), ft_lstnew(line, ft_strlen(line) + 1));
		free(line);
		while ((return_value = get_next_line(0, &line)) == 1)
		{
			if (!line || !(*line))
				free_and_exit(map, FAILURE);
			ft_lstaddend(&(map->input), ft_lstnew(line, ft_strlen(line) + 1));
			parse_input(map, line);
			free(line);
		}
	}
	if (return_value == -1 || (return_value == 0 && !(map->input)) ||
		map->rooms_count == -1 || map->start == -1 || map->end == -1 ||
		map->start >= map->rooms_count || map->end >= map->rooms_count ||
		map->ants_count < 1 || map->start == map->end)
		free_and_exit(map, FAILURE);
	return (map);
}

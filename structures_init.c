#include "includes/main_header.h"

t_characters		*characters_init(void)
{
	t_characters	*character;

	character = malloc(2 * sizeof(t_characters));
	character[0].id = 0;
	character[1].id = 1;
	return (character);
}

t_map				**map_init(int map_size_x, int map_size_y)
{
	int		i;
	int		j;
	t_map	**map;

	map = malloc(map_size_y * sizeof(t_map));
	for (i = 0; i < map_size_x; i++)
		map[i] = malloc(map_size_x * sizeof(t_map));

	for (i = 0; i < map_size_y; i++)
	{
		for (j = 0; j < map_size_x; j++)
		{
			map[i][j].terrain = '*';
			map[i][j].spotting_range_bonus = 0;
			map[i][j].unit_on_tile = NULL;
		}
	}
	return (map);
}

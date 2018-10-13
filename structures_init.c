#include "includes/main_header.h"

/*
	Création du tableau des personnages
	On les malloc et leur donne un id
*/
t_characters		*characters_init(void)
{
	t_characters	*character;

	character = malloc(2 * sizeof(t_characters));
	character[0].id = 0;
	character[1].id = 1;
	return (character);
}

/*
	Création de la carte
	On malloc et donne quelques données à chaque case de carte
*/
t_map				**map_init(int map_size_x, int map_size_y)
{
	int		i;
	int		j;
	int		random;
	t_map	**map;

	map = malloc(map_size_y * sizeof(t_map));
	for (i = 0; i < map_size_x; i++)
		map[i] = malloc(map_size_x * sizeof(t_map));

	for (i = 0; i < map_size_y; i++)
	{
		for (j = 0; j < map_size_x; j++)
		{
			random = rand() % 4;
			map[i][j].terrain = 'P';
			map[i][j].height_level = 1;
			map[i][j].unit_on_tile = NULL;
			map[i][j].x = j;
			map[i][j].y = i;
		}
	}
	return (map);
}

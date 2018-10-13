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
	Fonctions de créations de structures de carte
	paramètres x/y	= position actuelle de la case étudiée

	tab_x/y			= tableau de la taille de structure_size
		Chaque int à l'intérieur du tableau correspond à la modification apportée aux paramètres x/y
	temp_x/y		= position x/y acuelle + modification du tab_x/y
*/
void				w(t_map **map, int y, int x)
{
	const int	structure_size = 10;
	int			tab_x[] = {-3, -2, -1, 0, 0, 1, 1, 2, 3, 4};
	int			tab_y[] = {1, 1, 1, 1, 0, 0, -1, -1, -1, -1};
	int			temp_x;
	int			temp_y;
	int			i;
	
	for (i = 0; i < structure_size; i++)
	{
		temp_x = x + tab_x[i];
		temp_y = y + tab_y[i];
		if (temp_x >= 0 && temp_x <= 19 && temp_y >= 0 && temp_y <= 19 && map[temp_y][temp_x].structure_on_tile == false)
		{
			map[temp_y][temp_x].height_level = 1;
			map[temp_y][temp_x].terrain = 'W';
			map[temp_y][temp_x].structure_on_tile = true;
		}
	}
}

void				p(t_map **map, int y, int x)
{
	const int	structure_size = 9;
	int			tab_x[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
	int			tab_y[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
	int			temp_x;
	int			temp_y;
	int			i;

	for (i = 0; i < structure_size; i++)
	{
		temp_x = x + tab_x[i];
		temp_y = y + tab_y[i];
		if (temp_x >= 0 && temp_x <= 19 && temp_y >= 0 && temp_y <= 19 && map[temp_y][temp_x].structure_on_tile == false)
		{
			map[temp_y][temp_x].height_level = 1;
			map[temp_y][temp_x].terrain = 'P';
			map[temp_y][temp_x].structure_on_tile = true;
		}
	}
}

void				f(t_map **map, int y, int x)
{
	const int	structure_size = 8;
	int			tab_x[] = {-1, -1, -1, -1, 0, 0, 0, 0};
	int			tab_y[] = {-1, 0, 1, 2, -1, 0, 1, 2};
	int			temp_x;
	int			temp_y;
	int			i;

	for (i = 0; i < structure_size; i++)
	{
		temp_x = x + tab_x[i];
		temp_y = y + tab_y[i];
		if (temp_x >= 0 && temp_x <= 19 && temp_y >= 0 && temp_y <= 19 && map[temp_y][temp_x].structure_on_tile == false)
		{
			map[temp_y][temp_x].height_level = 1;
			map[temp_y][temp_x].terrain = 'F';
			map[temp_y][temp_x].structure_on_tile = true;
		}
	}
}

void				h(t_map **map, int y, int x)
{
	const int	structure_size = 5;
	int			tab_x[] = {-1, 0, 0, 0, 1};
	int			tab_y[] = {0, -1, 0, 1, 0};
	int			temp_x;
	int			temp_y;
	int			i;

	for (i = 0; i < structure_size; i++)
	{
		temp_x = x + tab_x[i];
		temp_y = y + tab_y[i];
		if (temp_x >= 0 && temp_x <= 19 && temp_y >= 0 && temp_y <= 19 && map[temp_y][temp_x].structure_on_tile == false)
		{
			map[temp_y][temp_x].height_level = 2;
			map[temp_y][temp_x].terrain = 'H';
			map[temp_y][temp_x].structure_on_tile = true;
		}
	}
}

/*
	Création de la carte
	On malloc et donne quelques données à chaque case de carte, puis on lance un aléatoire qui décide quelle structure donner à chaque case
*/
t_map				**map_init(int map_size_x, int map_size_y)
{
	int		i;
	int		j;
	int		random;
	t_map	**map;

	map = malloc(map_size_y * sizeof(t_map));				// On malloc la carte
	for (i = 0; i < map_size_x; i++)
		map[i] = malloc(map_size_x * sizeof(t_map));
	for (i = 0; i < map_size_y; i++)						// Pour toutes les cases de la carte : on indique qu'il n'y a rien dessus
		for (j = 0; j < map_size_x; j++)
			map[i][j].structure_on_tile = false;
	for (i = 0; i < map_size_y; i++)						// Pour toutes les cases de la carte : on donne une structure
	{
		for (j = 0; j < map_size_x; j++)
		{
			random = rand() % 8;
			map[i][j].unit_on_tile = NULL;
			map[i][j].x = j;
			map[i][j].y = i;
			if (map[i][j].structure_on_tile == false)
			{
				if (random <= 2)
					p(map, i, j);
				else if (random == 3 || random == 4)
					w(map, i, j);
				else if (random == 5 || random == 6)
					f(map, i, j);
				else if (random == 7)
					h(map, i, j);
			}
		}
	}
	return (map);
}

#include "../../includes/main_header.h"

/*
	Fonctions de créations de structures de carte
	paramètres x/y	= position actuelle de la case étudiée

	tab_x/y			= tableau de la taille de structure_size
		Chaque int à l'intérieur du tableau correspond à la modification apportée aux paramètres x/y
	temp_x/y		= position x/y acuelle + modification du tab_x/y
	random			= pour possiblement inversé certains itinéraires (ex : une rivière qui va de gauche à droite en montant descendra à la place
*/
void				river_ltr(t_map **map, int y, int x)
{
	const int	structure_size = 7;
	int			tab_x[] = {0, 1, 2, 3, 3, 4, 5};
	int			tab_y[] = {0, 0, 0, 0, 1, 1, 1};
	int			temp_x;
	int			temp_y;
	int			i;
	int			random;

	random = rand() % 2;
	if (random == 1)
		for (i = 0; i < structure_size; i++)
			tab_y[i] -= tab_y[i];
	for (i = 0; i < structure_size; i++)
	{
		temp_x = x + tab_x[i];
		temp_y = y + tab_y[i];
		if (temp_x >= 0 && temp_x <= 19 && temp_y >= 0 && temp_y <= 19 && map[temp_y][temp_x].structure_on_tile == false)
		{
			map[temp_y][temp_x].height_level = 1;
			map[temp_y][temp_x].terrain = 'W';
			map[temp_y][temp_x].structure_on_tile = true;	
			map[temp_y][temp_x].structure_number = 1;
		}
	}
}

void				river_htl(t_map **map, int y, int x)
{
	const int	structure_size = 8;
	int			tab_x[] = {0, 0, 0, 0, 1, 1, 2, 2};
	int			tab_y[] = {0, 1, 2, 3, 3, 4, 4, 5};
	int			temp_x;
	int			temp_y;
	int			i;	
	int			random;

	random = rand() % 2;
	if (random == 1)
		for (i = 0; i < structure_size; i++)
			tab_x[i] -= tab_x[i];
	for (i = 0; i < structure_size; i++)
	{
		temp_x = x + tab_x[i];
		temp_y = y + tab_y[i];
		if (temp_x >= 0 && temp_x <= 19 && temp_y >= 0 && temp_y <= 19 && map[temp_y][temp_x].structure_on_tile == false)
		{
			map[temp_y][temp_x].height_level = 1;
			map[temp_y][temp_x].terrain = 'W';
			map[temp_y][temp_x].structure_on_tile = true;	
			map[temp_y][temp_x].structure_number = 2;
		}
	}
}

void				lake(t_map **map, int y, int x)
{
	const int	structure_size = 13;
	int			tab_x[] = {-2, -1, -1, -1, 0, 0, 0, 0, 0, 1, 1, 1, 2};
	//int			tab_y[] = {1, 0, 1, 2, -1, 0, 1, 2, 3, 0, 1, 2, 1};
	int			tab_y[] = {0, -1, 0, 1, -2, -1, 0, 1, 2, -1, 0, 1, 0};
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
			map[temp_y][temp_x].structure_number = 3;
		}
	}
}

/*
	On choisit aléatoirement quelle structure de x type prendre
	paramètres x/y	= position actuelle de la case étudiée
	int random = Utilisé pour choisir quel structure prendre
*/
void				water(t_map **map, int y, int x)
{
	int		random;

	random = rand() % 9;
	if (random <= 3)
	{
		if (x - 1 >= 0 && map[y][x - 1].structure_number == 3)
			river_ltr(map, y, x);
		else
			river_htl(map, y, x);
	}
	else if (random <= 7)
	{
		if (y - 1 >= 0 && map[y - 1][x].structure_number == 3)
			river_htl(map, y, x);
		else
			river_ltr(map, y, x);
	}
	else
		lake(map, y, x);
}

void				forest_ltr(t_map **map, int y, int x)
{
	const int	structure_size = 7;
	int			tab_x[] = {0, 1, 2, 3, 3, 4, 5};
	int			tab_y[] = {0, 0, 0, 0, 1, 1, 1};
	int			temp_x;
	int			temp_y;
	int			i;
	int			random;

	random = rand() % 2;
	if (random == 1)
		for (i = 0; i < structure_size; i++)
			tab_y[i] -= tab_y[i];
	for (i = 0; i < structure_size; i++)
	{
		temp_x = x + tab_x[i];
		temp_y = y + tab_y[i];
		if (temp_x >= 0 && temp_x <= 19 && temp_y >= 0 && temp_y <= 19 && map[temp_y][temp_x].structure_on_tile == false)
		{
			map[temp_y][temp_x].height_level = 1;
			map[temp_y][temp_x].terrain = 'F';
			map[temp_y][temp_x].structure_on_tile = true;	
			map[temp_y][temp_x].structure_number = 1;
		}
	}
}

void				forest_htl(t_map **map, int y, int x)
{
	const int	structure_size = 8;
	int			tab_x[] = {0, 0, 0, 0, 1, 1, 2, 2};
	int			tab_y[] = {0, 1, 2, 3, 3, 4, 4, 5};
	int			temp_x;
	int			temp_y;
	int			i;	
	int			random;

	random = rand() % 2;
	if (random == 1)
		for (i = 0; i < structure_size; i++)
			tab_x[i] -= tab_x[i];
	for (i = 0; i < structure_size; i++)
	{
		temp_x = x + tab_x[i];
		temp_y = y + tab_y[i];
		if (temp_x >= 0 && temp_x <= 19 && temp_y >= 0 && temp_y <= 19 && map[temp_y][temp_x].structure_on_tile == false)
		{
			map[temp_y][temp_x].height_level = 1;
			map[temp_y][temp_x].terrain = 'F';
			map[temp_y][temp_x].structure_on_tile = true;	
			map[temp_y][temp_x].structure_number = 2;
		}
	}
}

void				big_forest(t_map **map, int y, int x)
{
	const int	structure_size = 13;
	int			tab_x[] = {-2, -1, -1, -1, 0, 0, 0, 0, 0, 1, 1, 1, 2};
	//int			tab_y[] = {1, 0, 1, 2, -1, 0, 1, 2, 3, 0, 1, 2, 1};
	int			tab_y[] = {0, -1, 0, 1, -2, -1, 0, 1, 2, -1, 0, 1, 0};
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
			map[temp_y][temp_x].structure_number = 3;
		}
	}
}
void				plains(t_map **map, int y, int x)
{
	int		random;

	random = rand() % 9;
	if (random <= 3)
	{
		if (x - 1 >= 0 && map[y][x - 1].structure_number == 3)
			forest_ltr(map, y, x);
		else
			forest_htl(map, y, x);
	}
	else if (random <= 7)
	{
		if (y - 1 >= 0 && map[y - 1][x].structure_number == 3)
			forest_htl(map, y, x);
		else
			forest_ltr(map, y, x);
	}
	else
		big_forest(map, y, x);
}

void				forests(t_map **map, int y, int x)
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

void				hills(t_map **map, int y, int x)
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

#include "../includes/main_header.h"

/*
	Affiche la carte
	int owner = l'id du joueur, afin de faire les fonctions d'appartenance de troupes facilement
*/
void				ft_print_map(t_map **map, t_units *unit, int map_size_x, int map_size_y, int owner)
{
	int		i;
	int		j;

	printf("\n\n\n");
	for (i = 0; i < map_size_y; i++)
	{
		owner = 0;
		printf("\t");
		for (j = 0; j < map_size_x; j++)
		{
			if (map[i][j].unit_on_tile != NULL && (map[i][j].unit_on_tile->owner == owner || (map[i][j].unit_on_tile->owner == !owner && ft_show_enemy(map, map[i][j].unit_on_tile, owner) == 1)))
				printf("%s%s%c ", ft_select_font_color(map, unit, i, j, owner), ft_select_background_color(map, map[i][j].terrain), map[i][j].unit_on_tile->sigle);
			else
				printf("%s%s  ", ft_select_font_color(map, unit, i, j, owner), ft_select_background_color(map, map[i][j].terrain));
		}
		printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
		owner = 1;
		for (j = 0; j < map_size_x; j++)
		{
			if (map[i][j].unit_on_tile != NULL && (map[i][j].unit_on_tile->owner == owner || (map[i][j].unit_on_tile->owner == !owner && ft_show_enemy(map, map[i][j].unit_on_tile, owner) == 1)))
				printf("%s%s%c ", ft_select_font_color(map, unit, i, j, owner), ft_select_background_color(map, map[i][j].terrain), map[i][j].unit_on_tile->sigle);
			else
				printf("%s%s  ", ft_select_font_color(map, unit, i, j, owner), ft_select_background_color(map, map[i][j].terrain));
		}
		printf("\n");
	}
	printf(BACKGROUND_DEFAULT "\n\n");
	printf(FONT_DEFAULT "\n\n");
}

/*
	Savoir si l'unité ennemie est vue
	On ratisse sur une zone de 12, et si après les calculs on découvre qu'une unité alliée peut la voir, on l'affiche
	Retourne 1 si on peut voir l'ennemi, 0 sinon
*/
int					ft_show_enemy(t_map **map, t_units *unit, int owner)
{
	int		i;
	int		j;
	int		k;
	int		l;

	for (i = unit->pos_y - 6; i < unit->pos_y + 6; i++)
		for (j = unit->pos_x - 6; j < unit->pos_x + 6; j++)
			if ((i >= 0 && i <= 19 && j >= 0 && j <= 19) && map[i][j].unit_on_tile != NULL && map[i][j].unit_on_tile->owner == owner)
			{
				for (k = i - unit->pos_y; k < 0; k = -k);
				for (l = j - unit->pos_x; l < 0; l = -l);
				if (map[i][j].unit_on_tile->spotting_range >= k && map[i][j].unit_on_tile->spotting_range >= l)
					return (1);
			}
	return (0);
}

/*
	Choisi la couleur de police (utilisée pour les unités)
	Si on accède à la fonction depuis le menu d'unité, l'unité sélectionnée sera jaune
*/
char				*ft_select_font_color(t_map **map, t_units *unit, int i, int j, int owner)
{
	if (map[i][j].unit_on_tile != NULL && map[i][j].unit_on_tile->owner == owner)
	{
		if (map[i][j].unit_on_tile == unit)
			return (FONT_LIGHT_YELLOW);
		return (FONT_BLUE);
	}
	else if (map[i][j].unit_on_tile != NULL && map[i][j].unit_on_tile->owner != owner && ft_show_enemy(map, map[i][j].unit_on_tile, owner) == 1)
		return (FONT_RED);
	else
		return (FONT_DEFAULT);
}

/*
	Choisir la couleur de fond (en fonction du terrain)
*/
char				*ft_select_background_color(t_map **map, char terrain)
{
	if (terrain == 'P')
		return (BACKGROUND_LIGHT_GREEN);
	else if (terrain == 'H')
		return (BACKGROUND_YELLOW);
	else if (terrain == 'F')
		return (BACKGROUND_GREEN);
	else if (terrain == 'W')
		return (BACKGROUND_LIGHT_CYAN);
}

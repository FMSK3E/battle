#include "includes/main_header.h"

void				ft_print_map(t_map **map, int map_size_x, int map_size_y, int nb_players, int owner)
{
	int		i;
	int		j;

	printf("\n\n\n");
	for (i = 0; i < map_size_y; i++)
	{
		owner = 0;
		for (j = 0; j < map_size_x; j++)
		{
			if (map[i][j].unit_on_tile != NULL && (map[i][j].unit_on_tile->owner == owner || (map[i][j].unit_on_tile->owner == !owner && ft_show_enemy(map, map[i][j].unit_on_tile, owner) == 1)))
				printf("%s%s%c ", ft_select_font_color(map, i, j, owner), ft_select_background_color(map, map[i][j].terrain), map[i][j].unit_on_tile->sigle);
			else
				printf("%s%s%c ", ft_select_font_color(map, i, j, owner), ft_select_background_color(map, map[i][j].terrain), map[i][j].terrain);
		}
		printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
		owner = 1;
		for (j = 0; j < map_size_x; j++)
		{
			if (map[i][j].unit_on_tile != NULL && (map[i][j].unit_on_tile->owner == owner || (map[i][j].unit_on_tile->owner == !owner && ft_show_enemy(map, map[i][j].unit_on_tile, owner) == 1)))
				printf("%s%s%c ", ft_select_font_color(map, i, j, owner), ft_select_background_color(map, map[i][j].terrain), map[i][j].unit_on_tile->sigle);
			else
				printf("%s%s  ", ft_select_font_color(map, i, j, owner), ft_select_background_color(map, map[i][j].terrain));
		}
		printf("\n");
	}
	printf(BACKGROUND_DEFAULT "\n\n");
	printf(FONT_DEFAULT "\n\n");
}

int					ft_show_enemy(t_map **map, t_units *unit, int owner)
{
	int		i;
	int		j;
	int		k;
	int		l;

	for (i = unit->pos_y - 6; i < unit->pos_y + 6; i++)
		for (j = unit->pos_x - 6; j < unit->pos_x + 6; j++)
			if (i >= 0 && i <= 19 && j >= 0 && j <= 19)
				if (map[i][j].unit_on_tile != NULL && map[i][j].unit_on_tile->owner == owner)
				{
					k = i - unit->pos_y;
					l = j - unit->pos_x;
					if (k < 0)
						k = -k;
					if (l < 0)
						l = -l;
					if (map[i][j].unit_on_tile->spotting_range + map[i][j].spotting_range_bonus >= k && map[i][j].unit_on_tile->spotting_range >= l)
						return (1);
				}
	return (0);
}

char				*ft_select_font_color(t_map **map, int i, int j, int owner)
{
	if (map[i][j].unit_on_tile != NULL && map[i][j].unit_on_tile->owner == owner)
		return (FONT_BLUE);
	else if (map[i][j].unit_on_tile != NULL && map[i][j].unit_on_tile->owner != owner && ft_show_enemy(map, map[i][j].unit_on_tile, owner) == 1)
		return (FONT_RED);
	else
		return (FONT_DEFAULT);
}

char				*ft_select_background_color(t_map **map, char terrain)
{
	if (terrain == '*')
		return (BACKGROUND_LIGHT_GREEN);
	else if (terrain == 'H')
		return (BACKGROUND_YELLOW);
	else if (terrain == 'F')
		return (BACKGROUND_GREEN);
	else if (terrain == 'W')
		return (BACKGROUND_LIGHT_CYAN);
}

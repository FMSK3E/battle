#include "includes/main_header.h"

void				print_map(t_map **map, int map_size_x, int map_size_y, int nb_players, int owner, int enemy)
{
	int		i;
	int		j;

	printf("\n\n\n");
	for (i = 0; i < map_size_y; i++)
	{
		owner = 0;
		enemy = 1 - owner;
		for (j = 0; j < map_size_x; j++)
		{
			if (map[i][j].unit_on_tile != NULL && (map[i][j].unit_on_tile->owner == owner || (map[i][j].unit_on_tile->owner == 1 - owner && show_enemy(map, i, j, owner, enemy) == 1)))
				printf("%s%s%c ", select_font_color(map, i, j, owner, enemy), select_background_color(map, i, j), map[i][j].unit_on_tile->sigle);
			else
				printf("%s%s  ", select_font_color(map, i, j, owner, enemy), select_background_color(map, i, j));
		}
		printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
		owner = 1;
		enemy = 1 - owner;
		for (j = 0; j < map_size_x; j++)
		{
			if (map[i][j].unit_on_tile != NULL && (map[i][j].unit_on_tile->owner == owner || (map[i][j].unit_on_tile->owner == 1 - owner && show_enemy(map, i, j, owner, enemy) == 1)))
				printf("%s%s%c ", select_font_color(map, i, j, owner, enemy), select_background_color(map, i, j), map[i][j].unit_on_tile->sigle);
			else
				printf("%s%s  ", select_font_color(map, i, j, owner, enemy), select_background_color(map, i, j));
		}
		printf("\n");
	}
	printf(BACKGROUND_DEFAULT "\n\n");
	printf(FONT_DEFAULT "\n\n");
}

int					show_enemy(t_map **map, int i, int j, int owner, int enemy)
{
	int		k;
	int		l;
	int		m;
	int		n;

	for (k = i - 6; k < i + 6; k++)
		for (l = j - 6; l < j + 6; l++)
			if (k >= 0 && k <= 19 && l >= 0 && l <= 19)
				if (map[k][l].unit_on_tile != NULL && map[k][l].unit_on_tile->owner == owner)
				{
					m = k - i;
					n = l - j;
					if (m < 0)
						m = -m;
					if (n < 0)
						n = -n;
					if (map[k][l].unit_on_tile->spotting_range + map[k][l].spotting_range_bonus >= m && map[k][l].unit_on_tile->spotting_range >= n)
						return (1);
				}
	return (0);
}

char				*select_font_color(t_map **map, int i, int j, int owner, int enemy)
{
	if (map[i][j].unit_on_tile != NULL && map[i][j].unit_on_tile->owner == owner)
		return (FONT_BLUE);	
	else if (map[i][j].unit_on_tile != NULL && map[i][j].unit_on_tile->owner == enemy && show_enemy(map, i, j, owner, enemy) == 1)
		return (FONT_RED);
	else
		return (FONT_DEFAULT);
}

char				*select_background_color(t_map **map, int i, int j)
{
	if (map[i][j].terrain == '*')
		return (BACKGROUND_LIGHT_GREEN);
	else if (map[i][j].terrain == 'H')
		return (BACKGROUND_YELLOW);
	else if (map[i][j].terrain == 'F')
		return (BACKGROUND_GREEN);
	else if (map[i][j].terrain == 'W')
		return (BACKGROUND_LIGHT_CYAN);
}

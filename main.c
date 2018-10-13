#include "includes/main_header.h"

void				f(t_map **map, t_characters *players, int nb_players, int map_size_x, int map_size_y)
{
	while (players[0].nb_units_owned != 0 || players[1].nb_units_owned != 0)
	{
		while (main_menu(map, players, &players[0], 0, map_size_x, map_size_y) != 1);
		if (nb_players == 2)
			while(main_menu(map, players, &players[1], 1, map_size_x, map_size_y) != 1);
		//else
	}
}

int					main(void)
{
	/* TODO
	une vraie carte
	Plus de paramètres pour les troupes
	Fonction d'attaque plus développée ?
	IA
	*/
	srand(time(NULL));
	int		i;
	int		j;
	int		map_size_x;
	int		map_size_y;
	int		nb_players;
	
	map_size_x = 20;
	map_size_y = 20;
	clear_screen();
	t_characters *players = characters_init();
	t_map	**map = map_init(map_size_x, map_size_y);

	printf("Is there 1 or 2 human players ?\n");
	while (!(nb_players == 1 || nb_players == 2))
		scanf("%d", &nb_players);
	ft_pick_units_players(map, players, 0);
	if (nb_players == 1)
		printf("A FAIRE\n");
	else
		ft_pick_units_players(map, players, 1);
	f(map, players, nb_players, map_size_x, map_size_y);

	for (i = 0; i < 2; i++)
		for (j = 0; j < 10; j++)
			free(players[i].units_owned[j]);
	free(players);
	for (i = 0; i < 20; i++)
		free(map[i]);
	free(map);
	return (0);
}

#include "includes/main_header.h"

/*
	Fonction qui gère les tours des joueurs
*/
void				turns(t_map **map, t_characters *players, int nb_players, int map_size_x, int map_size_y)
{
	while (players[0].nb_units_owned != 0 || players[1].nb_units_owned != 0)
	{
		while (main_menu(map, players, &players[0], 0, nb_players, map_size_x, map_size_y) != 1);
		if (nb_players == 2)
			while(main_menu(map, players, &players[1], 1, nb_players, map_size_x, map_size_y) != 1);
		//else
	}
}

/*
	Simple fonction pour free tout ce qui a été malloc
*/
void				free_stuff(t_map **map, t_characters *players)
{
	int		i;
	int		j;
	
	for (i = 0; i < 2; i++)						// On free d'abord les unités possédées par les joueurs
		for (j = 0; j < 10; j++)
			free(players[i].units_owned[j]);
	free(players);								// Puis les joueurs eux mêmes
	for (i = 0; i < 20; i++)					// Puis la carte
		free(map[i]);
	free(map);
}

/*
	Le main initialise la carte et les joueurs puis lance le jeu et free à la fin
*/
int					main(void)
{
	/* TODO
	Plus de structures pour la carte
	Plus de paramètres pour les troupes ?
	Fonction d'attaque plus développée ?
	IA
	*/
	srand(time(NULL));
	int		map_size_x;
	int		map_size_y;
	char	nb_players[5];
	
	map_size_x = 20;
	map_size_y = 20;
	clear_screen();								
	t_characters *players = characters_init();
	t_map	**map = map_init(map_size_x, map_size_y);

	printf("\nIs there 1 or 2 human players ?\n");
	while (!(atoi(nb_players) == 1 || atoi(nb_players) == 2))
		scanf("%s", nb_players);
	ft_pick_units_players(map, players, 0, map_size_x, map_size_y);
	if (atoi(nb_players) == 1)
		printf("A FAIRE\n");
	else
		ft_pick_units_players(map, players, 1, map_size_x, map_size_y);
	turns(map, players, atoi(nb_players), map_size_x, map_size_y);			// Quand on a fini de paramétrer, on lance le jeu
	free_stuff(map, players);												// On free quand c'est terminé
	return (0);
}

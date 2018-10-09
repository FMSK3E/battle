#include "includes/main_header.h"

void				ft_pick_units_players(t_map **map, t_characters *players, int owner)
{
	int		i;
	int		nb_units;
	char	answer[5];

	clear_screen();
	printf("\n----------Player %d :\nHow many units do you want ? The minimum is 3 and the max is 7 !\n\n", owner + 1);
	while (!(nb_units >= 1 && nb_units <= 7))
	{
		scanf("%s", answer);
		nb_units = atoi(answer);
		if (nb_units >= 1 && nb_units <= 7) // MIS A 1 POUR DES TESTS, A MODIFIER APRES
			players[owner].nb_units_owned = nb_units;	
	}
	printf("Pick the troops you want on the battlefield :\n\tS : Swordsmen : strong against Lancers and weak against Bowmen !\n\tL : Lancers : strong against Cavalry and weak against Swordsmen !\n\tC : Cavalry : strong against Bowmen and weak against Lancers !\n\tB : Bowmen : strong against Swordsmen and weak against Cavalry !\n");
		for (i = 0; i < nb_units; i++)
		{
			printf("\n\nUnit %d :\n", i + 1);
			scanf("%s", answer);
			if (strstr(answer, "S") || strstr(answer, "s"))
				players[owner].units_owned[i] = ft_pick_swordsmen(map, owner);
			else if (strstr(answer, "L") || strstr(answer, "l"))
				players[owner].units_owned[i] = ft_pick_lancers(map, owner);
			else if (strstr(answer, "C") || strstr(answer, "c"))
				players[owner].units_owned[i] = ft_pick_cavalry(map, owner);
			else if (strstr(answer, "B") || strstr(answer, "b"))
				players[owner].units_owned[i] = ft_pick_bowmen(map, owner);
			if (!(strstr(answer, "S") || strstr(answer, "s") || strstr(answer, "L") || strstr(answer, "l") || strstr(answer, "C") || strstr(answer, "c") || strstr(answer, "B") || strstr(answer, "b")))
				i--;
		}
		nb_units = 0;	// Sinon, quand il y a deux joueurs, le jeu prend en suppose qu'il y a le même nombres de soldats et ne redemande pas
		//	TESTS : l'unité est bien assignée à la carte et au personnage, quand on NULL sur la carte ça marche segfault si on cherche à y accéder mais ça ne casse pas le personnage || quand on change quelque chose sur la carte ça ou le joueur ça fait sur l'autre aussi
		/*
		printf("%d\n", players[i].units_owned[j - 1]->pos_y);
		printf("%d\n", map[0][7].unit_on_tile->pos_y);
		map[0][7].unit_on_tile = NULL;
		printf("%d\n", players[i].units_owned[j - 1]->pos_y);
		printf("%d\n", map[0][7].unit_on_tile->pos_y);*/
}

t_units				*ft_pick_swordsmen(t_map **map, int owner)
{
	t_units			*unit;
	char			x[5];
	char			y[5];
	int				pos_ok;

	pos_ok = 0;
	unit = malloc(sizeof(t_units));
	strcpy(unit->type, "swordsmen");
	unit->owner = owner;
	unit->sigle = 'S';
	unit->troops_in_unit = 100;
	unit->max_troops_in_unit = 100;
	unit->attack_range = 1;
	unit->spotting_range = 4;
	unit->strong_against = 'L';
	unit->weak_against = 'B';
	unit->max_actions = 2;
	unit->current_actions = unit->max_actions;
	printf("Choose the location of your unit (x y (ex : 10 10)) ! Player 1 can only go from 0/7y | Player 2, from 12/19y !\n");
	while (!pos_ok)
	{
		scanf("%s %s", x, y);
		if (((owner == 0 && atoi(y) >= 0 && atoi(y) <= 7) || (owner == 1 && atoi(y) >= 12 && atoi(y) <= 19)) && map[atoi(y)][atoi(x)].unit_on_tile == NULL)
		{
			unit->pos_x = atoi(x);
			unit->pos_y = atoi(y);
			map[atoi(y)][atoi(x)].unit_on_tile = unit;
			pos_ok = 1;
		}
		else
			printf("WARNING : Pick a valid position !\n");
	}
	return (unit);
}

t_units				*ft_pick_lancers(t_map **map, int owner)
{

}

t_units				*ft_pick_cavalry(t_map **map, int owner)
{

}

t_units				*ft_pick_bowmen(t_map **map, int owner)
{

}

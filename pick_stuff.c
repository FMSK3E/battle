#include "includes/main_header.h"

void				pick_units_players(t_map **map, t_characters *players, int owner)
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
		i = 0;
		while (i < nb_units)
		{
			printf("\n\nUnit %d :\n", i + 1);
			scanf("%s", answer);
			if (strstr(answer, "S") || strstr(answer, "s"))
				players[owner].units_owned[i] = pick_swordsmen(map, owner);
			else if (strstr(answer, "L") || strstr(answer, "l"))
				players[owner].units_owned[i] = pick_lancers(map, owner);
			else if (strstr(answer, "C") || strstr(answer, "c"))
				players[owner].units_owned[i] = pick_cavalry(map, owner);
			else if (strstr(answer, "B") || strstr(answer, "b"))
				players[owner].units_owned[i] = pick_bowmen(map, owner);
			if (strstr(answer, "S") || strstr(answer, "s") || strstr(answer, "L") || strstr(answer, "l") || strstr(answer, "C") || strstr(answer, "c") || strstr(answer, "B") || strstr(answer, "b"))
				i++;
		}
		nb_units = 0;	// Sinon, quand il y a deux joueurs, le jeu prend en suppose qu'il y a le même nombres de soldats et ne redemande pas
		//	TESTS : l'unité est bien assignée à la carte et au personnage, quand on NULL sur la carte ça marche segfault si on cherche à y accéder mais ça ne casse pas le personnage.
		/*
		printf("%d\n", players[i].units_owned[j - 1]->pos_y);
		printf("%d\n", map[0][7].unit_on_tile->pos_y);
		map[0][7].unit_on_tile = NULL;
		printf("%d\n", players[i].units_owned[j - 1]->pos_y);
		printf("%d\n", map[0][7].unit_on_tile->pos_y);*/
}

t_units				*pick_swordsmen(t_map **map, int owner)
{
	t_units			*unit;
	int				x;
	int				y;
	char			xc[5];
	char			yc[5];
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
	unit->used = 0;
	printf("Choose the location of your unit (x y (ex : 10 10)) ! Player 1 can only go from 0 to 9 / Player 2, from 10 to 19 !\n");
	while (!pos_ok)
	{
		scanf("%s %s", xc, yc);
		x = atoi(xc);
		y = atoi(yc);
		if (((owner == 0 && x >= 0 && x <= 9 && y >= 0 && y <= 9) || (owner == 1 && x >= 10 && x <= 19 && y >= 10 && y <= 19)) && map[y][x].unit_on_tile == NULL)
		{
			unit->pos_x = x;
			unit->pos_y = y;
			map[y][x].unit_on_tile = unit;
			pos_ok = 1;
		}
		else
			printf("WARNING : Pick a valid position !\n");
	}
	return (unit);
}

t_units				*pick_lancers(t_map **map, int owner)
{

}

t_units				*pick_cavalry(t_map **map, int owner)
{

}

t_units				*pick_bowmen(t_map **map, int owner)
{

}

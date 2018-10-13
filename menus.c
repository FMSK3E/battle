#include "includes/main_header.h"

/*
	Menu de gestion de l'unité, depuis là on peut attaquer ou bouger
	int		*available_troops	= On baisse de 1 si l'unité n'a plus de points après son action
	int		id					= Juste pour afficher le numéro de l'unité
	int		map_size_x/y		= Pour afficher la carte
	
*/
void				unit_menu(t_map **map, t_characters *players, t_characters *player, t_units *unit, int owner, int *available_troops, int id, int map_size_x, int map_size_y)
{
	char	answer[5];

	if (unit->current_actions <= 0)
		return;
	while (unit->current_actions > 0)
	{
		clear_screen();
		ft_print_map(map, unit, map_size_x, map_size_y, owner);
		printf("\n--------------------Unit %d - %s - %d/%d troops in unit - %dx / %dy\n", id, unit->type, unit->troops_in_unit, unit->max_troops_in_unit, unit->pos_x, unit->pos_y);
		printf("Control the unit :\n\tZ : north\n\tQ : west\n\tS : south\n\tD : east\n\tA : attack\n\tR : Go back to the units manager menu\n\n%d action points left !\n\n", unit->current_actions);
		scanf("%s", answer);
		if (strstr(answer, "A") || strstr(answer, "a"))	
			unit->current_actions -= ft_find_unit_to_attack(map, players, unit);
		else if (strstr(answer, "Q") || strstr(answer, "q"))
			unit->current_actions -= ft_move_unit(map, players, unit, -1, 0);
		else if (strstr(answer, "S") || strstr(answer, "s"))
			unit->current_actions -= ft_move_unit(map, players, unit, 0, 1);
		else if (strstr(answer, "D") || strstr(answer, "d"))
			unit->current_actions -= ft_move_unit(map, players, unit, 1, 0);
		else if (strstr(answer, "Z") || strstr(answer, "z"))
			unit->current_actions -= ft_move_unit(map, players, unit, 0, -1);	
		else if (strstr(answer, "R") || strstr(answer, "r"))
			return;
	}
	if (unit->current_actions <= 0)
		(*available_troops)--;
}

/*
	Menu de gestion de l'unité, depuis là on peut attaquer ou bouger
	int		owner				= Pour les fonctions d'attaque
	int		*available_troops	= Pour la fonction plus haute, on return directement si c'est 0
	int		map_size_x/y		= Pour afficher la carte
	
*/
void				units_manager_menu(t_map **map, t_characters *players, t_characters *player, int owner, int *available_troops, int map_size_x, int map_size_y)
{
	int		i;
	char	answer[5];

	while (1)
	{
		if (!(*available_troops))
			return;
		if (player->nb_units_owned == 1)	
		{
			unit_menu(map, players, player, player->units_owned[0], owner, available_troops, 1, map_size_x, map_size_y);
			return;
		}
		clear_screen();
		ft_print_map(map, NULL, map_size_x, map_size_y, owner);
		printf("\n-------------------------Troops menu, select an action : %d unit(s) waiting your order\n\t1-9 to select one of your units\n\t0 to go back to the main menu\n\n\nAvailable troops :\n", *available_troops);
		for (i = 0; i < player->nb_units_owned; i++)
			if (player->units_owned[i]->current_actions > 0)
				printf("---> Unit %d - %s - %d/%d troops in unit - %dx / %dy\n", i + 1, player->units_owned[i]->type, player->units_owned[i]->troops_in_unit, player->units_owned[i]->max_troops_in_unit, player->units_owned[i]->pos_x, player->units_owned[i]->pos_y);
		scanf("%s", answer);
		if (atoi(answer) >= 1 && atoi(answer) <= 9 && player->units_owned[atoi(answer) - 1] != NULL)
			unit_menu(map, players, player, player->units_owned[atoi(answer) - 1], owner, available_troops, atoi(answer), map_size_x, map_size_y);
		else if (atoi(answer) == 0)
			return;
	}
}

/*
	Menu de gestion de l'unité, depuis là on peut attaquer ou bouger
	int		owner				= Pour les fonctions d'attaque
	int		map_size_x/y		= Pour afficher la carte
	
*/
int					main_menu(t_map **map, t_characters *players, t_characters *player, int owner, int nb_players, int map_size_x, int map_size_y)
{
	int		i;
	int		available_troops;
	char	answer[5];

	available_troops = player->nb_units_owned;
	while(1)
	{
		clear_screen();
		if (nb_players == 1 && !available_troops)
		{
			for (i = 0; i < player->nb_units_owned; i++)
				player->units_owned[i]->current_actions = player->units_owned[i]->max_actions;
			return (1);
		}
		ft_print_map(map, NULL, map_size_x, map_size_y, owner);
		printf("\n----------------------------------------Main menu, current player : Player %d", player->id + 1);
		if (!available_troops)
			printf(" --- NO AVAILABLE TROOPS !");
		printf("\n\t1 : manage your units\n\t2 : end the turn\n\n");
		scanf("%s", answer);
		if (strstr(answer, "1"))
		{
			if (available_troops)
				units_manager_menu(map, players, player, owner, &available_troops, map_size_x, map_size_y);
		}
		else if (strstr(answer, "2"))
		{
			for (i = 0; i < player->nb_units_owned; i++)
				player->units_owned[i]->current_actions = player->units_owned[i]->max_actions;
			return (1);
		}
	}
}

#include "includes/main_header.h"

void				unit_menu(t_map **map, t_characters *players, t_units *unit, int owner, int *available_troops, int id)
{
	int		answer_ok;
	char	answer[5];

	if (unit->used == 1)
		return;
	while (answer_ok != 1)
	{
		clear_screen();
		printf("\n--------------------Unit %d - %s - %d/%d troops in unit - %dx / %dy\n", id, unit->type, unit->troops_in_unit, unit->max_troops_in_unit, unit->pos_x, unit->pos_y);
		printf("Control the unit :\n\tZ : north\n\tQ : west\n\tS : south\n\tD : east\n\tA : attack\n");
		scanf("%s", answer);
		if (strstr(answer, "A") || strstr(answer, "a"))	
			answer_ok = ft_find_unit_to_attack(map, players, unit, owner);
		else if (strstr(answer, "Q") || strstr(answer, "q"))
			answer_ok = ft_move_unit(map, players, unit, -1, 0);
		else if (strstr(answer, "S") || strstr(answer, "s"))
			answer_ok = ft_move_unit(map, players, unit, 0, 1);
		else if (strstr(answer, "D") || strstr(answer, "d"))
			answer_ok = ft_move_unit(map, players, unit, 1, 0);
		else if (strstr(answer, "Z") || strstr(answer, "z"))
			answer_ok = ft_move_unit(map, players, unit, 0, -1);
	}
	players[owner].units_owned[id]->used = 1;
	(*available_troops)--;
}

void				units_manager_menu(t_map **map, t_characters *players, int owner, int *available_troops)
{
	int		i;
	char	answer[5];

	while (1)
	{
		if (!(*available_troops))
			return;
		clear_screen();
		printf("\n-------------------------Troops menu, select an action : %d unit(s) waiting your order\n\t1-9 to select one of your units\n\t10 to go back to the main menu\n\n\nAvailable troops :\n", *available_troops);
		for (i = 0; i < players[owner].nb_units_owned; i++)
			if (!players[owner].units_owned[i]->used)
				printf("---> Unit %d - %s - %d/%d troops in unit - %dx / %dy\n", i + 1, players[owner].units_owned[i]->type, players[owner].units_owned[i]->troops_in_unit, players[owner].units_owned[i]->max_troops_in_unit, players[owner].units_owned[i]->pos_x, players[owner].units_owned[i]->pos_y);
		scanf("%s", answer);
		if (atoi(answer) >= 1 && atoi(answer) <= 9 && players[owner].units_owned[atoi(answer) - 1] != NULL)
			unit_menu(map, players, players[owner].units_owned[atoi(answer) - 1], owner, available_troops, atoi(answer) - 1);
		else if (atoi(answer) == 10)
			return;
	}
}

int					main_menu(t_map **map, t_characters *players, int owner, int map_size_x, int map_size_y, int nb_players)
{
	int		i;
	int		available_troops;
	char	answer[5];

	available_troops = players[owner].nb_units_owned;
	while(1)
	{
		clear_screen();
		printf("\n----------------------------------------Main menu, current player : Player %d", owner + 1);
		if (!available_troops)
			printf(" --- NO AVAILABLE TROOPS !");
		printf("\n\t1 : manage your units\n\t2 : end the turn\n");
		ft_print_map(map, map_size_x, map_size_y, nb_players, owner);
		scanf("%s", answer);
		if (strstr(answer, "1"))
		{
			if (available_troops)
				units_manager_menu(map, players, owner, &available_troops);
		}
		else if (strstr(answer, "2"))
		{
			for (i = 0; i < players[owner].nb_units_owned; i++)
				players[owner].units_owned[i]->used = 0;
			return (1);
		}
	}
}

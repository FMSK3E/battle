void				player_action_unit(t_map **map, t_characters *players, int owner, int id, int *available_troops)
{
	int		answer_ok;
	char	answer[5];

	if (players[owner].units_owned[id]->used == 1)
		return;
	clear_screen();
	printf("\n--------------------Unit %d - %s - %d/%d troops in unit - %dx / %dy\n", id, players[owner].units_owned[id]->type, players[owner].units_owned[id]->troops_in_unit, players[owner].units_owned[id]->max_troops_in_unit, players[owner].units_owned[id]->pos_x, players[owner].units_owned[id]->pos_y);
	printf("Control the unit :\n\tZ : north\n\tQ : west\n\tS : south\n\tD : east\n\tA : attack\n");
	while (answer_ok != 1)
	{
		scanf("%s", answer);
		if (strstr(answer, "1"))	
			printf("!!!!!!!!!!!!!!!!!! !\n");
		else if (strstr(answer, "Q") || strstr(answer, "q"))
			answer_ok = move_unit(map, players, owner, id, 0, -1);
		else if (strstr(answer, "S") || strstr(answer, "s"))
			answer_ok = move_unit(map, players, owner, id, 1, 0);
		else if (strstr(answer, "D") || strstr(answer, "d"))
			answer_ok = move_unit(map, players, owner, id, 0, 1);
		else if (strstr(answer, "Z") || strstr(answer, "z"))
			answer_ok = move_unit(map, players, owner, id, -1, 0);
		else
			printf("WARNING : Pick a valid answer !\n");
	}
	players[owner].units_owned[id]->used = 1;
	(*available_troops)--;
}

void				troops_menu(t_map **map, t_characters *players, int owner, int enemy, int *available_troops)
{
	int		i;
	int		answer;
	char	answer_char[5];

	while (1)
	{
		clear_screen();
		printf("\n-------------------------Troops menu, select an action : %d unit(s) waiting your order\n\t0-9 to select one of your units\n\t10 to show the list of available units\n\t11 to go back to the main menu\n\n\nAvailable troops :\n", *available_troops);
		for (i = 0; i < players[owner].nb_units_owned; i++)
			if (!players[owner].units_owned[i]->used)
				printf("---> Unit %d - %s - %d/%d troops in unit - %dx / %dy\n", i, players[owner].units_owned[i]->type, players[owner].units_owned[i]->troops_in_unit, players[owner].units_owned[i]->max_troops_in_unit, players[owner].units_owned[i]->pos_x, players[owner].units_owned[i]->pos_y);
		scanf("%s", answer_char);
		answer = atoi(answer_char);
		if (answer >= 0 && answer <= 9 && players[owner].units_owned[answer] != NULL)
			player_action_unit(map, players, owner, answer, available_troops);
		else if (answer == 10)
		{
			printf("Available troops :\n");
			for (i = 0; i < players[owner].nb_units_owned; i++)
				if (!players[owner].units_owned[i]->used)
					printf("---> Unit %d - %s - %d/%d troops in units - %dx / %dy\n", i, players[owner].units_owned[i]->type, players[owner].units_owned[i]->troops_in_unit, players[owner].units_owned[i]->max_troops_in_unit, players[owner].units_owned[i]->pos_x, players[owner].units_owned[i]->pos_y);
		}
		else if (answer == 11)
			return;
	}
}

int					main_menu(t_map **map, t_characters *players, int owner, int enemy, int map_size_x, int map_size_y, int *do_print, int nb_players)
{
	int		i;
	int		available_troops;
	char	answer[5];

	available_troops = players[owner].nb_units_owned;
	while(1)
	{
		clear_screen();
		if (*do_print)
		{
			*do_print = 0;
			print_map(map, map_size_x, map_size_y, nb_players, owner, enemy);
		}
		printf("\n----------------------------------------Main menu, current player : Player %d :\n\t1 : use your troops", owner + 1);
		if (!available_troops)
			printf(" --- NO AVAILABLE TROOPS !");
		printf("\n\t2 : show the map\n\t3 : end the turn\n");
		print_map(map, map_size_x, map_size_y, nb_players, owner, enemy);
		scanf("%s", answer);
		if (strstr(answer, "1"))
		{
			if (available_troops)
				troops_menu(map, players, owner, enemy, &available_troops);
		}
		else if (strstr(answer, "2"))
		{
			*do_print = 1;
			return 0;
		}
		else if (strstr(answer, "3"))
		{
			for (i = 0; i < players[owner].nb_units_owned; i++)
				players[owner].units_owned[i]->used = 0;
			return 1;
		}
	}
}

void				f(t_map **map, t_characters *players, int nb_players, int map_size_x, int map_size_y)
{
	int		do_print;

	do_print = 0;
	while (main_menu(map, players, 0, 1, map_size_x, map_size_y, &do_print, nb_players) != 1);
	if (nb_players == 2)
		while(main_menu(map, players, 1, 0, map_size_x, map_size_y, &do_print, nb_players) != 1);
	//else
}

int					main(void)
{
	/* TODO
	Fonction de combat
	IA
	*/
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
	pick_units_players(map, players, 0);
	if (nb_players == 1)
		printf("A FAIRE\n");
	else
		pick_units_players(map, players, 1);
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

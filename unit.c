#include "includes/main_header.h"

/*
	Fonction qui permet de bouger l'unité
	Retourne 0 si impossible
	Le return correspond à la perte de points d'actions
*/
int					ft_move_unit(t_map **map, t_characters *players, t_units *unit, int new_x, int new_y)
{
	int		cost;

	cost = 0;
	if ((unit->pos_x + new_x < 0 || unit->pos_x + new_x > 19 || unit->pos_y + new_y < 0 || unit->pos_y + new_y > 19) || map[unit->pos_y + new_y][unit->pos_x + new_x].unit_on_tile != NULL)	// On retourne 0 s'il y a un pb
		return (cost);
	cost = 1;
	if (map[unit->pos_y][unit->pos_x].height_level <= map[unit->pos_y + new_y][unit->pos_x + new_x].height_level || map[unit->pos_y + new_y][unit->pos_x + new_x].terrain == 'W')
		cost++;
	map[unit->pos_y][unit->pos_x].unit_on_tile = NULL;
	unit->pos_x += new_x;
	unit->pos_y += new_y;
	map[unit->pos_y][unit->pos_x].unit_on_tile = unit;

	return (cost);
}

/*
	Liste dans un t_characters temp la liste des unités trouvées dans un rayon de 12x12 et ayant une distance inférieure à la portée de l'attaquant
	Retourne la fonction d'attaque qui se lance si au moins une cible est trouvé et que le joueur décide d'attaquer
	Le return correspond à la perte de points d'actions
	La fonction d'attaque retourne 3
*/
int					ft_find_unit_to_attack(t_map **map, t_characters *players, t_units *unit)
{
	int				i;
	int				j;
	int				k;		// Nombre de cibles trouvées
	char			target[5];
	t_characters	temp;

	clear_screen();
	k = 0;
	for (i = unit->pos_y - 6; i < unit->pos_y + 6; i++)			// On ratisse sur une zone de 12x12
	{
		for (j = unit->pos_x - 6; j < unit->pos_x + 6; j++)
		{
			if ((i >= 0 && i <= 19 && j >= 0 && j <= 19) && map[i][j].unit_on_tile != NULL && map[i][j].unit_on_tile->owner != unit->owner && ft_calculate_attack_range(map[unit->pos_y][unit->pos_x], map[i][j], unit) == 1) // Si on trouve une unité à distance d'attaque on l'affiche et on la liste
			{
					temp.units_owned[k] = map[i][j].unit_on_tile;
					printf("---> Target %d - %s - %d/%d troops in unit - %dx / %dy\n", k + 1, temp.units_owned[k]->type, temp.units_owned[k]->troops_in_unit, temp.units_owned[k]->max_troops_in_unit, temp.units_owned[k]->pos_x, temp.units_owned[k]->pos_y);
					k++;
			}
		}
	}
	if (!k)			// Si aucune unité listée
		return (0);
	printf("\nPick a target or go back to the unit menu with R\n");
	while (1)
	{
		scanf("%s", target);
		if(strstr(target, "R") || strstr(target, "r"))
			return (0);
		else if (atoi(target) <= k && atoi(target) != 0)		// On empêche le 0 pour éviter les erreurs au cas où on appuierais sur e-d-f-t à la place de R, ce qui causerait l'attaque sur l'unité 0
			return (ft_attack_unit(map, players, unit, temp.units_owned[atoi(target) - 1], 0));		// Au lieu d'une fonction void, on fait une fonction int qui retourne toujours 1, ça permet de  gagner 3 lignes
	}
}

/*
	Calcul de la distance entre l'attaquant et la cible potentielle
	Retourne 1 si une attaque est possible, 0 sinon
*/
int					ft_calculate_attack_range(t_map unit_tile, t_map target_tile, t_units *unit)
{
	int		attack_range;
	int		y_distance;
	int		x_distance;

	attack_range = unit->attack_range;

	if (unit_tile.height_level > target_tile.height_level && unit->sigle == 'B')		// On regarde si la portée de l'unité est affectée par le terrain
		attack_range++;
	if (unit_tile.height_level < target_tile.height_level && unit->sigle == 'B')
		attack_range--;
	for (y_distance = unit_tile.y - target_tile.y; y_distance < 0; y_distance = -y_distance);
	for (x_distance = unit_tile.x - target_tile.x; x_distance < 0; x_distance = -x_distance);

	if (x_distance <= attack_range && y_distance <= attack_range)
		return (1);
	return (0);
}

/*
	Calcul des dommages et contre attaque de l'unité ennemie
	int retaliation utilisé de façon récursive pour ne pas contre attaquer jusqu'à ce que mort s'ensuive
	Retourne la perte de points d'actions du à l'attaque
*/
int					ft_attack_unit(t_map **map, t_characters *players, t_units *attacker, t_units *defender, int retaliation)
{
	int		damage;

	damage = attacker->troops_in_unit / 5;
	if (defender->weak_against == attacker->sigle)				// Forces - Faiblesses
		damage *= 1.2;
	else if (defender->strong_against == attacker->sigle)
		damage *= 0.8;

	if (retaliation && attacker->sigle == 'B' && defender->sigle != 'B')		// Si des archers se défendent au càc
		damage *= 0.3;
	if (!retaliation && attacker->sigle == 'C' && defender->sigle != 'L')		// Charge de cavalerie hors lanciers
		damage *= 1.8;
	if (attacker->sigle == 'C' && defender->sigle == 'B')						// Charge de cavalerie contre archer
		damage *= 2;
	if (!retaliation && attacker->sigle != 'B' && defender->sigle == 'C')		// Si attaque d'infanterie contre cavalerie en défense
		damage *= 1.3;
	if (!retaliation && map[attacker->pos_y][attacker->pos_x].height_level > map[defender->pos_y][defender->pos_x].height_level && attacker->sigle != 'B')		// Bonus ou malus de terrain
		damage *= 1.2;
	else if (!retaliation && map[attacker->pos_y][attacker->pos_x].height_level < map[defender->pos_y][defender->pos_x].height_level && attacker->sigle != 'B')
		damage *= 0.8;
	defender->troops_in_unit -= damage;					// Application des dommages
	if (!ft_unit_destroyed(map, &players[defender->owner]) && !retaliation && ft_calculate_attack_range(map[defender->pos_y][defender->pos_x], map[attacker->pos_y][defender->pos_x], defender) == 1)		// Le défenseur attaque à son tour
		ft_attack_unit(map, players, defender, attacker, 1);
	return (3);
}

/*
	On utilise cette fonction après chaque attaque pour voir une des unités ayant participé au combat est détruite
	La fonction retourne 1 si l'unité est détruite (ça bloque la contre attaque, forcément) et 0 si ce n'est pas le cas
*/
int					ft_unit_destroyed(t_map **map, t_characters *owner)
{
	int		i;
	int		j;

	for (i = 0; i < owner->nb_units_owned; i++)
	{
		if (owner->units_owned[i]->troops_in_unit <= 0)
		{
			map[owner->units_owned[i]->pos_y][owner->units_owned[i]->pos_x].unit_on_tile = NULL;
			free(owner->units_owned[i]);
			owner->nb_units_owned--;
			for (j = i; j < owner->nb_units_owned; j++)
				owner->units_owned[j] = owner->units_owned[j + 1];
			return (1);
		}
	}
	return (0);
}

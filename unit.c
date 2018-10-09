#include "includes/main_header.h"

int					ft_move_unit(t_map **map, t_characters *players, t_units *unit, int new_x, int new_y)
{
	if (unit->pos_x + new_x < 0 || unit->pos_x + new_x > 19 || unit->pos_y + new_y < 0 || unit->pos_y + new_y > 19)		// On fait d'abord ce if pour s'assurer de ne pas tomber hors de la carte
	{
		printf("WARNING : You cannot move in this direction, you've reached map's borders !\n");
		return (0);
	}
	else if (map[unit->pos_y + new_y][unit->pos_x + new_x].unit_on_tile != NULL)	// Si il y a déjà une unitée sur la case voulue
	{
		printf("WARNING : An unit is already on the tile !\n");
		return (0);
	}
	else				// Tout est bon, on change les positions de l'unité
	{
		map[unit->pos_y][unit->pos_x].unit_on_tile = NULL;
		unit->pos_x += new_x;
		unit->pos_y += new_y;
		map[unit->pos_y][unit->pos_x].unit_on_tile = unit;
	}
	return (1);
}

int					ft_find_unit_to_attack(t_map **map, t_characters *players, t_units *unit, int owner)
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
			if (i >= 0 && i <= 19 && j >= 0 && j <= 19)			// On s'assure de ne pas tomber hors de la carte
			{
				if (map[i][j].unit_on_tile != NULL && map[i][j].unit_on_tile->owner != owner && ft_calculate_attack_range(map, unit, map[i][j].unit_on_tile) <= unit->attack_range) // Si on trouve une unité à distance d'attaque on l'affiche et on la liste
				{
						temp.units_owned[k] = map[i][j].unit_on_tile;
						printf("---> Target %d - %s - %d/%d troops in unit - %dx / %dy\n", k + 1, temp.units_owned[k]->type, temp.units_owned[k]->troops_in_unit, temp.units_owned[k]->max_troops_in_unit, temp.units_owned[k]->pos_x, temp.units_owned[k]->pos_y);
						k++;
				}
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

int					ft_calculate_attack_range(t_map **map, t_units *unit, t_units *target)
{
	int		range;

	range = 1;
	return (range);
}

int					ft_attack_unit(t_map **map, t_characters *players, t_units *attacker, t_units *defender, int retaliation)
{
	int		damage;
	int		unit_destroyed;			// Si une unité est détruite, pour éviter de lancer la fonction de contre attaque

	unit_destroyed = 0;
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
	t_characters ptr = players[1];
	defender->troops_in_unit -= damage;					// Application des dommages
	if (attacker->troops_in_unit <= 0)					// Si les unités sont détruites
	{
		ft_unit_destroyed(map, &players[attacker->owner]);
		unit_destroyed = 1;
	}
	if (defender->troops_in_unit <= 0)
	{
		ft_unit_destroyed(map, &players[defender->owner]);
		unit_destroyed = 1;
	}
	if (!retaliation && !unit_destroyed && ft_calculate_attack_range(map, defender, attacker) <= defender->attack_range)		// Le défenseur attaque à son tour
		ft_attack_unit(map, players, defender, attacker, 1);
	return (3);
}

void				ft_unit_destroyed(t_map **map, t_characters *owner)
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
		}
	}
}	

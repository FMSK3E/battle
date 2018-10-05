#ifndef		MAIN_HEADER_H
#define 	MAIN_HEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define clear_screen()				printf("\033[H\033[J")

#define FONT_DEFAULT				"\x1b[0m"
#define FONT_BLACK					"\x1b[30m"
#define FONT_RED					"\x1b[31m"
#define FONT_GREEN					"\x1b[32m"
#define FONT_YELLOW					"\x1b[33m"
#define FONT_BLUE					"\x1b[34m"
#define FONT_MAGENTA				"\x1b[35m"
#define FONT_CYAN					"\x1b[36m"
#define FONT_LIGHT_GRAY				"\x1b[37m"
#define FONT_DARK_GRAY				"\x1b[90m"
#define FONT_LIGHT_RED				"\x1b[91m"
#define FONT_LIGHT_GREEN			"\x1b[42m"
#define FONT_LIGHT_YELLOW			"\x1b[93m"
#define FONT_LIGHT_BLUE				"\x1b[94m"
#define FONT_LIGHT_MAGENTA			"\x1b[95m"
#define FONT_LIGHT_CYAN				"\x1b[96m"

#define BACKGROUND_DEFAULT			"\e[49m"
#define BACKGROUND_RED				"\e[41m"
#define BACKGROUND_GREEN			"\e[42m"
#define BACKGROUND_YELLOW			"\e[43m"
#define BACKGROUND_BLUE				"\e[44m"
#define BACKGROUND_MAGENTA			"\e[45m"
#define BACKGROUND_CYAN				"\e[46m"
#define BACKGROUND_LIGHT_GRAY		"\e[47m"
#define BACKGROUND_DARK_GRAY		"\e[100m"
#define BACKGROUND_LIGHT_RED_		"\e[101m"
#define BACKGROUND_LIGHT_GREEN		"\e[102m"
#define BACKGROUND_LIGHT_YELLOW		"\e[103m"
#define BACKGROUND_LIGHT_BLUE		"\e[104m"
#define BACKGROUND_LIGHT_MAGENTA	"\e[105m"
#define BACKGROUND_LIGHT_CYAN		"\e[106m"

typedef struct	s_units
{
	char		type[10];
	int			owner;
	char		sigle;

	int			troops_in_unit;
	int			max_troops_in_unit;
	int			attack_range;
	int			spotting_range;
	char		strong_against;
	char		weak_against;

	int			pos_x;
	int			pos_y;

	int			used;
}				t_units;

typedef struct	s_characters
{
	int			id;
	int			nb_units_owned;
	t_units		*units_owned[10];
}				t_characters;

typedef struct	s_map
{
	t_units		*unit_on_tile;
	int			spotting_range_bonus;
	char		terrain;
}				t_map;

//					stuctures_init.c
t_characters		*characters_init(void);
t_map				**map_init(int map_size_x, int map_size_y);

//					print_stuff.c
void				ft_print_map(t_map **map, int map_size_x, int map_size_y, int nb_players, int owner, int enemy);
int					ft_show_enemy(t_map **map, t_units *unit, int owner, int enemy);
char				*ft_select_font_color(t_map **map, int i, int j, int owner, int enemy);
char				*ft_select_background_color(t_map **map, char terrain);

//					pick_stuff.c
void				ft_pick_units_players(t_map **map, t_characters *players, int owner);
t_units				*ft_pick_swordsmen(t_map **map, int owner);
t_units				*ft_pick_lancers(t_map **map, int owner);
t_units				*ft_pick_cavalry(t_map **map, int owner);
t_units				*ft_pick_bowmen(t_map **map, int owner);

//					menus.c
int					main_menu(t_map **map, t_characters *players, int owner, int enemy, int map_size_x, int map_size_y, int nb_players);
void				units_manager_menu(t_map **map, t_characters *players, int owner, int enemy, int *available_units);
void				unit_menu(t_map **map, t_characters *players, t_units *unit, int owner, int *available_units, int id);

//					unit.c
int					ft_move_unit(t_map **map, t_characters *players, t_units *unit, int new_x, int new_y);
int					ft_find_unit_to_attack(t_map **map, t_characters *players, t_units *unit, int owner);
int					ft_calculate_attack_range(t_map **map, t_units *unit, t_units *target);
int					ft_attack_unit(t_map **map, t_units *attacker, t_units *defender);

#endif

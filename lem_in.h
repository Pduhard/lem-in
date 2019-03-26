/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_in.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/01 03:09:06 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/09 22:51:28 by sbedene     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# define START -1
# define NONE -2
# define END 0
# define NO_ANT -1

typedef struct		s_ant
{
	struct s_ant	*next;
	struct s_ant	**chd;
	struct s_ant	**prt;
	char			*name;
	struct s_ant	*only_way;
	int				ant;
	int				hot;
	int				x;
	int				y;
	long long		way;
}					t_ant;

typedef struct		s_room
{
	char			*name;
	struct s_room	*next;
	int				ant;
}					t_room;

typedef struct		s_way
{
	struct s_room	*rooms;
	int				len;
	struct s_way	*next;
}					t_way;

typedef struct		s_data
{
	struct s_ant	*start;
	struct s_ant	*end;
	struct s_ant	*ant_hill;
	int				way_nbr;
	struct s_way	*ways;
	long			nb_ant;
}					t_data;

t_ant				*pr_parsing(long *nb_ant, t_data *data, char **file);
int					ft_clean_exit(int error, t_data *data, char *file);
t_ant				*free_ant_hill(t_ant *list);
int					get_name_len(char *str);
int					get_coord(t_ant *new_rm, char *line, t_ant *ipt);
int					is_valid_room(char *line, int check);
int					is_valid_tube(char *line);
int					return_valid(char **line, int to_ret);
t_ant				*ft_antnew(char *line, int hot, t_data *data, t_ant *ipt);
int					pr_create_child(t_ant *ipt, t_ant ***child);
int					add_link(char *name1, char *name2, t_ant *ipt);
int					ft_find_ways(t_data *data);
void				set_heat(t_ant *room, int heat, int way);
int					get_child_nbr(t_ant **chd);
int					pr_backtrack_heat(t_ant *begin, int tier, int way,
						int target);
t_ant				*free_ant_hill(t_ant *list);
t_way				*free_ways(t_way *way);
void				delete_rm(t_room *rm, t_room *tmp2);
int					delete_way(t_way **begin, t_way **to_del);
void				pr_trim(t_data *data);
int					get_nb_turn(t_data *data);
t_data				*ft_sort_child(t_data *data);
int					load_way(t_room *room, int *ant, int nb_ant, int space);
int					ant_send(t_data *data, int nb_turn);
t_room				*create_room(char *name);
void				ft_init_value(int *index, int *i, int *test, int *min);
int					get_tmp(t_ant *begin, int *check, int i, int tmp);
int					is_last_way(t_room *tmp);
char				*ft_rmsps(char *line);
void				chuuuuut(t_ant **ipt, t_ant **curr);
int					chuuuuut2(char **line, char **file, int ret);

int					tr_can_take(t_ant *noeud, t_ant *end, int ant_in);
int					tr_move_ant(t_ant *noeud, t_ant *after, int ant_in);
int					tr_heat_tracking(t_ant *noeud, int target_hot, int ant_in);
int					tr_solver(t_ant *head, int nbr_fourmi, int hot_max);
int					pr_backtrack_end(t_ant *begin, t_ant *start);
t_way				*ft_probe(t_ant *begin);
int					is_child_of(t_ant *child, t_ant *parent);

#endif

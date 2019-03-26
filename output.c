/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   output.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/08 02:51:34 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/08 04:16:53 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int			get_nb_turn(t_data *data)
{
	int		sum;
	int		i;
	int		nb_turn;
	t_way	*tmp;

	nb_turn = 0;
	sum = 0;
	i = -1;
	while (data->nb_ant >= sum)
	{
		tmp = data->ways;
		sum = 0;
		i = -1;
		while (tmp)
		{
			sum += nb_turn - (tmp->len - 1);
			tmp = tmp->next;
		}
		nb_turn++;
	}
	return (nb_turn - 1);
}

t_data		*ft_sort_child(t_data *data)
{
	t_ant	*tmp;
	int		i;

	i = 0;
	while (data->start->chd && data->start->chd[++i])
	{
		if (data->start->chd[i - 1]->hot > data->start->chd[i]->hot)
		{
			tmp = data->start->chd[i - 1];
			data->start->chd[i - 1] = data->start->chd[i];
			data->start->chd[i] = tmp;
			i--;
		}
	}
	return (data);
}

int			load_way(t_room *room, int *ant, int nb_ant, int space)
{
	t_room	*tmp;
	int		check;

	tmp = room;
	check = 0;
	while (tmp->next)
	{
		if (tmp->next->ant && (check = 1) == 1)
		{
			ft_putchar('L');
			ft_putnbr(tmp->next->ant);
			ft_putchar('-');
			ft_putstr(tmp->name);
			tmp->ant = tmp->next->ant;
			tmp->next->ant = 0;
			if (!(space == 0 && is_last_way(tmp->next)))
				ft_putchar(' ');
		}
		tmp = tmp->next;
	}
	if (*ant <= nb_ant && (tmp->ant = *ant) == *ant)
		*ant = *ant + 1;
	return (check);
}

void		print_travel(t_way *sender, int *ant, int nb_ant, t_data *data)
{
	int		j;

	j = 1;
	while (j == 1)
	{
		j = 0;
		sender = data->ways;
		while (sender)
		{
			j = load_way(sender->rooms, ant, nb_ant, sender->next ? 1 : 0) | j;
			sender = sender->next;
		}
		if (j)
			write(1, "\n", 1);
	}
}

int			ant_send(t_data *data, int nb_turn)
{
	int		ant;
	int		j;
	int		check;
	int		nb_ant;
	t_way	*sender;

	j = 0;
	nb_ant = data->nb_ant;
	ant = 1;
	check = 1;
	while (check)
	{
		sender = data->ways;
		check = 0;
		while (nb_ant && sender && nb_turn > sender->len - 1)
		{
			check = load_way(sender->rooms, &ant,
					nb_ant, sender->next ? 1 : 0) | check;
			sender = sender->next;
		}
		j++;
	}
	print_travel(sender, &ant, nb_ant, data);
	return (0);
}

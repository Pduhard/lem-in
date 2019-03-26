/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_probe.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 21:15:32 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/09 21:47:18 by sbedene     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int		goto_end(t_ant *begin, int count, long long way)
{
	int		i;
	int		min;
	int		test;
	int		index;

	ft_init_value(&index, &i, &test, &min);
	count++;
	if (begin->hot == START)
		return (count);
	if (get_child_nbr(begin->chd) == 1 && (begin->chd[0]->way & (1 << way)))
		return (goto_end(begin->chd[0], count, way));
	else
	{
		while (begin->chd[++i])
			if ((begin->chd[i]->way & (1 << way)))
			{
				test = goto_end(begin->chd[i], count, way);
				if ((test < min || min == -1) && (index = i) == i)
					min = test;
			}
		if (min != -1 && min != 1000)
			return (goto_end(begin->chd[index], count, way));
	}
	return (1000);
}

t_room	*select_shortest_way(t_ant **child, t_ant **begin, long long way)
{
	int		i;
	int		tst;
	int		index;
	int		end;

	end = -1;
	i = 0;
	while (child[i])
	{
		if (((tst = goto_end(child[i], 0, way)) < end
		|| end == -1) && (index = i) == i)
			end = tst;
		i++;
	}
	if (end != -1)
		*begin = child[index];
	return (end != -1 ? create_room(child[index]->name) : NULL);
}

int		ft_checker(t_ant **begin, int way, t_room **room, int check)
{
	int		index;
	int		i;

	i = -1;
	while ((*begin)->chd && (*begin)->chd[++i])
		if (((*begin)->chd[i]->way & (1 << way)) &&
		(!((*begin)->chd[i]->only_way)
		|| ((*begin)->chd[i]->way & (1 << way))) && ++check)
			index = i;
	if (check == 1)
	{
		(*begin)->way = (1 << way);
		if (!((*room)->next = (create_room((*begin)->chd[index]->name))))
			return (-1);
		(*room) = (*room)->next;
		(*begin) = (*begin)->chd[index];
	}
	else if (check > 1 && ((*begin)->way = 0) == 0)
	{
		if (!((*room)->next =
		(select_shortest_way((*begin)->chd, &(*begin), way))))
			return (-1);
		(*room) = (*room)->next ? (*room)->next : (*room);
	}
	return (check == 0);
}

t_way	*get_new_way(t_ant *begin, long long way, char *start_name)
{
	t_way	*ways;
	t_room	*room;
	t_room	*tmp;
	int		i;
	int		check;

	if (!(ways = (t_way *)malloc(sizeof(t_way)))
		|| (!(room = create_room(start_name))
			|| !(room->next = create_room(begin->name))))
		return (NULL);
	ways->rooms = room;
	room = room->next;
	ways->next = NULL;
	while (begin->hot != END)
	{
		i = -1;
		check = 0;
		check = ft_checker(&begin, way, &room, check);
		if (check == -1 || check == 1)
			return ((check == -1) ? NULL : ways);
		tmp = ways->rooms;
		while (tmp)
			tmp = tmp->next;
	}
	return (ways);
}

t_way	*ft_probe(t_ant *begin)
{
	int		i;
	int		check;
	int		tmp;
	t_way	*way;
	t_way	*curr;

	i = -1;
	curr = NULL;
	way = NULL;
	while (++i < 64)
	{
		check = 0;
		tmp = get_tmp(begin, &check, i, tmp);
		if (check == 1)
		{
			if ((!way && !(way = get_new_way(begin->chd[tmp],
			i, begin->name))) || (curr && !(curr->next =
			get_new_way(begin->chd[tmp], i, begin->name))))
				return (NULL);
			curr = way->next ? curr->next : way;
			begin->chd[tmp]->way = 0;
			i = -1;
		}
	}
	return (way);
}

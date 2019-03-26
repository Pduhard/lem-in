/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/08 02:09:10 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/09 22:02:49 by sbedene     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

t_ant	*free_ant_hill(t_ant *list)
{
	t_ant	*tmp;

	while (list)
	{
		tmp = list->next;
		if (list->chd)
			free(list->chd);
		if (list->name)
			ft_strdel(&list->name);
		free(list);
		list = tmp;
	}
	return (NULL);
}

t_way	*free_ways(t_way *way)
{
	t_room	*tmp_room;
	t_way	*tmp_way;

	tmp_way = way;
	while (way)
	{
		tmp_room = way->rooms;
		while (way->rooms)
		{
			tmp_room = tmp_room->next;
			if (way->rooms->name)
				ft_strdel(&way->rooms->name);
			way->rooms->next = NULL;
			free(way->rooms);
			way->rooms = tmp_room;
		}
		tmp_way = tmp_way->next;
		if (way->rooms)
			free(way->rooms);
		way->next = NULL;
		free(way);
		way = tmp_way;
	}
	return (NULL);
}

int		ft_clean_exit(int error, t_data *data, char *file)
{
	char	*line;

	if (data)
	{
		free_ant_hill(data->ant_hill);
		free_ways(data->ways);
		ft_memdel((void**)(&data));
	}
	while (get_next_line(0, &line))
		ft_strdel(&line);
	ft_strdel(&file);
	if (error == -1)
		write(1, "ERROR\n", 6);
	return (0);
}

void	delete_rm(t_room *rm, t_room *tmp2)
{
	while (rm)
	{
		ft_strdel(&rm->name);
		tmp2 = rm->next;
		free(rm);
		rm = tmp2;
	}
}

int		delete_way(t_way **begin, t_way **to_del)
{
	t_way	*tmp;
	t_room	*tmp2;
	t_room	*rm;

	tmp = *begin;
	tmp2 = NULL;
	if (*begin == *to_del)
	{
		*begin = (*begin)->next;
		rm = (*to_del)->rooms;
		delete_rm(rm, tmp2);
		free(*to_del);
		return (*begin == NULL ? 0 : 1);
	}
	while (tmp->next != *to_del)
		tmp = tmp->next;
	rm = (*to_del)->rooms;
	delete_rm(rm, tmp2);
	tmp->next = tmp->next->next;
	free(*to_del);
	return (1);
}

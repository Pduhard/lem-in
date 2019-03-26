/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_probe_utils.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/08 03:10:29 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/08 03:13:47 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*create_room(char *name)
{
	t_room	*room;

	if (!(room = (t_room *)malloc(sizeof(*room))))
		return (NULL);
	room->name = ft_strdup(name);
	room->next = NULL;
	room->ant = 0;
	return (room);
}

void	ft_init_value(int *index, int *i, int *test, int *min)
{
	*index = -1;
	*i = -1;
	*test = 0;
	*min = -1;
}

int		get_tmp(t_ant *begin, int *check, int i, int tmp)
{
	int		j;

	j = 0;
	while (begin->chd && begin->chd[j])
	{
		if ((begin->chd[j]->way & (1 << i)) && (tmp = j) == j)
			*check = *check + 1;
		j++;
	}
	return (tmp);
}

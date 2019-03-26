/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_trim.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/07 19:47:44 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/09 17:39:45 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	remove_child(t_ant *child, t_ant *parent)
{
	int		i;
	int		j;

	i = 0;
	while (child->chd && child->chd[i])
	{
		if (child->chd[i] == parent)
		{
			j = 0;
			while (child->chd[j])
				j++;
			child->chd[i] = child->chd[j - 1];
			child->chd[j - 1] = NULL;
		}
		i++;
	}
}

t_ant	*check_first_trim(t_data *data, int *check)
{
	t_ant	*begin;
	int		child_nb;

	*check = 0;
	begin = data->ant_hill;
	while ((child_nb = get_child_nbr(begin->chd)) <= 1
		&& begin->hot != START && begin->hot != END)
	{
		data->ant_hill = begin->next;
		if (child_nb == 1)
			remove_child(begin->chd[0], begin);
		ft_strdel(&begin->name);
		if (begin->chd)
			free(begin->chd);
		free(begin);
		begin = data->ant_hill;
		*check = 1;
	}
	return (begin);
}

void	pr_trim(t_data *data)
{
	t_ant	*begin;
	t_ant	*tmp;
	int		check;
	int		child_nb;

	check = 1;
	while (check == 1 && (begin = check_first_trim(data, &check)))
		while (begin && begin->next)
		{
			if ((child_nb = get_child_nbr(begin->next->chd)) <= 1
					&& begin->next->hot != START && begin->next->hot != END)
			{
				tmp = begin->next->next;
				if (child_nb == 1)
					remove_child(begin->next->chd[0], begin->next);
				ft_strdel(&begin->next->name);
				if (begin->next->chd)
					free(begin->next->chd);
				free(begin->next);
				begin->next = tmp;
				check = 1;
			}
			begin = begin->next;
		}
}

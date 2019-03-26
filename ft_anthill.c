/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_anthill.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sbedene <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/01 03:01:44 by sbedene      #+#   ##    ##    #+#       */
/*   Updated: 2018/12/07 23:42:30 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int			pr_backtrack_end(t_ant *begin, t_ant *start)
{
	int		way;
	int		target;
	int		ret;

	target = 1;
	ret = 1;
	while (ret != 0)
	{
		way = -1;
		ret = 0;
		while (begin->chd && begin->chd[++way])
		{
			if (!(begin->way & (1 << way)))
				begin->way += (1 << way);
			ret = pr_backtrack_heat(begin->chd[way], 1, way, target) | ret;
		}
		target++;
	}
	if (start->chd)
		free(start->chd);
	start->chd = NULL;
	return (1);
}

int			is_child_of(t_ant *child, t_ant *parent)
{
	int		i;

	i = 0;
	while (parent->chd && parent->chd[i])
	{
		if (parent->chd[i] == child)
			return (1);
		i++;
	}
	return (0);
}

int			pr_remove_child(t_ant *begin, int way, int *i)
{
	int		j;
	int		check;

	*i = -1;
	check = 0;
	j = 0;
	while (begin->chd && begin->chd[++(*i)])
	{
		if ((begin->chd[*i]->way & (1 << way)) && begin->chd[*i]->hot
		!= START && is_child_of(begin, begin->chd[*i]))
		{
			j = 0;
			while (begin->chd[j])
				j++;
			begin->chd[*i] = begin->chd[j - 1];
			begin->chd[j - 1] = NULL;
			check = 1;
		}
	}
	return (check);
}

int			pr_backtrack_heat(t_ant *begin, int tier, int way, int target)
{
	int		i;
	int		ret;
	int		check;

	i = -1;
	ret = 0;
	check = 0;
	if (tier == target)
		check = pr_remove_child(begin, way, &i);
	if (tier == target && begin->chd && i == 1 && begin->chd[0])
		begin->chd[0]->only_way = begin;
	i = -1;
	if (begin->hot != START && tier != target)
	{
		while (begin->chd && begin->chd[++i])
			ret = pr_backtrack_heat(begin->chd[i],
			tier + 1, way, target) | ret;
		return (ret);
	}
	else if (!(begin->way & (1 << way)) && (begin->only_way == NULL
	|| (begin->only_way->way & (1 << way))))
		begin->way += (1 << way);
	else
		return (check);
	return (1);
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_find_ways.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 07:47:27 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/09 22:51:41 by sbedene     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int		get_child_nbr(t_ant **chd)
{
	int		i;

	if (chd == NULL)
		return (0);
	i = 0;
	while (chd[i])
		i++;
	return (i);
}

int		is_last_way(t_room *tmp)
{
	while (tmp)
	{
		if (tmp->ant != 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	chuuuuut(t_ant **ipt, t_ant **curr)
{
	*ipt = NULL;
	*curr = NULL;
}

int		chuuuuut2(char **line, char **file, int ret)
{
	*file = ft_strfjoin(*file, ft_strjoin(*line, "\n"));
	ft_strdel(line);
	ret = get_next_line(0, line);
	return (ret);
}

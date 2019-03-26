/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_heat.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/05 11:14:28 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/08 00:29:48 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	set_ways(t_ant *room, int way)
{
	int		i;

	i = -1;
	if (room->hot == -1)
		return ;
	while (room->chd && room->chd[++i])
		if (room->chd[i]->hot > room->hot + 1)
		{
			if (!(room->chd[i]->way & 1 << way))
				room->chd[i]->way += way == 0 ? 1 << i : 1 << (way - 1);
		}
	i = -1;
	while (room->chd && room->chd[++i])
		if (room->chd[i]->hot > room->hot)
			set_ways(room->chd[i], way == 0 ? i + 1 : way);
}

void	set_heat(t_ant *room, int heat, int way)
{
	int		i;

	i = -1;
	if (room->hot == -1)
		return ;
	while (room->chd && room->chd[++i])
		if (room->chd[i]->hot == -2 || room->chd[i]->hot > heat + 1)
			room->chd[i]->hot = heat + 1;
	i = -1;
	while (room->chd && room->chd[++i])
		if (room->chd[i]->hot > room->hot)
			set_heat(room->chd[i], heat + 1, way == 0 ? i + 1 : way);
}

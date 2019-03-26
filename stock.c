/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   stock.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/04 06:59:04 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/09 22:30:16 by sbedene     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

t_ant	*parse_error(char **name, char **str, t_ant *to_free)
{
	ft_strdel(name);
	ft_strdel(str);
	free(to_free);
	return (NULL);
}

t_ant	*ft_antnew(char *line, int hot, t_data *data, t_ant *ipt)
{
	t_ant	*lstnew;
	char	*str;

	str = ft_strtrim(line);
	if (!(lstnew = (t_ant*)malloc(sizeof(t_ant))))
		return (NULL);
	lstnew->name = ft_strsub(str, 0, get_name_len(str));
	if ((ft_strchr(lstnew->name, '-')) || !(get_coord(lstnew, str, ipt)))
		return (parse_error(&lstnew->name, &str, lstnew));
	lstnew->ant = hot == START ? 0 : NO_ANT;
	lstnew->hot = ((hot == END && !(data->end))
			|| (hot == START && !(data->start))
				|| hot == NONE) ? hot : NONE;
	lstnew->next = NULL;
	lstnew->chd = NULL;
	lstnew->only_way = NULL;
	lstnew->way = 0;
	if (!(data->end))
		data->end = hot == END ? lstnew : data->end;
	if (!(data->start))
		data->start = hot == START ? lstnew : data->start;
	ft_strdel(&str);
	return (lstnew);
}

int		pr_create_child(t_ant *ipt, t_ant ***child)
{
	t_ant	**new_child;
	int		i;

	i = 0;
	while (*child && (*child)[i])
		if ((*child)[i++] == ipt)
			return (1);
	if (!(new_child = (t_ant **)malloc((i + 2) * sizeof(t_ant *))))
	{
		free(*child);
		return (0);
	}
	i = 0;
	while (*child && (*child)[i])
	{
		new_child[i] = (*child)[i];
		i++;
	}
	if (*child)
		free(*child);
	new_child[i] = ipt;
	new_child[i + 1] = NULL;
	*child = new_child;
	return (1);
}

int		add_link(char *name1, char *name2, t_ant *ipt)
{
	t_ant *room1;
	t_ant *room2;

	room1 = NULL;
	room2 = NULL;
	if (!name1 || !name2)
		return (0);
	while (ipt && (!room1 || !room2))
	{
		if (!room1 && !ft_strcmp(name1, ipt->name))
			room1 = ipt;
		else if (!room2 && !ft_strcmp(name2, ipt->name))
			room2 = ipt;
		ipt = ipt->next;
	}
	if (name1)
		ft_strdel(&name1);
	if (name2)
		ft_strdel(&name2);
	if (!room1 || !room2 || !(pr_create_child(room2, &(room1->chd)))
			|| !(pr_create_child(room1, &(room2->chd))))
		return (0);
	return (1);
}

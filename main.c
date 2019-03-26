/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/01 03:07:07 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/09 22:34:33 by sbedene     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

t_data		*create_data(char **file)
{
	t_data	*data;

	if (!(data = (t_data*)malloc(sizeof(*data))))
		return (NULL);
	data->start = NULL;
	data->end = NULL;
	data->ant_hill = NULL;
	data->ways = NULL;
	if (!(data->ant_hill = pr_parsing(&data->nb_ant, data, file))
			|| data->start == NULL || data->end == NULL)
	{
		ft_clean_exit(0, data, *file);
		return (NULL);
	}
	return (data);
}

t_data		*ft_sort_ways(t_data *data)
{
	t_way	*tmp;
	t_room	*swp;
	int		len;

	tmp = data->ways;
	while (tmp->next)
	{
		if (tmp->next->len < tmp->len)
		{
			len = tmp->len;
			swp = tmp->rooms;
			tmp->rooms = tmp->next->rooms;
			tmp->len = tmp->next->len;
			tmp->next->rooms = swp;
			tmp->next->len = len;
		}
		tmp = tmp->next;
	}
	return (data);
}

int			fill_len(t_data *data)
{
	t_way	*tmp_ways;
	t_way	*tmp;
	t_room	*tmp_room;
	int		len;
	int		check;

	tmp_ways = data ? data->ways : NULL;
	while (tmp_ways && (len = 0) == 0
			&& (check = 0) == 0)
	{
		tmp_room = tmp_ways->rooms;
		while (tmp_room)
		{
			check = !ft_strcmp(tmp_room->name, data->start->name) ? 1 : check;
			tmp_room = tmp_room->next;
			len++;
		}
		tmp = tmp_ways->next;
		if (check == 0 && len && !(delete_way(&data->ways, &tmp_ways)))
			return (0);
		if (check != 0)
			tmp_ways->len = len;
		tmp_ways = tmp;
	}
	return (1);
}

int			main(int argc, char **argv)
{
	t_data	*data;
	char	*file;

	file = NULL;
	if (argc != 1 && argv)
		;
	if (!(data = create_data(&file)))
		return (ft_clean_exit(-1, data, NULL));
	pr_trim(data);
	pr_backtrack_end(data->end, data->start);
	if (!(data->ways = ft_probe(data->end)))
		return (ft_clean_exit(-1, data, file));
	if (!(fill_len(data)))
		return (ft_clean_exit(-1, data, file));
	data = ft_sort_ways(data);
	ft_putstr(file);
	ft_putchar('\n');
	ant_send(data, get_nb_turn(data));
	return (ft_clean_exit(1, data, file));
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/04 06:20:23 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/09 22:52:04 by sbedene     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int		return_valid(char **line, int to_ret)
{
	ft_strdel(line);
	return (to_ret);
}

void	skip_comm(char **line, int *hot, char **file)
{
	*hot = NONE;
	while ((*line)[0] == '#')
	{
		if (!ft_strcmp(*line, "##start"))
			*hot = START;
		else if (!ft_strcmp(*line, "##end"))
			*hot = END;
		*file = ft_strfjoin(*file, ft_strjoin(*line, "\n"));
		ft_strdel(line);
		get_next_line(0, line);
	}
}

t_ant	*pr_get_rooms(int *i, char **line, t_data *data, char **f)
{
	t_ant	*ipt;
	t_ant	*curr;
	int		hot;
	int		ret;

	chuuuuut(&ipt, &curr);
	while ((ret = get_next_line(0, line)))
	{
		skip_comm(line, &hot, f);
		if (is_valid_room(ft_strtrim(*line), 0))
		{
			if ((!ipt && !(ipt = ft_antnew(*line, hot, data, NULL))) ||
					(curr && !(curr->next = ft_antnew(*line, hot, data, ipt))))
				return (free_ant_hill(ipt));
			*f = ft_strfjoin(*f, ft_strfjoin(ft_rmsps(*line), ft_strdup("\n")));
			ft_strdel(line);
			curr = (ipt->next ? curr->next : ipt);
		}
		else if (!(is_valid_tube(*line)))
			return (free_ant_hill(ipt));
		else
			break ;
		*i = *i + 1;
	}
	return (ret == 0 ? free_ant_hill(ipt) : ipt);
}

int		pr_get_tubes(t_ant *ipt, char *line, char **f)
{
	int		ret;
	char	*tmp;

	ret = 1;
	while (ret > 0)
	{
		if (is_valid_tube(line) && (tmp = ft_strchr(line, '-')))
		{
			if (!(add_link(ft_strsub(line, 0, tmp - line),
				ft_strsub(line, tmp - line + 1,
					ft_strlen(line) - (tmp - line + 1)), ipt)))
				return (return_valid(&line, 1));
			ret = chuuuuut2(&line, f, ret);
		}
		else if (line && line[0] == '#')
			while (line && line[0] == '#')
				ret = chuuuuut2(&line, f, ret);
		else
			break ;
	}
	return (return_valid(&line, 1));
}

t_ant	*pr_parsing(long *nb_ant, t_data *data, char **file)
{
	char	*line;
	t_ant	*ipt;
	int		i;

	line = NULL;
	get_next_line(0, &line);
	*nb_ant = ft_atoll(line);
	if (line)
		ft_strdel(&line);
	ft_lltoa(*nb_ant, file);
	*file = ft_strfjoin(*file, ft_strdup("\n"));
	if (*nb_ant <= 0)
		return (NULL);
	i = 0;
	if (!(ipt = pr_get_rooms(&i, &line, data, file)))
	{
		ft_strdel(&line);
		return (NULL);
	}
	if (!(line) || !(pr_get_tubes(ipt, line, file)))
	{
		ft_strdel(&line);
		return (NULL);
	}
	return (ipt);
}

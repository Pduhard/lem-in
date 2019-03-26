/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_utils.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/04 06:22:36 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/09 22:52:24 by sbedene     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int		get_name_len(char *str)
{
	int		i;

	i = 0;
	while (str && !(ft_isspace(str[i])))
		i++;
	return (i);
}

int		get_coord(t_ant *new_rm, char *line, t_ant *ipt)
{
	int		i;

	i = get_name_len(line);
	while (ft_isspace(line[i++]))
		;
	new_rm->x = ft_atoi(&line[i - 1]);
	while (ft_isdigit(line[i++]))
		;
	while (ft_isspace(line[i++]))
		;
	new_rm->y = ft_atoi(&line[i - 1]);
	while (ipt)
	{
		if ((ipt->x == new_rm->x && ipt->y == new_rm->y)
				|| !ft_strcmp(ipt->name, new_rm->name))
			return (0);
		ipt = ipt->next;
	}
	return (1);
}

int		is_valid_room(char *line, int check)
{
	int		i;

	i = 0;
	if (line[0] == 'L' || line[0] == '#')
		return (return_valid(&line, 0));
	while (line[i] && !(ft_isspace(line[i])) && (check = 1))
		i++;
	if (check != 1 || !(ft_isspace(line[i])))
		return (return_valid(&line, 0));
	while ((line[i] && (ft_isspace(line[i]))) || (check = 0))
		i++;
	if ((long long)ft_atoi(&line[i]) != ft_atoll(&line[i]))
		return (return_valid(&line, 0));
	while (ft_isdigit(line[i]) && (check = 1))
		i++;
	if (check != 1 || !(ft_isspace(line[i])))
		return (return_valid(&line, 0));
	while ((line[i] && ft_isspace(line[i])) || (check = 0))
		i++;
	if ((long long)ft_atoi(&line[i]) != ft_atoll(&line[i]))
		return (return_valid(&line, 0));
	while (ft_isdigit(line[i]) && (check = 1))
		i++;
	return (return_valid(&line, (check != 1 || line[i] != '\0') ? 0 : 1));
}

int		is_valid_tube(char *line)
{
	int		check;
	int		i;

	check = 0;
	i = 0;
	if (line[0] == 'L' || line[0] == '#')
		return (0);
	while (line[i] && line[i] != '-' && (check = 1))
		i++;
	if (check != 1 || line[i++] != '-')
		return (0);
	check = 0;
	while (line[i] && (check = 1))
		i++;
	if (check != 1 || line[i] != '\0')
		return (0);
	return (1);
}

char	*ft_rmsps(char *line)
{
	int		i;
	int		j;
	int		check;
	char	*tmp;
	char	*tmp2;

	check = 0;
	tmp = NULL;
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]) && (check = 1) == 1)
			i++;
		j = i;
		while (line[i] && !ft_isspace(line[i]))
			i++;
		tmp = ft_strfjoin(tmp, ft_strfjoin(check == 1 ? ft_strdup(" ") : NULL,
					ft_strsub(line, j, i - j)));
	}
	tmp2 = ft_strtrim(tmp);
	free(tmp);
	return (tmp2);
}

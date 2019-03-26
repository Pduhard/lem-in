/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 18:48:05 by pduhard-     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 16:00:30 by pduhard-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, int nb)
{
	int		x;
	int		cpt;

	x = 0;
	cpt = 0;
	while (s1[x] != '\0')
		x++;
	while (s2[cpt] != '\0' && cpt < nb)
		s1[x++] = s2[cpt++];
	s1[x] = '\0';
	return (s1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_sol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeanna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:39:04 by djeanna           #+#    #+#             */
/*   Updated: 2019/06/27 17:39:05 by djeanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lem_in.h"

int				ft_shift(t_hasht *h, int x, int y, t_lis **ants)
{
	int i;

	i = -1;
	while (++i <= h->top)
	{
		h->arr[i]->x += x;
		h->arr[i]->y += y;
	}
	i = -1;
	while (++i < h->num_a)
	{
		(*ants)[i].x += x;
		(*ants)[i].y += y;
	}
	return (0);
}

char			*ft_read_sol(void)
{
	char *res;
	char *tmp;
	char *buf;

	if (!(buf = ft_strnew(100000)))
		return (NULL);
	res = NULL;
	while (read(0, buf, 100000) > 0)
	{
		tmp = res;
		res = ft_strjoin(res, buf);
		tmp ? ft_strdel(&tmp) : NULL;
		ft_bzero(buf, 100000);
	}
	ft_strdel(&buf);
	return (res);
}

static int		ft_parse(char **str, int *i_ant, int *new_room)
{
	if (**str == 'L')
		*str = *str + 1;
	*i_ant = ft_atoi(*str);
	while (ft_isdigit(**str))
		*str = *str + 1;
	if (**str != '-')
		return (0);
	*str = *str + 1;
	*new_room = ft_atoi(*str);
	while (ft_isdigit(**str))
		*str = *str + 1;
	if (**str == ' ')
		*str = *str + 1;
	else if (**str != '\n')
		return (0);
	return (1);
}

int				ft_go(t_sdl s, t_hasht h, char **str, t_lis **ants)
{
	int i_ant;
	int new_room;

	if (!**str)
		return (1);
	while (**str && **str != '\n')
	{
		if (!ft_parse(str, &i_ant, &new_room) || new_room > h.top)
			return (1);
		h.ant = &(*ants)[i_ant - 1];
		if (!ft_mv(s, h.arr[new_room], &h, *ants))
			return (1);
		(*ants)[i_ant - 1].x = h.arr[new_room]->x;
		(*ants)[i_ant - 1].y = h.arr[new_room]->y;
		SDL_SetRenderTarget(s.ren, s.bg);
		SDL_RenderCopy(s.ren, s.bg, NULL, NULL);
		ft_paste_rooms(&h, s);
		ft_paste_ants(&h, *ants, s);
	}
	if (**str == '\n')
		*str = *str + 1;
	return (0);
}

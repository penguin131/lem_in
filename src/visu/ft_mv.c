/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeanna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 16:17:42 by djeanna           #+#    #+#             */
/*   Updated: 2019/07/01 16:19:30 by djeanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lem_in.h"

static void		ft_paste_all(t_sdl s, t_hasht *h, t_lis *ants)
{
	SDL_SetRenderTarget(s.ren, s.bg);
	SDL_RenderCopy(s.ren, s.bg, NULL, NULL);
	ft_paste_rooms(h, s);
	ft_paste_ants(h, ants, s);
}

static float	ft_dy(t_lis *room, t_hasht *h)
{
	if (room->x - h->ant->x != 0)
	{
		if (room->x > h->ant->x)
			return ((room->y - h->ant->y) * 1.0 / (room->x - h->ant->x) * 1.0);
		return ((room->y - h->ant->y) * 1.0 / (h->ant->x - room->x) * 1.0);
	}
	if (room->y < h->ant->y)
		return (-2);
	return (2);
}

static void		ft_xy(t_sdl s, t_lis *room, t_hasht *h, t_lis *ants)
{
	float x;
	float y;

	x = h->ant->x;
	y = h->ant->y;
	while ((int)x != room->x && (int)y != room->y)
	{
		h->ant->x = x;
		h->ant->y = y;
		ft_paste_all(s, h, ants);
		x += 1;
		y += room->dy;
	}
}

static void		ft_x(t_sdl s, t_lis *room, t_hasht *h, t_lis *ants)
{
	float x;
	float y;

	x = h->ant->x;
	y = h->ant->y;
	while ((int)x != room->x)
	{
		h->ant->x = x;
		h->ant->y = y;
		ft_paste_all(s, h, ants);
		x += 2;
	}
}

int				ft_mv(t_sdl s, t_lis *room, t_hasht *h, t_lis *ants)
{
	float	x;
	float	y;

	if (!room)
		return (0);
	room->dy = ft_dy(room, h);
	x = h->ant->x;
	y = h->ant->y;
	if ((int)x != room->x && (int)y != room->y)
		ft_xy(s, room, h, ants);
	else if ((int)x != room->x)
		ft_x(s, room, h, ants);
	else if ((int)y != room->y)
		while ((int)y != room->y)
		{
			h->ant->x = x;
			h->ant->y = y;
			ft_paste_all(s, h, ants);
			y += room->dy;
		}
	ft_paste_all(s, h, ants);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paste_room_help.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeanna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 16:26:49 by djeanna           #+#    #+#             */
/*   Updated: 2019/07/01 16:26:50 by djeanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lem_in.h"

void	ft_win_size(int x, int y, t_sdl *s)
{
	if (x > s->win_x)
		s->win_x = x + 50;
	if (y > s->win_y)
		s->win_y = y + 10;
}

void	ft_init_l(SDL_Rect *srcr, SDL_Rect *destr, t_sdl s)
{
	srcr->x = 0;
	srcr->y = 0;
	srcr->w = 700;
	srcr->h = 700;
	destr->w = s.size_sqr;
	destr->h = s.size_sqr;
}

void	ft_paste_l(SDL_Rect srcr, SDL_Rect destr, t_sdl s, int i)
{
	if (i)
	{
		SDL_SetRenderTarget(s.ren, s.end);
		SDL_RenderCopy(s.ren, s.end, &srcr, &destr);
	}
	else
	{
		SDL_SetRenderTarget(s.ren, s.sqr);
		SDL_RenderCopy(s.ren, s.sqr, &srcr, &destr);
	}
}

t_lis	*ft_init_ants(t_hasht h)
{
	t_lis	*ants;
	int		i;

	if (!(ants = malloc(sizeof(t_lis) * h.num_a)))
		return (NULL);
	i = -1;
	while (++i < h.num_a)
	{
		ants[i].i = i + 1;
		ants[i].x = h.arr[h.start.i]->x;
		ants[i].y = h.arr[h.start.i]->y;
	}
	return (ants);
}

void	ft_paste_ants(t_hasht *h, t_lis *ants, t_sdl s)
{
	int			i;
	SDL_Rect	srcr;
	SDL_Rect	destr;

	i = -1;
	srcr.x = 0;
	srcr.y = 0;
	srcr.w = 2000;
	srcr.h = 2000;
	destr.w = s.size_sqr;
	destr.h = s.size_sqr;
	while (++i <= h->num_a)
	{
		destr.x = ants[i].x;
		destr.y = ants[i].y;
		SDL_SetRenderTarget(s.ren, s.ant);
		SDL_RenderCopy(s.ren, s.ant, &srcr, &destr);
	}
	SDL_RenderPresent(s.ren);
}

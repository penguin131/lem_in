/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeanna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:01:04 by djeanna           #+#    #+#             */
/*   Updated: 2019/06/24 12:01:05 by djeanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lem_in.h"

static int	ft_err(void)
{
	write(1, "Error\n", 7);
	return (0);
}

static int	ft_init2(t_sdl *s)
{
	if (!(s->bmp = SDL_LoadBMP("pic/sqr.bmp")))
		return (ft_err());
	s->sqr = SDL_CreateTextureFromSurface(s->ren, s->bmp);
	SDL_FreeSurface(s->bmp);
	if (!(s->sqr))
		return (ft_err());
	if (!(s->bmp = SDL_LoadBMP("pic/sqr_end.bmp")))
		return (ft_err());
	s->end = SDL_CreateTextureFromSurface(s->ren, s->bmp);
	SDL_FreeSurface(s->bmp);
	if (!(s->end))
		return (ft_err());
	return (1);
}

int			ft_init(t_sdl *s)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (ft_err());
	if (!(s->win = SDL_CreateWindow("Cute ants!", 100, 100, s->win_x,
			s->win_y, SDL_WINDOW_SHOWN)))
		return (ft_err());
	if (!(s->ren = SDL_CreateRenderer(s->win, -1, SDL_RENDERER_ACCELERATED |
											SDL_RENDERER_PRESENTVSYNC)))
		return (ft_err());
	if (!(s->bmp = SDL_LoadBMP("pic/antfarm.bmp")))
		return (ft_err());
	s->bg = SDL_CreateTextureFromSurface(s->ren, s->bmp);
	SDL_SetTextureBlendMode(s->bg, SDL_BLENDMODE_NONE);
	SDL_FreeSurface(s->bmp);
	if (!(s->bg))
		return (ft_err());
	if (!(s->bmp = SDL_LoadBMP("pic/ant.bmp")))
		return (ft_err());
	s->ant = SDL_CreateTextureFromSurface(s->ren, s->bmp);
	SDL_FreeSurface(s->bmp);
	if (!(s->ant))
		return (ft_err());
	s->size_sqr = 30;
	return (ft_init2(s));
}

void		ft_quit(t_sdl *s)
{
	SDL_DestroyTexture(s->sqr);
	SDL_DestroyTexture(s->ant);
	SDL_DestroyTexture(s->bg);
	SDL_DestroyTexture(s->end);
	SDL_DestroyRenderer(s->ren);
	SDL_DestroyWindow(s->win);
	SDL_Quit();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_visu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeanna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 09:17:52 by djeanna           #+#    #+#             */
/*   Updated: 2019/06/24 09:17:53 by djeanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lem_in.h"

void				ft_fill(int x, int y, int lvl, t_lis **l)
{
	(*l)->lvl = lvl;
	(*l)->x = x;
	(*l)->y = y;
}

static char			*ft_is_data_validd(t_hasht *h, char *str)
{
	t_lis *tmp;
	t_lis *tmp2;

	if (!str)
		return (0);
	if (((str = ft_get_ants(str, &(h->num_a))) && h->num_a <= 0) ||
			!(str = ft_add_rooms(h, str)))
		return (NULL);
	while (*str && *str != 'L')
	{
		if (*str == '#')
			str = skip_until_slashn(str);
		else
		{
			if (!(tmp = ft_hasht_search(h, str, '-')))
				return (0);
			str = ft_skip_until_tire(str);
			if (!(tmp2 = ft_hasht_search(h, str, '\n')))
				return (0);
			str = skip_until_slashn(str);
			ft_lis_pushback(&tmp, ft_lis_copy(tmp2));
			ft_lis_pushback(&tmp2, ft_lis_copy(tmp));
		}
	}
	return (str);
}

static int			ft_event(t_sdl s, t_hasht *h, char **str, t_lis **ants)
{
	SDL_Event		e;

	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
			return (1);
		else if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_RETURN)
				return (ft_go(s, *h, str, ants));
			else if (e.key.keysym.sym == SDLK_UP)
				return (ft_shift(h, 0, -2, ants));
			else if (e.key.keysym.sym == SDLK_DOWN)
				return (ft_shift(h, 0, 2, ants));
			else if (e.key.keysym.sym == SDLK_RIGHT)
				return (ft_shift(h, 2, 0, ants));
			else if (e.key.keysym.sym == SDLK_LEFT)
				return (ft_shift(h, -2, 0, ants));
			else if (e.key.keysym.sym == SDLK_ESCAPE)
				return (1);
		}
	}
	return (0);
}

void				ft_visu(t_hasht h, t_sdl s, char *str)
{
	SDL_Event		e;
	int				quit;
	t_lis			*ants;

	if (!ft_init(&s) || !(ants = ft_init_ants(h)))
		return ;
	quit = 0;
	while (!quit)
	{
		SDL_SetRenderTarget(s.ren, s.bg);
		SDL_RenderCopy(s.ren, s.bg, NULL, NULL);
		ft_paste_rooms(&h, s);
		ft_paste_ants(&h, ants, s);
		quit = ft_event(s, &h, &str, &ants);
	}
	ft_quit(&s);
}

int					main(int c, char **v)
{
	char		*str;
	char		*c_str;
	t_sdl		s;
	t_hasht		h;

	str = ft_read_sol();
	if (!ft_strcmp(str, "Error\n"))
	{
		ft_strdel(&str);
		return (write(1, "Error\n", 6));
	}
	ft_hasht_new(&h);
	h.start.name = NULL;
	h.end.name = NULL;
	c_str = ft_is_data_validd(&h, str);
	if (!c_str)
	{
		return (write(1, "Error\n", 6));
	}
	if (!ft_init_rooms(&h, &s))
		return (write(1, "Error_visu: max num of rooms\n", 29));
	ft_visu(h, s, c_str);
	ft_hash_del(&h);
	ft_strdel(&str);
	return (0);
}

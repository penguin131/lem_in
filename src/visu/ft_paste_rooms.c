/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paste_rooms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeanna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:49:54 by djeanna           #+#    #+#             */
/*   Updated: 2019/06/25 16:49:55 by djeanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lem_in.h"

void				zero_lvl_htable(t_hasht *h)
{
	t_lis	*tmp;
	int		i;

	i = -1;
	while (++i <= h->top)
	{
		tmp = h->arr[i];
		while (tmp)
		{
			tmp->lvl = -1;
			tmp = tmp->next;
		}
	}
}

void				ft_paste_rooms(t_hasht *h, t_sdl s)
{
	int			i;
	SDL_Rect	srcr;
	SDL_Rect	destr;
	t_lis		*tmp;

	i = -1;
	ft_init_l(&srcr, &destr, s);
	while (++i <= h->top)
	{
		if (!(h->arr[i]))
			continue ;
		destr.x = h->arr[i]->x;
		destr.y = h->arr[i]->y;
		ft_paste_l(srcr, destr, s, (h->end.i == i || h->start.i == i));
		tmp = h->arr[i]->next;
		if (h->arr[i]->x > 0 && h->arr[i]->y > 0)
			while (tmp)
			{
				if (h->arr[tmp->i]->x < 1000000 && h->arr[tmp->i]->y < 1000000)
					SDL_RenderDrawLine(s.ren, h->arr[i]->x + 15, h->arr[i]->y
					+ 15, h->arr[tmp->i]->x + 15, h->arr[tmp->i]->y + 15);
				tmp = tmp->next;
			}
	}
}

static t_stack		*check_links_down(t_hasht *h, t_stack *source,
												int lvl, t_sdl *s)
{
	t_stack		*res;
	t_lis		*tmp;
	static int	x = 10;
	int			y;

	res = NULL;
	x += 60;
	y = 10;
	while (source)
	{
		tmp = h->arr[source->nb];
		while ((tmp = tmp->next))
		{
			if (h->arr[tmp->i]->lvl == -1)
			{
				ft_fill(x, y, lvl, &(h->arr[tmp->i]));
				y += 60;
				if (tmp->i != h->end.i)
					push_stack(&res, new_item(tmp->i, 0));
			}
		}
		source = source->next;
	}
	ft_win_size(x, y, s);
	return (res);
}

static int			going_down(t_hasht *h, t_sdl *s)
{
	t_stack	*current;
	t_stack	*next;
	int		lvl;

	h->arr[(h->start).i]->lvl = 0;
	h->arr[(h->start).i]->x = 10;
	h->arr[(h->start).i]->y = 40;
	current = NULL;
	push_stack(&current, new_item(h->start.i, 0));
	lvl = 1;
	if (!current)
		return (0);
	while ((next = check_links_down(h, current, lvl++, s)))
	{
		if (!current)
			return (0);
		free_stack(&current);
		current = next;
	}
	free_stack(&current);
	return (1);
}

int					ft_init_rooms(t_hasht *h, t_sdl *s)
{
	s->win_x = 0;
	s->win_y = 0;
	zero_lvl_htable(h);
	going_down(h, s);
	return (1);
}

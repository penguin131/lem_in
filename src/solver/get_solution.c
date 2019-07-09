/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_solution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smight <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 03:31:23 by smight            #+#    #+#             */
/*   Updated: 2019/07/02 03:31:28 by smight           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lem_in.h"

void		hold_link(t_hasht *h, int src, int dst)
{
	t_lis	*tmp;

	tmp = h->arr[src];
	while ((tmp = tmp->next))
	{
		if (tmp->i == dst && tmp->i != h->end.i)
		{
			tmp->is_hold = 1;
			if (tmp->reverse && tmp->reverse->is_hold)
			{
				tmp->used = 1;
				tmp->reverse->used = 1;
			}
		}
	}
}

void		fake_initialize(t_hasht *h, t_lis *tmp)
{
	if (!(h->fakes[tmp->i] = ft_memalloc(sizeof(t_lis))))
		return ;
	h->fakes[tmp->i]->is_fake = 1;
	h->fakes[tmp->i]->i = tmp->i;
}

void		*free_solution(t_solution *sol)
{
	int		i;
	t_stack	*tmp;
	t_stack	*tmp2;

	if (!sol)
		return (NULL);
	i = -1;
	while (sol->array && ++i < sol->ways)
	{
		tmp = sol->array[i];
		while (tmp)
		{
			tmp2 = tmp->next;
			free(tmp);
			tmp = tmp2;
		}
	}
	ft_memdel((void**)&sol->len);
	ft_memdel((void**)&sol->ants);
	ft_memdel((void**)&sol->array);
	ft_memdel((void**)&sol->end);
	ft_memdel((void**)&sol);
	return (NULL);
}

void		reverse_links_upgrade(t_hasht *h)
{
	t_lis	*tmp;
	t_lis	*start;
	int		i;

	i = -1;
	while (++i <= h->top)
	{
		start = h->arr[i];
		while ((start = start->next))
		{
			tmp = h->arr[start->i]->next;
			while (tmp->i != h->arr[i]->i)
				tmp = tmp->next;
			tmp->reverse = start;
		}
	}
}

void		zero_htable(t_hasht *h, int param)
{
	t_lis	*tmp;
	int		i;

	i = -1;
	while (++i <= h->top)
	{
		tmp = h->arr[i];
		if (param == FAKES)
			ft_memdel((void**)&h->fakes[i]);
		while (param != FAKES && tmp)
		{
			if (param == ROOT)
			{
				if (h->arr[tmp->i]->root && !h->arr[tmp->i]->root->is_fake)
					h->arr[tmp->i]->root = NULL;
			}
			else if (param == LINKS && ((tmp->reverse &&\
			!(tmp->reverse->is_hold && tmp->is_hold)) ||\
			!tmp->reverse))
				tmp->is_hold = 0;
			else if (param == ALL_ROOT)
				h->arr[tmp->i]->root = NULL;
			tmp = tmp->next;
		}
	}
}

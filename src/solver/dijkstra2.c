/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smight <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 19:53:27 by smight            #+#    #+#             */
/*   Updated: 2019/06/25 19:53:28 by smight           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lem_in.h"

void		get_fakes(t_hasht *h)
{
	t_lis	*tmp;
	t_lis	*tmp2;
	int		child;
	int		child2;

	tmp2 = NULL;
	child = h->end.i;
	tmp = h->arr[child]->root;
	while (tmp)
	{
		child2 = child;
		child = tmp->i;
		if (!h->fakes[tmp->i] && child != h->start.i)
		{
			fake_initialize(h, tmp);
			if (child2 != h->end.i)
			{
				tmp2 = h->arr[child]->root;
				h->arr[child]->root = h->fakes[child2];
				tmp = tmp2;
			}
		}
		tmp = (!h->fakes[tmp->i] && child != h->start.i &&\
		child2 != h->end.i) ? tmp2 : tmp->root;
	}
}

int			get_fake_link(t_hasht *h, int index)
{
	int i;

	i = -1;
	while (++i <= h->top)
	{
		if (h->arr[i]->root && h->arr[i]->root->is_fake\
		&& h->arr[i]->root->i == index)
			return (i);
	}
	return (-1);
}

void		push_params(t_stack **res, t_hasht *h, t_lis *tmp, int source)
{
	if (h->fakes && !h->fakes[tmp->i])
	{
		push_stack(res, new_item(tmp->i, REAL));
		h->arr[tmp->i]->root = h->arr[source];
	}
	else if (h->fakes && h->fakes[tmp->i])
	{
		push_stack(res, new_item(tmp->i, FAKE));
		h->fakes[tmp->i]->root = h->arr[source];
	}
}

t_stack		*check_links_down_d(t_hasht *h, t_stack *source, int *ways)
{
	t_stack *res;
	t_lis	*tmp;

	res = NULL;
	while (!(*ways) && source)
	{
		if (source->nb != -1 && source->is_fake)
			push_stack(&res, new_item(get_fake_link(h, source->nb), REAL));
		else if (source->nb != -1)
		{
			tmp = h->arr[source->nb];
			while (!(*ways) && (tmp = tmp->next))
			{
				if (tmp->is_hold || tmp->i == h->start.i ||\
				(h->arr[tmp->i]->root && !h->arr[tmp->i]->root->is_fake) ||\
				(h->fakes && h->fakes[tmp->i] && h->fakes[tmp->i]->root))
					continue ;
				push_params(&res, h, tmp, source->nb);
				if (tmp->i == h->end.i)
					(*ways)--;
			}
		}
		source = source->next;
	}
	return (res);
}

int			cycle_bfs(t_hasht *h)
{
	t_stack		*current;
	t_stack		*next;
	int			end;

	current = NULL;
	end = 0;
	push_stack(&current, new_item(h->start.i, REAL));
	while ((next = check_links_down_d(h, current, &end)))
	{
		free_stack(&current);
		current = next;
		if (end)
		{
			free_stack(&current);
			hold_way(h);
			get_fakes(h);
			return (1);
		}
	}
	free_stack(&current);
	return (0);
}

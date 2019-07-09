/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smight <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 04:56:19 by smight            #+#    #+#             */
/*   Updated: 2019/07/02 04:56:24 by smight           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lem_in.h"

void		zero(t_hasht *h, int param)
{
	if (param == 1)
	{
		zero_htable(h, ALL_ROOT);
		zero_htable(h, FAKES);
		zero_htable(h, LINKS);
	}
	else
	{
		zero_htable(h, LINKS);
		zero_htable(h, ALL_ROOT);
	}
}

t_stack		*new_item(int nb, int param)
{
	t_stack	*res;

	if ((res = ft_memalloc(sizeof(t_stack))))
	{
		res->nb = nb;
		res->is_fake = param;
	}
	return (res);
}

void		push_stack(t_stack **start, t_stack *new)
{
	if (!start || !new)
		return ;
	if (!*start)
	{
		*start = new;
		return ;
	}
	new->next = *start;
	(*start)->prev = new;
	*start = new;
}

void		free_stack(t_stack **start)
{
	if (*start)
	{
		free_stack(&(*start)->next);
		ft_memdel((void**)start);
	}
}

int			get_max_ways(t_hasht *h)
{
	int		i;
	int		j;
	t_lis	*tmp;

	i = 0;
	j = 0;
	tmp = h->arr[h->end.i];
	while ((tmp = tmp->next))
		i++;
	tmp = h->arr[h->start.i];
	while ((tmp = tmp->next))
		j++;
	return (i > j ? j : i);
}

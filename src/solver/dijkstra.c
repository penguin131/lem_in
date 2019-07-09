/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smight <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 02:57:43 by smight            #+#    #+#             */
/*   Updated: 2019/07/02 02:57:50 by smight           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lem_in.h"

void		hold_way(t_hasht *h)
{
	t_lis	*tmp;
	t_lis	*tmp2;
	int		index;

	tmp = h->arr[h->end.i]->root;
	index = h->end.i;
	while (tmp)
	{
		tmp2 = h->arr[tmp->i];
		while (tmp2 && tmp2->i != index)
			tmp2 = tmp2->next;
		if (!tmp2)
			return ;
		tmp2->is_hold = 1;
		tmp2->used = 1;
		tmp2->reverse->used = 1;
		index = tmp->i;
		tmp = tmp->root;
	}
}

t_stack		*go_upper(t_hasht *h, int *len)
{
	t_stack	*result;
	t_lis	*tmp;

	result = NULL;
	push_stack(&result, new_item(h->end.i, REAL));
	tmp = h->arr[h->end.i];
	while ((tmp = tmp->root))
	{
		(*len)++;
		if (tmp->i != h->start.i)
			h->arr[tmp->i]->is_hold = 1;
		push_stack(&result, new_item(tmp->i, REAL));
	}
	return (result);
}

t_stack		*check_links_down_c(t_hasht *h, t_stack *source, int *ways)
{
	t_stack *res;
	t_lis	*tmp;

	res = NULL;
	while (!(*ways) && source)
	{
		tmp = h->arr[source->nb];
		while (!(*ways) && (tmp = tmp->next))
		{
			if (h->arr[tmp->i]->is_hold || tmp->is_hold ||\
			tmp->i == h->start.i || h->arr[tmp->i]->root)
				continue ;
			push_stack(&res, new_item(tmp->i, REAL));
			h->arr[tmp->i]->root = h->arr[source->nb];
			if (tmp->i == h->end.i)
				(*ways)++;
		}
		source = source->next;
	}
	return (res);
}

t_stack		*get_min_way(t_hasht *h, int *len)
{
	t_stack *result;
	t_stack	*current;
	t_stack	*next;
	int		end;

	end = 0;
	*len = 0;
	current = NULL;
	push_stack(&current, new_item(h->start.i, REAL));
	while ((next = check_links_down_c(h, current, &end)))
	{
		free_stack(&current);
		current = next;
		if (end)
		{
			free_stack(&current);
			result = go_upper(h, len);
			return (result);
		}
	}
	free_stack(&current);
	return (NULL);
}

t_solution	*general_bfs(t_hasht *h, int ways)
{
	t_solution	*result;
	int			i;
	int			len;

	if (!(result = ft_memalloc(sizeof(t_solution))) ||\
	!(result->len = ft_memalloc(sizeof(int) * ways)) ||\
	!(result->array = ft_memalloc(sizeof(t_lis*) * ways)))
		return (free_solution(result));
	i = -1;
	while (++i < ways)
	{
		if (!(result->array[i] = get_min_way(h, &len)))
			break ;
		result->len[i] = len;
		zero_htable(h, ALL_ROOT);
	}
	result->ways = ways;
	return (result);
}

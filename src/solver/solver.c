/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smight <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:11:20 by smight            #+#    #+#             */
/*   Updated: 2019/06/17 18:11:22 by smight           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lem_in.h"

int		get_min(t_solution *s)
{
	int min;
	int min_index;
	int i;

	min_index = 0;
	min = s->ants[0];
	i = 1;
	while (i < s->ways && s->ants[0] == -1)
		min = s->ants[++i];
	i = 0;
	while (++i < s->ways)
	{
		if (min > s->ants[i] && s->ants[i] != -1)
		{
			min = s->ants[i];
			min_index = i;
		}
	}
	return (min_index);
}

void	get_ants_count(t_hasht *h, t_solution *s)
{
	int sum;
	int i;

	if (!s || !(s->ants = ft_memalloc(sizeof(int) * s->ways)))
		return ;
	i = -1;
	while (++i < s->ways)
		s->ants[i] = s->len[i];
	sum = h->num_a;
	while (sum)
	{
		s->ants[get_min(s)]++;
		sum--;
	}
	i = -1;
	while (++i < s->ways)
		s->ants[i] -= s->len[i];
}

int		initialization(t_hasht *h)
{
	h->max_ways = get_max_ways(h);
	h->result = general_bfs(h, 1);
	if (!h->result)
		return (0);
	get_ants_count(h, h->result);
	if (!(h->fakes = ft_memalloc(sizeof(t_lis**) * (h->size + 1))))
		return (0);
	return (1);
}

void	compare_solutions(t_hasht *h, t_solution *tmp1)
{
	get_ants_count(h, tmp1);
	if (get_max(tmp1) < get_max(h->result))
	{
		free_solution(h->result);
		h->result = tmp1;
	}
	else
		free_solution(tmp1);
}

int		solver(t_hasht *h)
{
	int			i;
	int			j;
	t_solution	*tmp1;

	i = 1;
	if (!initialization(h))
		return (0);
	while (++i <= h->max_ways)
	{
		zero(h, 1);
		cycle_bfs(h);
		j = 0;
		while (++j < i)
		{
			zero_htable(h, ROOT);
			if (!cycle_bfs(h))
				return (1);
		}
		zero(h, 1);
		if (!(tmp1 = general_bfs(h, i)))
			break ;
		compare_solutions(h, tmp1);
	}
	return (1);
}

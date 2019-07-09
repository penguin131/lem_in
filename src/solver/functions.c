/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smight <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:33:49 by smight            #+#    #+#             */
/*   Updated: 2019/07/02 17:33:51 by smight           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lem_in.h"

void	free_program(t_hasht *h)
{
	int i;

	i = -1;
	while (++i <= h->top)
		ft_lis_del(&h->fakes[i]);
	ft_memdel((void**)&h->fakes);
	free_solution(h->result);
}

int		get_max(t_solution *s)
{
	int max;
	int i;

	if (!s)
		return (0);
	max = s->ants[0] + s->len[0] - 1;
	i = 0;
	while (++i < s->ways)
	{
		if (s->ants[i] + s->len[i] - 1 > max)
			max = s->ants[i] + s->len[i] - 1;
	}
	return (max);
}

void	step_tmp_initialize(t_stack **tmp, t_solution *s, int i)
{
	!(s->end[i]) ? s->end[i] = s->array[i] : 0;
	(*tmp) = s->end[i];
	if (!tmp || !(*tmp))
		return ;
	if (!(*tmp)->next)
		(*tmp)->ant_number = 0;
	else
		(*tmp) = (*tmp)->next;
	s->end[i] = (*tmp);
}

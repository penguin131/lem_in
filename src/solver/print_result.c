/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smight <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 19:59:29 by smight            #+#    #+#             */
/*   Updated: 2019/06/22 19:59:31 by smight           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lem_in.h"
#include "stdio.h"

void	steps_ants(t_solution *s, t_hasht *h)
{
	int		i;
	t_stack	*tmp;

	i = -1;
	while (++i < s->ways)
	{
		step_tmp_initialize(&tmp, s, i);
		if (!tmp)
			return ;
		while (tmp->prev)
		{
			if (tmp->prev->ant_number > 0)
				tmp->ant_number = tmp->prev->ant_number;
			else if (s->ants[i])
			{
				tmp->ant_number = (h->cnt)++;
				s->ants[i]--;
			}
			tmp->prev->ant_number = 0;
			if (tmp->ant_number == 0)
				break ;
			tmp = tmp->prev;
		}
	}
}

int		check_end(t_stack **table, int ways)
{
	int	i;

	i = -1;
	while (++i < ways)
	{
		if (table && table[i])
			return (1);
	}
	return (0);
}

t_stack	**initialise_step(t_solution *s)
{
	t_stack	**res;
	int		i;

	if (!(res = ft_memalloc(sizeof(t_stack*) * s->ways)))
		return (NULL);
	i = -1;
	while (++i < s->ways)
		res[i] = s->end[i];
	return (res);
}

void	print_step(t_solution *s, t_hasht *h, int check)
{
	t_stack	**table;
	int		i;
	int		beg;

	if (!(table = initialise_step(s)))
		return ;
	beg = 0;
	while (check_end(table, s->ways))
	{
		i = -1;
		while (++i < s->ways)
		{
			if (table[i] && table[i]->ant_number)
			{
				beg++ ? printf(" ") : 0;
				!check ? printf("L%d-%s", table[i]->ant_number,
						h->arr[table[i]->nb]->name) : printf("L%d-%d",
						table[i]->ant_number, table[i]->nb);
			}
			if (table[i])
				table[i] = table[i]->prev;
		}
	}
	ft_memdel((void**)&table);
	printf("\n");
}

void	print_result(t_solution *s, t_hasht *h, int check)
{
	int i;
	int max;

	i = -1;
	h->cnt = 1;
	if (!s)
		return ;
	max = get_max(s);
	if (!(s->end = ft_memalloc(sizeof(t_stack*) * s->ways)))
		return ;
	while (++i < max)
	{
		steps_ants(s, h);
		print_step(s, h, check);
	}
	free_program(h);
}

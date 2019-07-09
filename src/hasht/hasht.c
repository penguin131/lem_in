/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hasht.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeanna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 14:06:54 by djeanna           #+#    #+#             */
/*   Updated: 2019/06/17 14:06:55 by djeanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lem_in.h"

void				ft_hasht_new(t_hasht *new)
{
	new->arr = NULL;
	new->start.name = NULL;
	new->end.name = NULL;
	new->top = -1;
	new->size = 0;
}

t_lis				*ft_hasht_search(t_hasht *h, char *str, char c)
{
	int i;

	i = -1;
	while (++i <= h->top)
		if (!ft_strcmp_edge_line(str, h->arr[i]->name, c))
			return (h->arr[i]);
	return (NULL);
}

int					ft_hasht_add(t_hasht *h, t_lis *a)
{
	t_lis	**arr;
	int		i;

	if (h->size - 1 == h->top)
	{
		if (!(arr = ft_memalloc(sizeof(t_lis *) * (h->size + 9))))
		{
			ft_hash_del(h);
			return (0);
		}
		i = -1;
		while (++i <= h->top)
			arr[i] = h->arr[i];
		free(h->arr);
		h->arr = arr;
		h->size += 9;
	}
	++(h->top);
	h->arr[h->top] = a;
	return (1);
}

void				ft_hash_del(t_hasht *h)
{
	int		i;

	i = -1;
	while (++i <= h->top)
	{
		ft_memdel((void**)&(h->arr)[i]->name);
		ft_lis_del(&h->arr[i]);
	}
	ft_memdel((void**)&h->arr);
}

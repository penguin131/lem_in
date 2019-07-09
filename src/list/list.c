/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeanna <djeanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:09:36 by djeanna           #+#    #+#             */
/*   Updated: 2019/06/27 16:21:08 by djeanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lem_in.h"

t_lis		*ft_lis_new(char *name, int i)
{
	t_lis	*new;

	if (!(new = ft_memalloc(sizeof(t_lis))))
		return (NULL);
	new->i = i;
	new->name = name;
	new->next = NULL;
	new->x = 1000000;
	new->y = 1000000;
	return (new);
}

int			ft_lis_pushback(t_lis **beg, t_lis *new)
{
	t_lis *tmp;

	if (!*beg)
		*beg = new;
	else
	{
		tmp = (*beg)->next;
		(*beg)->next = new;
		new->next = tmp;
	}
	return (1);
}

t_lis		*ft_lis_copy(t_lis *src)
{
	return (ft_lis_new(src->name, src->i));
}

void		ft_lis_del(t_lis **beg)
{
	if (beg && *beg)
	{
		ft_lis_del(&((*beg)->next));
		ft_memdel((void *)beg);
	}
}

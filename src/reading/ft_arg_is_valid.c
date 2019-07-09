/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_is_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeanna <djeanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 10:08:12 by djeanna           #+#    #+#             */
/*   Updated: 2019/06/27 16:21:08 by djeanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lem_in.h"

char		*ft_find_start(t_hasht *h, char *str)
{
	if (*(str - 1) == '#' && *(str - 2) == '#' && !ft_strcmp_line(str, "start"))
	{
		if (h->start.name)
			return (NULL);
		str = skip_until_slashn(str);
		str = ft_skip_something(str);
		if (!str || ft_strchr_line(str, '-') || *str == 'L' || *str == '#')
			return (NULL);
		h->start.name = ft_strcut(str, ' ');
		str = ft_skip_until_whitespaces(str);
		str = ft_skip_whitespaces(str);
		if (!(str = ft_skip_dig(str)))
			return (NULL);
		if (!(str = ft_skip_dig(str)))
			return (NULL);
		h->start.i = h->top + 1;
		ft_hasht_add(h, ft_lis_new(h->start.name, h->start.i));
		return (ft_skip_whitespaces(str));
	}
	return (str - 2);
}

char		*ft_find_end(t_hasht *h, char *str)
{
	if (*(str - 1) == '#' && *(str - 2) == '#' && !ft_strcmp_line(str, "end"))
	{
		if (h->end.name)
			return (NULL);
		str = skip_until_slashn(str);
		str = ft_skip_something(str);
		if (ft_strchr_line(str, '-') || *str == 'L' || *str == '#')
			return (NULL);
		h->end.name = ft_strcut(str, ' ');
		str = ft_skip_until_whitespaces(str);
		str = ft_skip_whitespaces(str);
		if (!(str = ft_skip_dig(str)))
			return (NULL);
		if (!(str = ft_skip_dig(str)))
			return (NULL);
		h->end.i = h->top + 1;
		ft_hasht_add(h, ft_lis_new(h->end.name, h->end.i));
		return (ft_skip_whitespaces(str));
	}
	return (str - 2);
}

char		*ft_get_ants(char *str, int *num_a)
{
	if (!(str = ft_comments(str, num_a)))
		return (NULL);
	str = ft_skip_whitespaces(str);
	*num_a = ft_atoi(str);
	while (*str && *str != '\n')
	{
		if (!ft_isdigit(*str))
			break ;
		str++;
	}
	str = ft_skip_whitespaces(str);
	if (*str && *str != '\n' && !ft_isdigit(*str))
		*num_a = 0;
	if (!*str)
		return (str);
	return (str + 1);
}

char		*ft_add_rooms2(t_hasht *h, char *str)
{
	str = ft_skip_whitespaces(str);
	ft_hasht_add(h, ft_lis_new(ft_strcut(str, ' '), h->top + 1));
	str = ft_skip_until_whitespaces(str);
	str = ft_skip_whitespaces(str);
	if (!(str = ft_skip_dig(str)))
		return (NULL);
	if (!(str = ft_skip_dig(str)))
		return (NULL);
	return (str);
}

int			ft_is_data_valid(t_hasht *h, char *str)
{
	if (!str)
		return (0);
	str = str;
	str = ft_get_ants(str, &(h->num_a));
	if (h->num_a <= 0 || !*str)
		return (0);
	if (!(str = ft_add_rooms(h, str)))
		return (0);
	while (*str)
	{
		if (*str == '#')
		{
			if (!(str = ft_help(str)))
				return (0);
		}
		else
		{
			if (!(str = ft_help2(str, h)))
				return (0);
		}
	}
	return (1);
}

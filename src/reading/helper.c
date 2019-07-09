/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeanna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 21:54:38 by djeanna           #+#    #+#             */
/*   Updated: 2019/07/01 21:54:40 by djeanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lem_in.h"

char		*ft_help(char *str)
{
	if (*(str + 1) != '#')
		str = skip_until_slashn(str);
	else
	{
		if (!ft_strcmp_line(str + 2, "end") ||
			!ft_strcmp_line(str + 2, "start"))
			return (0);
		else
			str = skip_until_slashn(str);
	}
	if (*(str - 1) != '\n')
		return (0);
	return (str);
}

char		*ft_help2(char *str, t_hasht *h)
{
	t_lis *tmp;
	t_lis *tmp2;

	str = ft_skip_whitespaces(str);
	if (ft_strchr_line(str, ' ') || !ft_strchr_line(str, '-'))
		return (0);
	if (!(tmp = ft_hasht_search(h, str, '-')))
		return (0);
	str = ft_skip_until_tire(str);
	if (!(tmp2 = ft_hasht_search(h, str, '\n')))
		return (0);
	str = skip_until_slashn(str);
	if (*(str - 1) != '\n')
		return (0);
	ft_lis_pushback(&tmp, ft_lis_copy(tmp2));
	ft_lis_pushback(&tmp2, ft_lis_copy(tmp));
	return (str);
}

char		*ft_add_rooms(t_hasht *h, char *str)
{
	while (*str)
	{
		if (*str == '#')
		{
			if (*(str + 1) != '#')
			{
				str = skip_until_slashn(str);
				continue ;
			}
			if (!(str = ft_find_start(h, str + 2)))
				return (0);
			if (!(str = ft_find_end(h, str + 2)))
				return (0);
		}
		else
		{
			if (ft_strchr_line(str, '-'))
				return (str);
			if (*str == 'L' ||
			ft_hasht_search(h, str, ' ') || !(str = ft_add_rooms2(h, str)))
				return (NULL);
		}
		*str ? str++ : NULL;
	}
	return (str);
}

char		*ft_comments(char *str, int *num_a)
{
	while (!ft_isdigit(*str))
	{
		if (*str == '#')
		{
			if (*(str + 1) != '#')
			{
				str = skip_until_slashn(str);
				continue;
			}
			if (!ft_strcmp_line(str + 2, "start") ||
				!ft_strcmp_line(str + 2, "end"))
			{
				*num_a = 0;
				return (NULL);
			}
			str = skip_until_slashn(str);
		}
		else
		{
			*num_a = 0;
			return (NULL);
		}
	}
	return (str);
}

char		*ft_skip_something(char *str)
{
	while (*str)
	{
		if (*str == '#' && *(str + 1) != '#')
			str = skip_until_slashn(str);
		else if (*str == '#' && *(str + 1) == '#')
			return (NULL);
		else
			return (str);
	}
	str = ft_skip_whitespaces(str);
	return (str);
}

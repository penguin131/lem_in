/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeanna <djeanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 11:51:28 by smight            #+#    #+#             */
/*   Updated: 2019/07/01 11:21:48 by djeanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static int	flags(int c, char **v, int *check, int *fd)
{
	if (c > 1 && !ft_strcmp("-v", v[1]))
	{
		v++;
		c--;
		*check = 1;
	}
	else if (c > 1 && !ft_strcmp("-f", v[1]))
	{
		if ((*fd = open(v[2], O_RDONLY)) < 0 || read(*fd, NULL, 0) == -1)
			return (write(1, "Error\n", 6));
		c -= 2;
		v += 2;
	}
	if (c > 1 && !ft_strcmp("-v", v[1]))
		*check = 1;
	else if (c > 1 && !ft_strcmp("-f", v[1]))
	{
		if ((*fd = open(v[1], O_RDONLY)) < 0 || read(*fd, NULL, 0) == -1)
			return (write(1, "Error\n", 6));
	}
	return (0);
}

static int	end_after_solver(int check, char **str, t_hasht *h)
{
	check ? 0 : write(1, *str, ft_strlen(*str));
	ft_strdel(str);
	ft_hash_del(h);
	return (write(1, "Error\n", 6));
}

static int	where_will_it_end(int check, char **str, t_hasht *h)
{
	!check ? write(1, *str, ft_strlen(*str)) : 0;
	ft_strdel(str);
	ft_hash_del(h);
	return (write(1, "Error\n", 6));
}

static int	cause_we_can(int check, char **str, t_hasht *h)
{
	write(1, *str, ft_strlen(*str));
	print_result(h->result, h, check);
	ft_strdel(str);
	ft_hash_del(h);
	return (0);
}

int			main(int c, char **v)
{
	int			fd;
	int			check;
	t_hasht		h;
	char		*str;

	fd = 0;
	check = 0;
	if (flags(c, v, &check, &fd))
		return (-1);
	ft_hasht_new(&h);
	if (!(str = ft_read(&h, fd, check)))
	{
		ft_hash_del(&h);
		return (write(1, "Error\n", 6));
	}
	if (!(h.start.name) || (!h.end.name))
		return (where_will_it_end(check, &str, &h));
	fd ? close(fd) : 0;
	zero_htable(&h, ROOT);
	reverse_links_upgrade(&h);
	if (!solver(&h))
		return (end_after_solver(check, &str, &h));
	return (cause_we_can(check, &str, &h));
}

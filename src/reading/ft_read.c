/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeanna <djeanna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 10:06:39 by djeanna           #+#    #+#             */
/*   Updated: 2019/06/27 16:21:08 by djeanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lem_in.h"

char		*ft_read(t_hasht *h, int fd, int check)
{
	char *buf;
	char *str;
	char *tmp;

	if (!(buf = ft_strnew(100000)))
		return (NULL);
	str = NULL;
	while (read(fd, buf, 100000))
	{
		tmp = str;
		str = ft_strjoin(str, buf);
		tmp ? ft_strdel(&tmp) : NULL;
		ft_bzero(buf, 100000);
	}
	ft_strdel(&buf);
	h->start.name = NULL;
	h->end.name = NULL;
	if (!ft_is_data_valid(h, str))
	{
		!check ? write(1, str, ft_strlen(str)) : 0;
		str ? ft_strdel(&str) : NULL;
		return (NULL);
	}
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeanna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 12:39:40 by djeanna           #+#    #+#             */
/*   Updated: 2019/06/21 12:39:41 by djeanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lem_in.h"

char	*ft_strchr_line(const char *s, int c)
{
	char *temp;

	temp = (char*)s;
	while (*temp && *temp != '\n')
	{
		if (*temp == (unsigned char)c)
			return (temp);
		temp++;
	}
	return (*temp == (unsigned char)c ? temp : NULL);
}

int		ft_strcmp_line(char *str1, char *str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 != *str2)
		{
			return ((*str1 == '\0' ? 0 : (int)*str1) -
					(*str2 == '\0' ? 0 : (int)*str2));
		}
		str1++;
		str2++;
	}
	if (!*str2 && *str1 == '\n')
		return (0);
	return (1);
}

int		ft_strcmp_edge_line(char *str1, char *str2, char c)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 != *str2)
		{
			return ((*str1 == '\0' ? 0 : (int)*str1) -
					(*str2 == '\0' ? 0 : (int)*str2));
		}
		str1++;
		str2++;
	}
	if (!*str2 && *str1 == c)
		return (0);
	return (1);
}

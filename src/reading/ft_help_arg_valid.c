/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help_arg_valid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djeanna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 10:12:50 by djeanna           #+#    #+#             */
/*   Updated: 2019/06/21 10:12:51 by djeanna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lem_in.h"

char	*skip_until_slashn(char *str)
{
	while (*str && *str != '\n')
		str++;
	if (*str == '\n')
		str++;
	return (str);
}

char	*ft_skip_whitespaces(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

char	*ft_skip_until_whitespaces(char *str)
{
	while (*str && *str != ' ')
		str++;
	return (str);
}

char	*ft_skip_dig(char *str)
{
	str = ft_skip_whitespaces(str);
	if (*str == '-' || *str == '+')
		str++;
	while (*str && ft_isdigit(*str))
		str++;
	if (*str && *str != ' ' && *str != '\t' && *str != '\n')
		return (NULL);
	str = ft_skip_whitespaces(str);
	return (str);
}

char	*ft_skip_until_tire(char *str)
{
	while (*str && *str != '-')
		str++;
	if (!*str)
		return (str);
	return (str + 1);
}

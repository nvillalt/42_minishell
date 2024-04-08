/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:06:48 by nvillalt          #+#    #+#             */
/*   Updated: 2023/12/26 19:37:59 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*s1copy;
	unsigned char	*s2copy;

	i = 0;
	s1copy = (unsigned char *)s1;
	s2copy = (unsigned char *)s2;
	while (s2copy[i] != '\0')
	{
		if (s1copy[i] != s2copy[i])
			return (s1copy[i] - s2copy[i]);
		i++;
	}
	return (s1copy[i] - s2copy[i]);
}

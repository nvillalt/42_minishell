/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:08:22 by nvillalt          #+#    #+#             */
/*   Updated: 2023/12/26 19:24:02 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1copy;
	unsigned char	*s2copy;

	i = 0;
	s1copy = (unsigned char *)s1;
	s2copy = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while ((s1copy[i] != '\0') && (i != n - 1))
	{
		if (s1copy[i] != s2copy[i])
			return (s1copy[i] - s2copy[i]);
		i++;
	}
	return (s1copy[i] - s2copy[i]);
}

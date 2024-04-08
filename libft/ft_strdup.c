/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:06:48 by nvillalt          #+#    #+#             */
/*   Updated: 2023/11/24 14:39:13 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*s;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(src);
	s = ft_calloc(sizeof(char), len + 1);
	if (!s)
		return (0);
	while (src[i] != '\0')
	{
		s[i] = (char)src[i];
		i++;
	}
	return (s);
}

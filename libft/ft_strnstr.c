/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:18:37 by nvillalt          #+#    #+#             */
/*   Updated: 2023/10/06 13:22:13 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	if (*haystack == 0 || ft_strlen(needle) > n)
		return (0);
	while ((char)haystack[i] != '\0')
	{
		j = 0;
		while ((char)haystack[i + j] == (char)needle[j] && (i + j) < n)
		{
			if ((char)haystack[i + j] == '\0' && (char)needle[j] == '\0')
				return ((char *)haystack + i);
			j++;
		}
		if ((char)needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (0);
}

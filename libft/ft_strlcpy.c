/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:07:46 by nvillalt          #+#    #+#             */
/*   Updated: 2023/10/06 13:21:23 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	count;
	char	*copy;

	i = 0;
	count = ft_strlen(src);
	copy = (char *)src;
	if (n == 0)
		return (count);
	while (copy[i] != '\0' && i < (n - 1))
	{
		dst[i] = copy[i];
		i++;
	}
	dst[i] = '\0';
	return (count);
}

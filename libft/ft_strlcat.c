/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:07:35 by nvillalt          #+#    #+#             */
/*   Updated: 2023/10/06 13:21:16 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstsize;
	size_t	srcsize;
	size_t	i;

	dstsize = ft_strlen(dst);
	srcsize = ft_strlen(src);
	i = 0;
	if (dst == 0 && size == 0)
		return (size + srcsize);
	if (size > dstsize)
	{
		while (*src != 0 && i < (size - dstsize - 1))
		{
			dst[dstsize + i] = *src;
			src++;
			i++;
		}
		dst[dstsize + i] = 0;
		return (dstsize + srcsize);
	}
	else
		return (size + srcsize);
}

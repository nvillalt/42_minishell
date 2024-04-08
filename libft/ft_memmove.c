/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:04:54 by nvillalt          #+#    #+#             */
/*   Updated: 2023/10/06 13:17:25 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*srccopy;
	unsigned char	*destcopy;

	srccopy = (unsigned char *)src;
	destcopy = (unsigned char *)dest;
	i = 0;
	if (srccopy == 0 && destcopy == 0)
		return ("");
	if (dest > src)
	{
		while (n-- != 0)
			destcopy[n] = srccopy[n];
	}
	else
	{
		while (i < n)
		{
			destcopy[i] = srccopy[i];
			i++;
		}
	}
	return (dest);
}

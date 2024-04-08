/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:08:35 by nvillalt          #+#    #+#             */
/*   Updated: 2023/10/06 13:22:21 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int				len;
	unsigned char	*copy;

	copy = (unsigned char *)str;
	len = ft_strlen(str);
	while (len >= 0)
	{
		if (copy[len] == (unsigned char)c)
			return ((char *)copy + len);
		len--;
	}
	return (0);
}

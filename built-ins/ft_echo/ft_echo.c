/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:35:19 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/04/08 14:34:11 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

static void c

static void	ft_echo(char **str)
{
	int	i;
	int	n_flag;
	int	argc;

	i = 1;
	n_flag = 1;
	if (ft_strncmp(str[i], "-n", 2) == 0 && ft_strlen(str[i]) == 2)
	{
		i++;
		n_flag = 0;
	}
	while(str[i])
	{
		printf("%s ", str[i]);
		i++;
	}
	if (n_flag != 0)
		printf("\n");
}

int main(int argc, char **argv)
{
	ft_echo(argv);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:08:07 by nvillalt          #+#    #+#             */
/*   Updated: 2024/05/13 20:05:04 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	quotes_len(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while(str[i])
	{
		if ((str[i] == 34 || str[i] == 39) && !flag)
		{
			flag = str[i];
			if (str[i + 1])
				i++;
		}
		else if (str[i] == flag && flag)
			break ;
		i++;
	}
	return (i);
}

static char	*erase_quotes(char *str, char c)
{
	int	len;

	len = quotes_len(str);
	printf("Longitud entre comillas - %d.\n", len);
}

char	*clean_quotes(char	*str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			erase_quotes(str, str[i]);
		i++;
	}
	if (ret == NULL)
		ret = ft_strdup(str);
	printf("---> Sin comillas: %s.\n", ret);
	return (ret);
}

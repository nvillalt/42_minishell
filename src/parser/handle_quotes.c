/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:08:07 by nvillalt          #+#    #+#             */
/*   Updated: 2024/05/26 20:08:32 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char *erase_quotes(char *str, int num)
{
	char	*final;
	int		flag;
	int		i;
	int		j;

	final = ft_calloc(sizeof(char), num + 1);
	if (!final)
		return (NULL);
	i = 0;
	flag = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34 && str[i + 1] == 34
			|| str[i] == 39 && str[i + 1] == 39)
			i += 2;
		if (str[i] == 34 || str[i] == 39 && !flag)
		{
			flag = str[i];
			i++;
			while (str[i] != flag && str[i])
			{
				final[j] = str[i];
				i++;
				j++;
			}
			flag = 0;
		}
		if (!flag && (str[i] != 34 && str[i] != 39))
		{
			final[j] = str[i];
			j++;
		}
		i++;
	}
	return (final);
}

char	*clean_quotes(char	*str)
{
	int		i;
	int		flag;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	flag = 0;
	if (str[0] == 34 && str[1] == 34 && str[2] == '\0'
		|| str[0] == 39 && str[1] == 39 && str[2] == '\0')
		return (ft_strdup(""));
	while (str[i])
	{
		if ((str[i] == 34 || str[i] == 39) && !flag)
		{
			flag = str[i];
			j++;
		}
		else if (str[i] == flag)
		{
			j++;
			flag = 0;
		}
		i++;
	}
	ret = erase_quotes(str, i - j);
	return (ret);
}

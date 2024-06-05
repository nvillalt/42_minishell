/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:08:07 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/05 20:17:49 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*erase_quotes(char *s, int num)
{
	char	*final;
	int		flag;
	int		i;
	int		j;

	i = 0;
	j = 0;
	final = init_quoteless_line(num);
	while (s[i] != '\0')
	{
		flag = 0;
		while ((s[i] == 34 && s[i + 1] == 34) || (s[i] == 39 && s[i + 1] == 39))
			i += 2;
		if (s[i] == 34 || s[i] == 39)
		{
			flag = s[i++];
			while (s[i] != flag && s[i])
				final[j++] = s[i++];
		}
		else if (s[i] != 34 && s[i] != 39)
			final[j++] = s[i];
		if (s[i] != '\0')
			i++;
	}
	return (final);
}

char	*clean_quotes(char	*str)
{
	int		i;
	int		flag;
	int		j;

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
	return (erase_quotes(str, i - j));
}

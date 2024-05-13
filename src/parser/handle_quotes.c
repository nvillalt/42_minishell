/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:08:07 by nvillalt          #+#    #+#             */
/*   Updated: 2024/05/13 23:48:07 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	quotes_len(char *str)
{
	int	i;
	int	flag;
	int	counter;

	i = 0;
	flag = 0;
	counter = 0;
	while(str[i])
	{
		if ((str[i] == 34 || str[i] == 39) && !flag)
		{
			flag = str[i];
			i++;
			while (str[i] != flag)
			{
				counter++;
				i++;
			}
		}
		else if (str[i] == flag && flag)
			break ;
		i++;
	}
	return (counter);
}

static int erase_quotes(char *str, char c, char **temp, int i)
{
	int	len;

	len = quotes_len(str);
	printf("Longitud entre comillas - %d.\ni: %d\n", len, i);
	*temp = ft_substr(str, i + 1, len);
	i += len + 1;
	printf("TEMP: %s\n.. %d\n", *temp, i);
}

static char	*append_temp(char *ret, char *temp)
{
	char	*final;

	final = NULL;
	if (ret == NULL)
	{
		final = strdup(temp);
		free(temp);
	}
	else if (ret != NULL)
	{
		final = ft_strjoin(ret, temp);
		free(ret);
		free(temp);
	}
	return (final);
}

char	*clean_quotes(char	*str)
{
	int		i;
	int		count;
	int		flag;
	char	*ret;
	char	*temp;

	i = 0;
	flag = 0;
	count = 0;
	temp = NULL;
	ret = NULL;
	while (str[i])
	{
		if ((str[i] == 34 || str[i] == 39) && !flag)
			erase_quotes(str, str[i], &temp, i);
		else if (str[i] == flag)
			flag = 0;
		while (!flag && str[i++])
			count++;
		if (temp == NULL)
			ret = ft_substr(str, i, count);
		ret = append_temp(ret, temp);
	}
	printf("---> Sin comillas: %s.\n", ret);
	return (ret);
}

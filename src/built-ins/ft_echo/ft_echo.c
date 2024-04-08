/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:35:19 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/04/08 16:04:45 by fmoran-m         ###   ########.fr       */
/*                                                                            */

#include "../libft/libft.h"
#include <stdio.h>

static int	count_argc(char **str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return(i);
}

static int	control_n(char **str, int i, int *n_flag)
{
	int	j;
	
	j = 2;
	while (str[i] && ft_strncmp(str[i], "-n", 2) == 0)
	{
		while(str[i][j] && str[i][j] == 'n')
			j++;
		if(str[i][j])
			break ;
		else
		{
			*n_flag = 0;
			i++;
		}
	}
	return (i);
}

static void	ft_echo(char **str)
{
	int	i;
	int	n_flag;
	int	argc;

	i = 1;
	n_flag = 1;
	if (str[1] == NULL)
	{
		printf("\n");
		return;
	}
	argc = count_argc(str);
	i = control_n(str, i, &n_flag);
	while(i < argc - 1)
	{
		printf("%s ", str[i]);
		i++;
	}
	if (str[i])
		printf("%s", str[i]);
	if (n_flag != 0)
		printf("\n");
}

int main(int argc, char **argv)
{
	ft_echo(argv);
	return (0);
}

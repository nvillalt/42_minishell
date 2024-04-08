/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:35:19 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/04/08 16:04:45 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

static int	count_argc(char **str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return(i);
}

static void	ft_echo(char **str)
{
	int	i;
	int	n_flag;
	int	argc;

	i = 1;
	n_flag = 1;
	argc = count_argc(str);
	if (ft_strncmp(str[i], "-n", 2) == 0 && ft_strlen(str[i]) == 2)
	{
		i++;
		n_flag = 0;
	}
	while(i < argc - 1)
	{
		printf("%s ", str[i]);
		i++;
	}
	printf("%s", str[i]);
	if (n_flag != 0)
		printf("\n");
}

int main(int argc, char **argv)
{
	ft_echo(argv);
	return (0);
}

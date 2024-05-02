




#include "../../minishell.h"

static char	*append_second_half(char *str)
{
	int		i;
	int		len;
	char	*aux;
	char	*temp;

	aux = NULL;
	temp = NULL;
	i = 1;
	len = ft_strlen(str);
	while (str[len - 1] != 34)
		len--;
	while (str[i] != 34)
		i++;
	aux = ft_substr(str, 1, i);
//	temp = ft_substr(str, );

	printf("-----> %s\n", aux);
}

char	*erase_quotes(char *str)
{
	char	**pieces;
	char	*ret;
	char	*aux;
	int		i;

	i = -1;
	aux = NULL;
	ret = NULL;
	pieces = ft_split(str, 34);
	while (pieces[++i])
	{
		if (aux != NULL && pieces[i + 1] != NULL)
		{
			ret = ft_strjoin(aux, pieces[i + 1]);
			printf("¨¨ %s\n", ret);
			break ;
		}
		if (pieces[i] && pieces[i + 1] != NULL)
			aux = ft_strjoin(pieces[i], pieces[i + 1]);
		printf("***** %s %d\n", aux, i);
	}
	if (ret == NULL)
		ret = ft_strdup(aux);
	free(aux);
	free_matrix(pieces);
	printf("!!!! %s\n", ret);
	return (ret);
}

static char	*clean_double_quotes(char *str)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	len = ft_strlen(str);
	if (str[0] == 34 && str[1] == 34 && str[2] == '\0')
		return (ft_strdup(""));
	else if (str[0] == 34 && str[len - 1] == 34)
		return (ft_substr(str, i + 1, len - 2));
	else if (str[0] == 34 && str[1] == 34 && str[2] != 34)
		return (ft_substr(str, i + 2, len - 1));
	ret = erase_quotes(str);
	return (ret);
}

char	*clean_quotes(char	*str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (str[i])
	{
		if (str[i] == 34)
		{
			ret = clean_double_quotes(str);
			break ;
		}
		// else if (str[i] == 39)
		// {
		// 	ret = clean_single_quotes(str);
		// 	break ;
		// }
		i++;
	}
	if (ret == NULL) // Proteger esto con !ret tambien????
		ret = ft_strdup(str);
	return (ret);
}
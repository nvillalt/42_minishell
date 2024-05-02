




#include "../../minishell.h"


static char	*erase_quotes(char *str, char c)
{
	char	**pieces;
	char	*ret;
	char	*aux;
	int		i;

	i = 0;
	aux = NULL;
	ret = NULL;
	pieces = ft_split(str, c);
	ret = ft_strdup(pieces[i]);
	while (pieces[++i])
	{
		aux = ft_strjoin(ret, pieces[i]);
		free(ret);
		ret = ft_strdup(aux);
		free(aux);
	}
	free_matrix(pieces);
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
	else if (str[len - 1] == 34 && str[len - 2] == 34)
		return (ft_substr(str, i, len - 2));
	ret = erase_quotes(str, 34);
	return (ret);
}

static char *clean_single_quotes(char *str)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	len = ft_strlen(str);
	if (str[0] == 39 && str[1] == 39 && str[2] == '\0')
		return (ft_strdup(""));
	else if (str[0] == 39 && str[len - 1] == 39)
		return (ft_substr(str, i + 1, len - 2));
	else if (str[0] == 39 && str[1] == 39 && str[2] != 39)
		return (ft_substr(str, i + 2, len - 1));
	else if (str[len - 1] == 39 && str[len - 2] == 39)
		return (ft_substr(str, i, len - 2));
	ret = erase_quotes(str, 39);
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
		else if (str[i] == 39)
		{
			ret = clean_single_quotes(str);
			break ;
		}
		i++;
	}
	if (ret == NULL) // Proteger esto con !ret tambien????
		ret = ft_strdup(str);
	return (ret);
}
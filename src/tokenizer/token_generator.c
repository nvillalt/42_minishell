
#include "../../minishell.h"

char	*trim_spaces(char *input)
{
	char	*str;
	int		i;
	int		len;

	i = whitespace_cmp(input);
	len = ft_strlen(input);
	if (*input == '\0')
		return (NULL);
	if (i == len)
		return (NULL);
	while (is_whitespace(input[len - 1]))
		len--;
	str = ft_substr(input, i, len - i);
	return (str);
}
static int	check_symbol(char *str)
{
	int	i;

	i = 0;
	while (str[i]) //TODO: REVISAR CON FRAN LOS ERRORES
	{
		if (check_redirections(str) == 2 || check_redirections(str) == 8)
		{
			ft_putendl_fd("syntax error near unexpected token `>'", 2);
			return (-1);
		}
		else if (check_redirections(str) == 9 || check_redirections(str) == 4)
		{
			ft_putendl_fd("syntax error near unexpected token `newline'", 2);
			return (-1);
		}
		else if (check_redirections(str) == 6)
		{
			ft_putendl_fd("syntax error near unexpected token `|'", 2);
			return (-1);
		}
		i++;
	}
	return (1);
}

static int	check_expand(char *temp)
{
	if (((temp[0] == '$' && temp[1] == ' '))
		|| (temp[0] == '$' && temp[1] == '\0')
		|| (temp[0] == '$' && temp[1] == '='))
	{
		ft_putendl_fd("command not found: $", 2);
		return (-1);
	}
	return (1);
}

static int	get_quote_subs(char *aux, int i)
{
	printf("Entras?\n");
	printf("----- Cantidad en i: %s\n", i);
	int	flag;

	flag = 0;
	while (aux[i])
	{
		if (aux[i] == 39 || aux[i] == 34)
			flag = aux[i];
		else if (aux[i] == flag)
			break ;
		i++;
	}
	return (i);
}

static int	get_redir_substr(char *aux, int i)
{
	while (aux[i])
	{
		if (check_symbol(aux) == -1)
			return (-1);
		else if (is_token(aux[0]) && !is_token(aux[1]))
			return (1);
		else if (is_token(aux[0]) && is_token(aux[1]))
			return (2);
		i++;
	}
	return (i);
}
static int	get_substr(char *aux, int i)
{
	int	num;

	num = i;
	printf("..Cantidad en i: %d\n", num);
	while (aux[i])
	{
		if (aux[i] == 39 || aux[i] == 34)
		{
			num = get_quote_subs(aux, num);
			return (i + num);
		}
		else if (is_token(aux[i]))
		{
			if (get_redir_substr == -1)
				return (-1);
			return (i + get_redir_substr(aux, i));
		}
		if (is_whitespace(aux[i]))
			break ;
		i++;
	}
	return (i);
}

// static int	get_substr(char *aux, int i)
// {
// 	int	flag;

// 	flag = 0;
// 	while (aux[i])
// 	{
// 		// Pasar esto a una única función que reciba un str e i
// 		if (!ft_strncmp(aux + i, "echo", 4))
// 			return (i + 4);
// 		if ((aux[i] == 34 && aux[i + 1] == 34)
// 			|| (aux[i + 1] == 39 && aux[i + 1] == 39)
// 			&& !ft_strncmp(aux + 2, "echo", 4))
// 			return (i + 2);
// 		if ((aux[i] == '<' && aux[i + 1] == '<' && !flag)
// 			|| (aux[i] == '>' && aux[i + 1] == '>' && !flag))
// 			return (i + 2);
// 		else if (!flag && is_token(aux[i]))
// 			return (i + 1);
// 		if ((aux[i] == 34 || aux[i] == 39) && flag == 0)
// 			flag = aux[i];
// 		else if (aux[i] == flag)
// 			flag = 0;
// 		if ((is_whitespace(aux[i]) && !flag))
// 			break ;
// 		if ((!flag && is_token(aux[i + 1])))
// 			return (i + 1);
// 		i++;
// 	}
// 	return (i);
// }

//"cat"<Makefile|wc
int	get_tokens(char	*aux, t_utils *utils)
{
	t_token	*token;
	char	*temp;
	int		i;
	int		j;

	token = NULL;
	j = 0;
	if (aux == NULL)
		return (0);
	i = 0;
	while (aux[i])
	{
		j = get_substr(aux, i);
		if ((!new_token(&token) && utils->token_list != NULL) || j == -1)
			return (clear_token_list(&utils->token_list));
		temp = ft_substr(aux, i, (j - i));
		printf("TEMP: %s\n\n", temp);
		if (check_symbol(temp) == 1 && check_expand(temp) == 1)
			token->str = temp;
		if (!add_token(&utils->token_list, token) || token->str == NULL)
			return (free_tokens(&utils->token_list, temp, 1));
		while (is_whitespace(aux[j]))
			j++;
		i = j;
	}
	t_token *print = utils->token_list;
	while(print->next != NULL)
	{
		printf("En nodo: %s\n", print->str);
		print = print->next;
	}
	printf("En nodo: %s\n", print->str);
	return (0);
}

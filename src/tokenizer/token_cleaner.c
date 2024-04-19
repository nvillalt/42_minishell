

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
	while (is_whitespace(input[len - 1]))
		len--;
	str = ft_substr(input, i, len - i + 1);
	return(str);
}
char	*remove_quotes(char *process)
{
	int		i;
	int		flag;
	char	*aux;

	i = 0;
	aux = trim_spaces(process);
	printf("%s\n", aux);

}
// "    " | pinga | "" | holaaa CHECAR CON ESTO

void	clean_tokens(t_utils *utils, char *aux)
{
	t_token	*token_list; // Contenido entre pipes
	char	**process;
	char	*tmp;
	int		i;

	i = 0;
	process = ft_split(aux, '|');
	free(aux);
	while (process[i])
	{
		tmp = remove_quotes(process[i]);
		i++;
	}
	free_matrix(process);
}

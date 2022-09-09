#include "minishell.h"
#include "libft/libft.h"

//removed quotes from the **arg
//i and j must be -1, k must be 0
//called by lexer
char    **rm_quote(char **arg, int i, int j, int k)
{
    char    *new;
    char    c;

    while (arg[++i] != NULL)
    {
        k = 0;
        j = -1;
        if (arg[i][0] != '\'' && arg[i][0] != '\"')
            continue ;
        c = arg[i][0];
        new = (char *)malloc(sizeof(char) * (ft_strlen(arg[i]) - 2));
        while (arg[i][++j] != '\0')
        {
            if (arg[i][j] == c)
                continue ;
            new[k] = arg[i][j];
            k++;
        }
        new[k] = '\0';
        free(arg[i]);
        arg[i] = ft_strdup(new);
        free(new);
        new = NULL; 
    }
    return(arg);
}

//removes whitespace in a string
//c and k must be 0, i must be -1
//called by main 
char	*rm_whitespace(char *s, char c, int k, int i)
{
	char *new;

	new = (char *)ft_calloc(ft_strlen(s), sizeof(char));
	while (s[++i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (c == 0)
				c = s[i];
			else
				c = 0;
		}
		if (c == 0 && s[i] == ' ')
		{
			while (s[++i] && s[i] == ' ');
			if (s[i] == '\0')
				break ;
			i--;
		}
		new[k] = s[i];
		k++;
	}
	new[k] = '\0';
	free(s);
	return (new);
}
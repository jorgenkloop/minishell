/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnm-jaya <jnm-jaya@student.42kl.edu>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:21:18 by jnm-jaya          #+#    #+#             */
/*   Updated: 2022/10/26 16:21:22 by jnm-jaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

int	check_special(char *s)
{
	int	i;

	i = 0;
	if (s[0] < 65 || (s[0] > 90 && s[0] < 97) || s[0] > 122)
		return (-3);
	while (s[i] != '=' || s[i] != '\0')
	{
		if (s[i] == '=')
			break ;
		if (s[i] < 48 || (s[i] > 57 && s[i] < 65)
			|| (s[i] > 90 && s[i] < 97) || s[i] > 122)
			return (-3);
		i++;
	}
	return (0);
}

void	print_export(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
	{
		ft_putstr_fd(envp[i], 1);
		ft_putchar_fd('\n', 1);
	}
}

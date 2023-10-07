/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:08:49 by marvin            #+#    #+#             */
/*   Updated: 2023/10/07 13:08:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

int	ft_strlen_trimmed(char *string, char *set)
{
	int		len;
	char	*trimmed_string;

	if (string == NULL || set == NULL)
		return (0);
	trimmed_string = ft_strtrim(string, set);
	len = ft_strlen(trimmed_string);
	free(trimmed_string);
	return (len);
}

int	ft_strlen_free(char *string)
{
	int	len;

	if (string == NULL)
		return (0);
	len = ft_strlen(string);
	free(string);
	return (len);
}

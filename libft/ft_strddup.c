/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strddup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcalik <rcalik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:08:02 by mkardes           #+#    #+#             */
/*   Updated: 2023/07/29 17:11:04 by rcalik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

// cift poiterlı strdup
char	**ft_strddup(char **str)
{
	char	**s;
	int		i;

	i = 0;
	if (!str || !str[0])
		return (NULL);
	while (str[i])
		i++;
	s = (char **)malloc(sizeof(char *) * i + 1);
	s[i] = NULL;
	i--;
	while (i >= 0)
	{
		s[i] = ft_strdup(str[i]);
		i--;
	}
	return (s);
}

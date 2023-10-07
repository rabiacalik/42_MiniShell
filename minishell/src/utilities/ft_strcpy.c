/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:08:29 by marvin            #+#    #+#             */
/*   Updated: 2023/10/07 13:08:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	src_length;

	src_length = ft_strlen(src);
	while (*src != '\0' && 1 < n)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}
	if (n != 0)
		*dest = '\0';
	return (src_length);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

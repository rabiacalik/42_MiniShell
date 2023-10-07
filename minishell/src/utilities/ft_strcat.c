/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:08:08 by marvin            #+#    #+#             */
/*   Updated: 2023/10/07 13:08:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcat(char *dst, const char *src)
{
	int	dst_len;

	dst_len = ft_strlen(dst);
	ft_strcpy(dst + dst_len, src);
	return (dst);
}

void	ft_strcat_free(char *dst, char *src)
{
	if (src == NULL)
		return ;
	ft_strcpy(dst + ft_strlen(dst), src);
	free(src);
}

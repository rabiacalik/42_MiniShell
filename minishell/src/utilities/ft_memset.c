/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:06:59 by marvin            #+#    #+#             */
/*   Updated: 2023/10/07 13:07:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	void	*s_address;

	s_address = s;
	while (0 < n)
	{
		*(unsigned char *)s = (unsigned char)c;
		s++;
		n--;
	}
	return (s_address);
}

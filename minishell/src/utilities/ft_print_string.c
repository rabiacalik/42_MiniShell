/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:07:41 by marvin            #+#    #+#             */
/*   Updated: 2023/10/07 13:07:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_print_string(int fd, const char *string)
{
	int	i;

	i = 0;
	if (string == NULL)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	while (*string != '\0')
	{
		ft_print_char(fd, *string);
		string++;
		i++;
	}
	return (i);
}

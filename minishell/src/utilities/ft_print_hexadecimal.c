/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexadecimal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:07:19 by marvin            #+#    #+#             */
/*   Updated: 2023/10/07 13:07:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_hexadecimal_len(unsigned int number)
{
	int	len;

	len = 0;
	if (number == 0)
		return (1);
	while (number != 0)
	{
		number = number / 16;
		len++;
	}
	return (len);
}

int	ft_print_hexadecimal(int fd, unsigned int number, char token)
{
	int	len;

	len = ft_hexadecimal_len(number);
	if (number <= 9)
		ft_print_char(fd, number + '0');
	else if (number < 16)
	{
		if (token == 'x')
			ft_print_char(fd, (number - 10) + 'a');
		else
			ft_print_char(fd, (number - 10) + 'A');
	}
	else
	{
		ft_print_hexadecimal(fd, number / 16, token);
		ft_print_hexadecimal(fd, number % 16, token);
	}
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:10:08 by marvin            #+#    #+#             */
/*   Updated: 2023/10/07 13:10:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	word_counter(char *command)
{
	int	count;
	int	word_found;

	count = pipe_redirection_count(command);
	word_found = 0;
	while (*command != '\0')
	{
		if (ft_strchr("\"\'", *command))
		{
			count++;
			command = skip_quotes(command);
			word_found = 0;
			if (*command == '\0')
				return (count);
		}
		if (word_found == 0 && !ft_strchr("|<> \"\'", *command))
		{
			count++;
			word_found = 1;
		}
		else if (word_found == 1 && ft_strchr("|<> ", *command))
			word_found = 0;
		command++;
	}
	return (count);
}

char	**command_parser(char *command)
{
	char	**commands;
	int		index;

	commands = (char **)ft_calloc(word_counter(command) + 1, sizeof(char *));
	index = 0;
	while (*command != '\0')
	{
		commands[index] = command_separator(command);
		command = command + ft_strlen(commands[index]);
		while (*command == ' ')
			command++;
		index++;
	}
	commands[index] = NULL;
	return (commands);
}

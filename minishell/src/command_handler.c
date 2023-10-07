/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:09:44 by marvin            #+#    #+#             */
/*   Updated: 2023/10/07 13:09:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quotes_check(char *command)
{
	char	quote;
	int		quote_count;

	quote_count = 0;
	while (*command != '\0')
	{
		if (*command == '\'' || *command == '\"')
		{
			quote = *command;
			quote_count++;
			command++;
			while (*command != '\0' && *command != quote)
				command++;
			if (*command == quote)
				quote_count++;
		}
		if (*command != '\0')
			command++;
	}
	if (quote_count % 2 == 0)
		return (1);
	return (0);
}

void	command_handler(char *command)
{
	char	**parsed_commands;
	t_token	*token_list;

	if (quotes_check(command) == 0)
	{
		ft_printf(STDERR_FILENO,
			"minishell: syntax error near unexpected token\n");
		return ;
	}
	parsed_commands = command_parser(command);
	change_all_env_variable_to_value(parsed_commands);
	fill_token_list(parsed_commands, &token_list);
	set_token_type(token_list);
	execute_commands(token_list);
	clear_token_list(&token_list);
	clear_string_list(parsed_commands);
	g_shell->heredoc_count = 0;
}

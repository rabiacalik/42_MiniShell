/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:10:24 by marvin            #+#    #+#             */
/*   Updated: 2023/10/07 13:10:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_env_variable(t_env *env)
{
	free(env->name);
	free(env->value);
	free(env);
	env = NULL;
}

void	delete_env_variable(char *variable_name)
{
	t_env	*temp_env;
	t_env	*prev_env;

	temp_env = g_shell->env;
	prev_env = NULL;
	if (temp_env == NULL)
		return ;
	if (ft_strcmp(temp_env->name, variable_name) == 0)
	{
		g_shell->env = g_shell->env->next;
		clear_env_variable(temp_env);
		return ;
	}
	while (temp_env != NULL && ft_strcmp(temp_env->name, variable_name) != 0)
	{
		prev_env = temp_env;
		temp_env = temp_env->next;
	}
	if (temp_env == NULL)
		return ;
	prev_env->next = temp_env->next;
	clear_env_variable(temp_env);
}

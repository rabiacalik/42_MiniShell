/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcalik <rcalik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:21:43 by mkardes           #+#    #+#             */
/*   Updated: 2023/07/29 18:25:36 by rcalik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// tek ve cıft tırnak içlerini atlamamızı saglar
void	partition_func(char	*s, int *i, int tmp, int j) // j: max size
{
	if (s[*i] == '\"')
	{
		while (s[++(*i)] != '\"' && (*i) - tmp < j)
			;
		(*i)++;
	}
	else if (s[(*i)] == '\'')
	{
		while (s[(++(*i))] != '\'' && (*i) - tmp < j)
			;
		(*i)++;
	}
}

void	check_func(char *s, int i, int *a, int j)
{
	if (s[i + (*a)] == '\"')
	{
		(*a)++;
		while (s[i + (*a)] != '\"' && (*a) < j)
			(*a)++;
		(*a)++;
	}
	else
	{
		(*a)++;
		while (s[i + (*a)] != '\'' && (*a) < j)
			(*a)++;
		(*a)++;
	}
}

// This function passes the string until reach to the another \" or '

void	fix_var(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 96)
			s[i] = '$';
		i++;
	}
}

void	quotes_state(char *s, int i, int *j, char c)
{
	(*j)++;
	while (s[i + (*j)] != c && s[i + (*j)])
	{
		if (c == '\'' && s[i + (*j)] == '$')
			s[i + (*j)] = 96;
		(*j)++;
	}
}

void	pass(char *s, int *i, char c)
{
	(*i)++;
	while (s[*i] && s[*i] != c)
		(*i)++;
	(*i)++;
}

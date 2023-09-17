/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcalik <rcalik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:25:40 by mkardes           #+#    #+#             */
/*   Updated: 2023/07/29 16:59:44 by rcalik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
verilen string içerisinde "=" arar ve buldugunda , "=" den sonrasını
çift tırnak içerisine alarak geriye dondurur
*/
char	*declare_add_quotes(char *s)
{
	char	*tmp;
	int		i;

	if (ft_strchr(s, '=') == 0) //stiringde eşittir yoksa stringi dondurur
		return (s);
	tmp = ft_calloc(ft_strlen(s) + 3, 1); // ikişer iki tırnak ve null için +3 ekledik
	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			break ;
		tmp[i] = s[i]; // esittire kadar tmp ye attı
		i++;
	}
	tmp[i++] = '=';			//çift tırnak tanımında karışıklık olmasın diye "\" koyduk escape
	*(i + tmp++) = '\"';	//tmp nin adresini arttırıyoruz ki s nin ve tmp nin indexleri aynı char ı gostersin
	while (s[i])
	{
		tmp[i] = s[i];
		i++;
	}
	*(i + tmp++) = '\"';
	tmp[i] = '\0';
	free(s);
	return (tmp - 2); // tmp yi iki defa arttırdığımız için eksiltme yapıp duzelttik (adresi)
}

// declares struct degişkenine kopyalar ve siler. kopyalanmış olana yeni değişkeni ekler ve tekrar declares e eşitler
void	declare_add(char *s)
{
	char	**n_dec;
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (g_shell.declares && g_shell.declares[i])
		i++;
	n_dec = (char **)ft_calloc(sizeof(char *), (i + 2));
	j = -1;
	while (++j < i)
		n_dec[j] = g_shell.declares[j];
	str = ft_strdup(s); //neden str ye s yi kopyalıyorsun !!!!!
	n_dec[i] = declare_add_quotes(str); //stringin tırnaklı hali döndü
	if (g_shell.declares)
		free(g_shell.declares);
	g_shell.declares = n_dec;
	declare_sort();
}

// iki boyutlu dizide alfabetik sıralama yapıyor
void	declare_sort(void)
{
	int		len;
	int		i;
	int		j;
	char	*tmp;

	len = 0;
	while (g_shell.declares[len])
		len++;
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (ft_strncmp(g_shell.declares[j], g_shell.declares // neden strcmp değil !!!!!!!!
					[j + 1], 1000) > 0)
			{
				tmp = g_shell.declares[j];
				g_shell.declares[j] = g_shell.declares[j + 1];
				g_shell.declares[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

// bilgisayardaki env leri tırnaklayıp alfabetik sekilde sıralıyoruz
void	declare_init(void)
{
	int	i;

	i = 0;
	while (g_shell.env[i])
	{
		declare_add(g_shell.env[i]);
		i++;
	}
}

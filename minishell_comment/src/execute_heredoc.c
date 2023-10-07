/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spirnaz <spirnaz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:34:22 by spirnaz            #+#    #+#             */
/*   Updated: 2023/07/07 00:10:34 by spirnaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *delimiter)
{
	ft_printf(STDERR_FILENO,
		"\nbash: warning: here-document delimited by end-of-file (wanted `%s')\n",
		delimiter);
}

// hero document 👇
/*
	"Here document" (burada belgesi), bir programın standart girişine doğrudan bir metin bloğu sağlamak için 
	kullanılan bir bash kabuk özelliğidir. Bir komut satırında, bir komutun girişini elle belirlemek için 
	<< operatörü kullanılır.
*/
/*
	"temp_token" içerisindeki çevresel değişken ve tilda ifadelerini uygun değerlerle değiştirir
	temizlenmiş "temp_token"ı belirtilen dosya tanımlayıcısına(fd) yazarak "here document" içeriğini oluşturur
	geçici tokenları temizlemek için "clear_temp_token" fonksiyonu çağırılır
*/
static void	heredoc_handler_helper(int fd, char **temp_token, char *line)
{
	change_all_env_variable_to_value(temp_token);
	ft_printf(fd, "%s\n", temp_token[0]);
	clear_temp_token(temp_token, line);
}

/*
	dup2, bir dosya tanımlayıcısını başka bir dosya tanımlayıcısıyla aynı dosyaya yönlendirmek için kullanılır.
	int dup2(int oldfd, int newfd);
		oldfd: Yönlendirilecek olan dosya tanımlayıcısı.
		newfd: oldfd'nin yönlendirileceği dosya tanımlayıcısı.
*/

/*
	heredoc (<<) ifadesi varsa bir sondaki token a geçerek grep,cat,head gibi
	ifadeler var mı kontrol edilir eğer varsa dosya açılır ve standart giriş
	artık buradan yapılacağı belirtili
*/
static void	readable_for_heredoc(char *file_name, t_token *token)
{
	int		fd;
	t_token	*prev_token;

	prev_token = NULL;
	while (token != NULL && token->next != NULL
		&& ft_strncmp(token->next->value, "<<", 2))
	{
		prev_token = token;
		token = token->next;
	}
	if ((prev_token != NULL && ft_strncmp(prev_token->value, "grep", 5) == 0)
		|| ft_strncmp(token->value, "cat", 4) == 0
		|| ft_strncmp(token->value, "head", 5) == 0
		|| ft_strncmp(token->value, "tail", 5) == 0
		|| ft_strncmp(token->value, "sort", 5) == 0)
	{
		fd = open(file_name, O_RDONLY, 0644);
		if (fd == -1)
		{
			ft_printf(STDERR_FILENO, "File can't opened !\n");
			return ;
		}
		dup2(fd, STDIN_FILENO);//standart giriş dosyası
		close(fd);
	}
}

/*
	heredoc_handler("END", fd);
	Bu örnekte, END belirleyicisi ile sınırlı bir here document işlemi yapılır. Kullanıcıya >
	ifadesiyle bir girdi beklenir ve her girdi satırını heredoc_handler_helper fonksiyonu 
	aracılığıyla belirtilen dosyaya yazar. Kullanıcı END yazana kadar bu işlem devam eder.
*/

/*
	1- kullanıcıdan girdi satırını alır (get_next_line ile)
	2- girdi satırı belirtilen belirleyiciyle (delimiter) eşitse yada null ise döngüyü sonlandırır
	3- (heredoc_handler_helper) çevresel değişkenler değerlendirilir ve girdi belirtilen dosyaya yazılır
*/
static void	heredoc_handler(char *delimiter, int fd)
{
	char	*line;
	char	**temp_token;

	while (1)
	{
		temp_token = (char **)malloc(sizeof(char *) * 2);
		ft_printf(STDIN_FILENO, "> ");
		line = get_next_line(0);
		temp_token[0] = ft_strdup(line);
		temp_token[1] = NULL;
		if (line == NULL)
		{
			print_error(delimiter);
			clear_temp_token(temp_token, line);
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			clear_temp_token(temp_token, line);
			break ;
		}
		heredoc_handler_helper(fd, temp_token, line);
	}
	close(fd);
}

/*
	"here document" işlemi gerçekleştirir ve ardından bu belgenin içeriğini
	bir dosyaya yazarak bu dosyayı okunabilir hale getirir
*/
void	execute_heredoc(char *file_name, t_token *token, int *heredoc_count)
{
	int	fd;

	*heredoc_count += 1;

	// O_TRUNC dosyayı boş bir dosya olarak açar
	fd = open("bin/.heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_printf(STDERR_FILENO, "File can't opened !\n");
		g_shell->exit_status = 1;
		g_shell->file_error_found = 1;
		return ;
	}
	heredoc_handler(file_name, fd);
	readable_for_heredoc("bin/.heredoc_temp", token);
}

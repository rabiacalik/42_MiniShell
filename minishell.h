/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcalik <rcalik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:25:40 by mkardes           #+#    #+#             */
/*   Updated: 2023/07/29 16:05:45 by rcalik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <dirent.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

//p_cnt : Pipe counts
//in_pipe: The count of words in every pipes
//mpipe: *pipes[0] read   --   *pipes[1] write
//save_fd:
//heredoc_pipe:
typedef struct m_shell {
	void	*funcs;		//İşlevleri (fonksiyonları) içeren bir işlev işaretçisi (pointer). 
	char	**env;		// Ortam değişkenlerinin depolandığı bir karakter işaretçisi dizisi
	char	**declares; //Bildirimlerin (değişkenlerin tanımlandığı) depolandığı bir karakter işaretçisi dizisi (pointer array).
	char	***all;		//Komut, argüman ve çevresel değişkenleri içeren bir karakter işaretçisi dizisi (pointer array of pointer array of pointer). Bu, kabukta işlenen komutun tamamını temsil edebilir.
	char	*line;		//Kullanıcının girdiği komut satırını (input) içeren bir karakter işaretçisi (pointer).
	char	*prompt;	//Kabuğun bir komut girdisi beklerken gösterdiği işaretçiyi içeren bir karakter işaretçisi (pointer).
	int		p_cnt;		//Pipe (|) sayısını temsil eden bir tamsayı (integer).
	int		*in_pipe;	//(pipe) girişlerinin indekslerini içeren bir tamsayı işaretçisi (pointer).
	int		type;		//Komut tipini temsil eden bir tamsayı (integer). Örneğin, arka plan işlemi, giriş/yönlendirme işlemi gibi.
	int		p;			// Pipe sayısını temsil eden bir tamsayı (integer).
	int		**mpipe;	//Birden fazla boru hattının (pipe) işaretçilerini içeren bir tamsayı işaretçisi dizisi (pointer array of pointer).
	int		exit_status;// En son yürütülen ön plan işleminin çıkış durumunu (exit status) temsil eden bir tamsayı (integer).
	int		*save_fd;	//Dosya tanımlayıcılarının (file descriptor) değerlerini içeren bir tamsayı işaretçisi (pointer).
	int		*heredocpipe;//Here-Doc için boru hattı (pipe) girişlerinin indekslerini içeren bir tamsayı işaretçisi (pointer).
}	t_shell;

t_shell	g_shell;

void	partition(int p, int i, int j, int c);
void	check_fill(char *s, int i, int j, int p);
void	quotes_state(char *s, int i, int *j, char c);
void	split_pipe(char *s, int i);
void	pass(char *s, int *i, char c);
void	parsing(void);
void	myfree(void);
void	sig_int(int sig);
void	env(void);
void	my_export(void);
void	echo(void);
void	cd(void);
void	pwd(void);
void	start(int pid);
void	my_exit(void);
void	my_unset(void);
void	ft_error(char *command, char *msg);
int		operator_chc(void);
int		env_finder(char *str);
int		command_chc(void);
char	**command__chc(int p);
void	env_add(char *str);
void	check_quote_var(void);
void	check_func(char *s, int i, int *a, int j);
void	partition_func(char	*s, int *i, int tmp, int j);
void	redirections(void);
void	save_std_fds(void);
void	restore_std_fds(void);
void	heredoc(void);
int		heredoc_fill(void);
void	partition_func(char	*s, int *i, int tmp, int j);
void	check_func(char *s, int i, int *a, int j);
void	quotes_state(char *s, int i, int *j, char c);
void	pass(char *s, int *i, char c);
char	*cut_var(char *str);
char	*fill_it(char *str);
char	*get_varriable(char *str);
void	save_std_fds(void);
void	restore_std_fds(void);
void	writable(char *file_name, int flag);
void	readable(char *file_name);
int		my_free_2(char **s);
void	my_free_1(char **tmp, char **s, char **var);
void	open_pipes(void);
char	**arg_add(char **arg, char *str);
void	get_output(void);
int		check_if_exist(char **env, char *str, char *last);

void	fix_var(char *s);
void	declare_add(char *str);
void	declare_init(void);
void	declare_sort(void);
void	declare_env_add_check(char *s);
int		is_dec_exist(char *str, char *last);
char	*declare_add_quotes(char *s);

#endif

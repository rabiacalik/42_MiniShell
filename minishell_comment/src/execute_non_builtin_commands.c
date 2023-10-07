/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_non_builtin_commands.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spirnaz <spirnaz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 02:35:41 by spirnaz            #+#    #+#             */
/*   Updated: 2023/07/06 21:51:47 by spirnaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	start ile dosya yolunu struct start türündeki buffer içerisine doldurur
	yapı; dosyanın boyutu, izinleri oluşturulma tarihi gibi bilgileri içerir

	 st_mode'un S_IFMT ile AND işlemi sonucunda sadece dosya türü bitleri alınır
	 S_IFDIR (dizin) olup olmadığı kontrol edilir

	 sadece kullanıcının dosyayı yürütme izni varsa (S_IXUSR), koşul sağlanmış olur.
*/
static int	command_path_is_executable(char *command_path)
{
	struct stat	buffer;

	if (stat(command_path, &buffer) != 0)
		return (0);
	if ((buffer.st_mode & S_IFMT) == S_IFDIR)
		return (0);
	if ((buffer.st_mode & S_IXUSR))
		return (1);
	return (0);
}

/*
	comman ve path_part eşleşiyorsa path_part ı döner
	command "/" ile başlamıyorsa part_path ile eşleşmiyorsa, path_partın
	sonuna / eklenerek command ile birleştirilir
	command / ile başlıyorosa zaten bir yoldur ve direkt döndürülür
*/
static char	*find_command_path(char *command, char *path_part)
{
	char	*command_path;
	char	*path_part_with_slash;

	command_path = NULL;
	path_part_with_slash = NULL;
	if (ft_strncmp(path_part, command, ft_strlen(path_part)) == 0)
	{
		command_path = ft_strdup(path_part);
	}
	else if (ft_strncmp(command, "/", 1) != 0)
	{
		path_part_with_slash = ft_strjoin(path_part, "/");
		command_path = ft_strjoin(path_part_with_slash, command);
		free(path_part_with_slash);
	}
	else
	{
		command_path = ft_strdup(command);
	}
	return (command_path);
}

/*
	kullanılan split ile ayırma işleminin amacı
	"/usr/bin:/bin:/usr/local/bin" gibi bir PATH değeri, bu satırın işlemi sonucunda 
	["/usr/bin", "/bin", "/usr/local/bin"] gibi bir dizi elde eder.

	find_command_path: Belirtilen klasör yolu ve komut adını kullanarak tam bir dosya yolu oluşturur.
	command_path_is_executable: Belirtilen dosya yolunun çalıştırılabilir olup olmadığını kontrol eder.
*/
static char	*get_executable_path(char **commands, char *path_env_value)
{
	char	**paths;
	char	*command_executable_path;
	int		i;

	paths = ft_split(path_env_value, ':');
	i = 0;
	while (paths != NULL && paths[i] != NULL)
	{
		command_executable_path = find_command_path(commands[0], paths[i]);
		if (command_path_is_executable(command_executable_path))
		{
			break ;
		}
		if (command_executable_path != NULL)
		{
			free(command_executable_path);
			command_executable_path = NULL;
		}
		i++;
	}
	clear_string_list(paths);
	return (command_executable_path);
}

/*
	fork() ile child proccess oluşturur ve id sini pid içerisine kaydeder
	pid == 0 --> çocuk süreç
	pid > 0  --> ebeveyn süreç
	pid < 0  --> hata durumu

	execve(command_path, commands, NULL) --> bir dosyayı başka bir dosya ile değiştirmek ve yeni
	programı çalıştırmak için kullanılır

	waitpid(pid, &result, 0) --> pid durumu beklenir ve sonucu result içerisine kaydedilir

	WIFEXITED = wait tarafından döndürülen durum bilgisini incelemek için kullanılan bir makrodur
	WIFEXSTATUS = çıkış durumu
*/
static void	execute_non_builtin_command_helper(char **commands,
	char *command_path)
{
	int	pid;
	int	result;

	pid = fork();
	if (pid == 0)
	{
		execve(command_path, commands, NULL);
		if (pid > 0)
			exit(0);
	}
	waitpid(pid, &result, 0);
	unlink("bin/.heredoc_temp");
	if (WIFEXITED(result))
		g_shell->exit_status = WEXITSTATUS(result);
}

void	execute_non_builtin_commands(char **commands)
{
	char	*path_env_value;
	char	*command_executable_path;

	path_env_value = get_path_env_value();
	if (path_env_value == NULL || path_env_value[0] == '\0')
		return ;
	command_executable_path = get_executable_path(commands, path_env_value);
	free(path_env_value);
	if (command_executable_path == NULL)
	{
		if (ft_strchr(commands[0], '/') == NULL)
			ft_printf(STDERR_FILENO, "%s: command not found\n", commands[0]);
		else
			ft_printf(STDERR_FILENO,
				"%s: No such file or directory\n", commands[0]);
		g_shell->exit_status = 127;
		return ;
	}
	execute_non_builtin_command_helper(commands, command_executable_path);
	free(command_executable_path);
}

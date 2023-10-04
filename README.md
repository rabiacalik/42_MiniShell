# 42_MiniShell

line = readline("minishell$ ");
		if (line == NULL)
			exit(EXIT_SUCCESS);
readline ctr + d tusları girildiğinde veya hata durumlarında null döner
strtrim = belirtilen karakterleri baştan ve sondan kaldırır

STDOUT_FILENO, "\033[2J" ekranı temizler
STDOUT_FILENO, "\033[1;1H"); imleci ekranın sol üst köşesine taşır

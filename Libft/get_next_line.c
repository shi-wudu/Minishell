#include "libft.h"

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	ssize_t		bytes_read;
	char		*line;

	line = NULL;
	bytes_read = 1;
	while ((fd >= 0 && BUFFER_SIZE > 0) && bytes_read > 0)
	{
		if (buff[0])
		{
			line = ft_strjoin_gnl(line, buff);
			if (!line)
				return (NULL);
			if (line[ft_strlen_gnl(line) - 1] == '\n')
				break ;
		}
		else
		{
			bytes_read = read(fd, buff, BUFFER_SIZE);
			if (bytes_read < 0)
				return (free(line), NULL);
			buff[bytes_read] = '\0';
		}
	}
	return (line);
}

#include <stdio.h>
int	main(void)
{
	int		fd;
	char	*line;

	// Abrir o ficheiro para leitura
	fd = open("test_file.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Erro ao abrir o ficheiro");
		return (1);
	}

	// Ler e imprimir uma linha de cada vez
	printf("Pressione Enter para ler uma linha:\n");
	while ((line = get_next_line(fd)) != NULL)
	{
		getchar(); // Espera o usuário pressionar Enter
		printf("%s", line); // Imprime a linha retornada
		free(line); // Libera a memória da linha
	}

	// Fechar o ficheiro
	close(fd);
	return (0);
}
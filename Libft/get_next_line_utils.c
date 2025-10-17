#include "libft.h"

size_t	ft_strlen_gnl(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0' && str[i] != '\n')
	{
		i++;
	}
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*result;

	len1 = ft_strlen_gnl(s1);
	len2 = ft_strlen_gnl(s2);
	result = malloc((sizeof(char) * (len1 + len2) + 1));
	if (!result)
		return (free(s1), NULL);
	result[len1 + len2] = '\0';
	i = -1;
	while (++i < len1)
		result[i] = s1[i];
	i = -1;
	while (++i < len2)
		result[len1 + i] = s2[i];
	free(s1);
	i = -1;
	while (s2[len2 + ++i])
	{
		s2[i] = s2[len2 + i];
	}
	s2[i] = '\0';
	return (result);
}
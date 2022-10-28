/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 02:39:16 by fquist            #+#    #+#             */
/*   Updated: 2022/05/15 16:54:20 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	error_msg(char *str, int i)
{
	pthread_mutex_lock(&data()->print);
	printf("ERROR: [%d] %s%s%s\n", i, RED, str, RESET);
	data()->printable = false;
	pthread_mutex_unlock(&data()->print);
}

void	print_msg(int id, char *str)
{
	pthread_mutex_lock(&data()->print);
	if (data()->printable)
	{
		if (id == -1)
			printf("%lu\t%s\n", get_time(), str);
		else
			printf("%lu\t%d %s\n", get_time(), id, str);
	}
	pthread_mutex_unlock(&data()->print);
}

int	str_len(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	index;
	char	*destination;
	char	*source;

	index = 0;
	destination = dst;
	source = (char *) src;
	if (dstsize > 0)
	{
		while (*source && index < dstsize - 1)
		{
			*destination = *source;
			destination++;
			source++;
			index++;
		}
		*destination = '\0';
	}
	return (str_len(src));
}

char	*ft_strdup(const char *s1)
{
	char	*result;
	char	*string;

	string = (char *)s1;
	result = malloc(str_len(string) + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, string, str_len(string) + 1);
	return (result);
}

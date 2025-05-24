/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:50:49 by iwietzke          #+#    #+#             */
/*   Updated: 2024/05/15 23:29:57 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	size_t				i;

	ptr = s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)ptr[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
    const char *str = "igormates@hotmail.com";
    char value = '@';
    size_t num = strlen(str);

    // Encontrar a primeira ocorrência do byte '@' na string
    void *to_find = ft_memchr(str, value, num);

    if (to_find != NULL)
    {
        printf("O dominio é: %s\n", (char *)to_find);
    }
    else
    {
        printf("O caractere '%c' não foi encontrado na região de memória.\n",
		value);
    }
    return (0);
}*/
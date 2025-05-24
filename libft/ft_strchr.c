/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:08:43 by iwietzke          #+#    #+#             */
/*   Updated: 2024/05/15 22:55:33 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}
/*
int	main(void)
{
    const char *str = "Essa e Minha string!";
    char *to_find = ft_strchr(str, 'M');

    printf("Encontrou: %s\n", to_find);

    char *no_find = ft_strchr(str, 'Z');

    if (no_find == NULL)
    {
        printf("Caracter Z nao encontrado\n");
    }
}*/
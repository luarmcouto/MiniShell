/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:30:22 by iwietzke          #+#    #+#             */
/*   Updated: 2024/05/16 12:10:57 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_string;
	int		i;

	i = 0;
	new_string = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if ((!new_string))
		return (NULL);
	while (*s)
	{
		new_string[i++] = *s++;
	}
	new_string[i] = '\0';
	return (new_string);
}
/*
int	main(void)
{
    char array1[] = "Vamos inter";
    char *ptr;
    printf("A string no array1 e: %s\n", array1);
    ptr = ft_strdup(array1);
    printf("A string duplicada: e %s\n", ptr);
    return (0);
}*/
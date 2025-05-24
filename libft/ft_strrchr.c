/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:14:59 by iwietzke          #+#    #+#             */
/*   Updated: 2024/05/22 23:10:38 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last_occurrence;

	last_occurrence = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
			last_occurrence = s;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	else
		return ((char *)last_occurrence);
}
/*
int	main(void)
{
    const char *str = "alguma,coisa,com,virgula";

    char *to_find = ft_strrchr(str, ',');

    if (to_find != NULL)
    {
        printf("%s\n", to_find);
    }
    else
    {
        printf("Caractere não encontrado na string.\n");
    }
    return (0);
}*/
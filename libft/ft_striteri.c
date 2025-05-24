/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:50:34 by iwietzke          #+#    #+#             */
/*   Updated: 2024/05/17 22:19:55 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	if (NULL == s || NULL == f)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
void	uppercase(unsigned int index, char *c)
{
    if (*c >= 'a' && *c <= 'z') 
        *c -= 32;
}

int	main()
{
    char str[] = "INTER, gigante!";

    printf("String original: %s\n", str);
    ft_striteri(str, uppercase);
    printf("String modificada: %s\n", str);
    return (0);
}*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:50:45 by iwietzke          #+#    #+#             */
/*   Updated: 2024/05/16 11:53:27 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		*ptr = 0;
		ptr++;
		n--;
	}
}
/*
int	main(void)
{
    char str[20];
    ft_bzero(str, 10);
    ft_bzero(str + 10, 5);
    printf("%s\n", str);

	//Funcao original
	char str1[20];
    bzero(str1, 10);
    bzero(str1 + 10, 5);
    printf("%s\n", str1);
    return (0);
}*/
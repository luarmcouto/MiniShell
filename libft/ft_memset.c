/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:39:43 by iwietzke          #+#    #+#             */
/*   Updated: 2024/05/15 18:31:42 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		*ptr = (unsigned char)c;
		ptr++;
		n--;
	}
	return (s);
}
/*
int	main(void)
{
    char str[20];
    ft_memset(str, 'A', 10);
    ft_memset(str + 10, 'C', 10);
    printf("%s\n", str);

	//Funcao original
	char str1[20];
    memset(str1, 'A', 10);
    memset(str1 + 10, 'C', 10);
    printf("%s\n", str1);
    return (0);
}*/
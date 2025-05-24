/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:24:13 by iwietzke          #+#    #+#             */
/*   Updated: 2024/05/16 00:30:34 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	size_t			i;

	i = 0;
	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
			return ((unsigned char)ptr1[i] - (unsigned char)ptr2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
    char str1[] = "IgorMates";
    char str2[] = "IgorBates";
    size_t n = 6;

    int result = ft_memcmp(str1, str2, n);

    if (result < 0)
        printf("'%s' é menor que '%s'\n", str1, str2);
    else if (result > 0)
        printf("'%s' é maior que '%s'\n", str1, str2);
    else
        printf("'%s' é igual a '%s'\n", str1, str2);

    int original = memcmp(str1, str2, n);

    // Imprimindo o resultado da função de biblioteca padrão para verificação
    if (original < 0)
        printf("Original: '%s' é menor que '%s'\n", str1, str2);
    else if (original > 0)
        printf("Original: '%s' é maior que '%s'\n", str1, str2);
    else
        printf("Original: '%s' é igual a '%s'\n", str1, str2);
    return 0;
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:45:09 by iwietzke          #+#    #+#             */
/*   Updated: 2024/05/20 21:07:20 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*char_dest;
	const unsigned char	*char_src;
	size_t				i;

	if (!dest && !src)
		return (dest);
	char_dest = (unsigned char *)dest;
	char_src = src;
	i = 0;
	while (i < n)
	{
		char_dest[i] = char_src[i];
		i++;
	}
	return (dest);
}
/*
int	main(void) {
    char src[] = "Internacional";
	char dest[14];

	printf("\nSrc: %s\n", src);
	memcpy(dest, src, sizeof(char) * 14);
	printf("Dest: %s\n", dest);

	char str1[10];
    ft_memcpy(str1, src+8, sizeof(char) * 9);
    str1[9] = '\0';

    printf("str com aritmetica: %s\n", str1);
    printf("\n");
    printf("-------------------------\n");
    printf("\n");

    // Outro teste

    char src1[] = "copy this";
    char dest1[20];

    char *dest_ptr = ft_memcpy(dest1, src1, strlen(src1)+1);

    printf("src: %s\n", src1);
    printf("dest: %s\n", dest1);

    printf("dest_ptr: %p\n", dest_ptr);
    printf("    dest: %p\n", dest1);
    printf("\n");

	return(0);
}*/
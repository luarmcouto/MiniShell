/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:14:34 by iwietzke          #+#    #+#             */
/*   Updated: 2024/05/20 20:52:25 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dest_ptr;
	char	*src_ptr;

	dest_ptr = (char *)dest;
	src_ptr = (char *)src;
	if (!dest && !src)
		return (NULL);
	if (!n || dest == src)
		return (dest);
	if (dest < src)
		ft_memcpy(dest_ptr, src_ptr, n);
	else if (dest > src)
	{
		while (n > 0)
		{
			dest_ptr[n - 1] = src_ptr[n - 1];
			n--;
		}
	}
	return (dest_ptr);
}
/*
int main () {
   char dest[] = "oldstring";
   const char src[]  = "novastring";

   printf("Antes da memmove src = %s, dest = %s\n", src, dest);
   ft_memmove(dest, src, 3);
   printf("Depois mem.move src = %s, dest = %s\n", src, dest);

   return(0);
}*/
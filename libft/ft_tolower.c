/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:48:37 by iwietzke          #+#    #+#             */
/*   Updated: 2024/05/15 22:48:50 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c > 64 && c < 91)
		c += 32;
	return (c);
}
/*
int main(void) {
    char c;

    c = 'A';
    printf("%c -> %c", c, tolower(c));

    c = 'B';
    printf("\n%c -> %c\n", c, ft_tolower(c));
    return (0);
}*/
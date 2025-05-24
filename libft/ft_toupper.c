/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:47:28 by iwietzke          #+#    #+#             */
/*   Updated: 2024/05/15 22:47:51 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c > 96 && c < 123)
		c -= 32;
	return (c);
}
/*
int main(void) {
    char c;

    c = 'a';
    printf("%c -> %c", c, toupper(c));

    c = 'a';
    printf("\n%c -> %c\n", c, ft_toupper(c));
    return (0);
}*/
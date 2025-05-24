/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:57:07 by iwietzke          #+#    #+#             */
/*   Updated: 2024/05/16 13:48:12 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	if (!s)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
char	uppercase(unsigned int index, char c)
{
    if (c >= 'a' && c <= 'z') {
        return (c - 32);
    } else {
        return (c);
    }
}
int	main(void)
{
    char original[] = "inter, gigante!";
    char *modified;

    modified = ft_strmapi(original, uppercase);

    printf("Original: %s\n", original);
    printf("Modified: %s\n", modified);

    free(modified);

    return (0);
}*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 21:41:38 by iwietzke          #+#    #+#             */
/*   Updated: 2024/05/20 23:04:02 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len + 1);
	ft_strlcat(str, s2, len + 1);
	return (str);
}
/*
int	main(void)
{
	char str1[] = "Inter";
	char str2[] = ", maior do mundo!";

	char *join = ft_strjoin(str1, str2);

	if (join != NULL)
    {
        printf("Resultado: %s\n", join);
        free(join);
    }
    else
        printf("Erro: inválido.\n");

    return (0);
}*/
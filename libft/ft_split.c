/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:01:07 by iwietzke          #+#    #+#             */
/*   Updated: 2024/05/24 18:29:14 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static int	ft_wordlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**ft_free(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc((ft_wordcount(s, c) + 1) * sizeof(char *));
	if (!s || !str)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			str[j] = ft_substr(s, i, ft_wordlen(&s[i], c));
			if (!str[j])
				return (ft_free(str, j));
			j++;
			i += ft_wordlen(&s[i], c);
		}
		else
			i++;
	}
	str[j] = NULL;
	return (str);
}
/*
int	main()
{
	char **result;
    printf("Splits:\n");
    result = ft_split("Inter maior do mundo", ' ');
    if (result)
    {
        int i = 0;
        while (result[i] != NULL)
        {
            printf("%s\n", result[i]);
            free(result[i]);
            i++;
        }
        free(result);
    }
    else
        printf("Erro: a função ft_split retornou NULL\n");
	//Teste: cc ft_split.c ft_substr.c ft_strlcpy.c
	//ft_strlen.c ft_strdup.c ft_calloc.c ft_bzero.c
}*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 16:32:01 by myener            #+#    #+#             */
/*   Updated: 2020/06/22 02:06:23 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_bl(char *base)
{
	int	baselen;
	int	j;

	baselen = 0;
	while (base[baselen])
	{
		if (base[baselen] == '-' || base[baselen] == '+')
			return (0);
		j = baselen + 1;
		while (base[j])
		{
			if (base[baselen] == base[j])
				return (0);
			++j;
		}
		++baselen;
	}
	return (baselen >= 2 ? baselen : 0);
}

int		troubleshoot(char *s, char *base)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	while (s[k] && (ft_isblank(s[k]) || s[k] == '\r' || s[k] == '\n'
	|| s[k] == '\v' || s[k] == '\f'))
		k++;
	i = k;
	while (s[i])
	{
		j = 0;
		while (base[j] && (s[i] != base[j] || (s[i] == '-' || s[i] == '+')))
			++j;
		if (s[i] != base[j] && s[i] != '-' && s[i] != '+')
			return (0);
		i++;
	}
	return (i == 0 ? 0 : 1);
}

int		get_nb(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] && base[i] != c)
		i++;
	return (i);
}

int		ft_atoi_base(char *str, char *base)
{
	int	s;
	int	i;
	int	r;
	int	neg;

	if (!troubleshoot(str, base))
		return (0);
	s = 0;
	while (str[s] && (ft_isblank(str[s] || str[s] == '\r' || str[s] == '\n'
	|| str[s] == '\v' || str[s] == '\f')))
		s++;
	i = s - 1;
	r = 0;
	neg = 1;
	while (str[++i] && (((str[i] == '-' || str[i] == '+') && i == s) ||
			(str[i] != '-' && str[i] != '+')))
	{
		neg = (str[i] == '-') ? -1 : neg;
		r = (str[i] != '+') ? (r * get_bl(base) + (get_nb(str[i], base))) : r;
	}
	free(str);
	return (r * neg);
}

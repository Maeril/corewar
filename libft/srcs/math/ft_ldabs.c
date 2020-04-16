/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldabs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 10:47:02 by hben-yah          #+#    #+#             */
/*   Updated: 2019/11/27 10:47:15 by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


long double		ft_ldabs(long double d)
{
	return (d < 0 ? -d : d);
}

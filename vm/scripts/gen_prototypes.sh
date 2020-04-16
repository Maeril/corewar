#!/bin/sh
echo "/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-yah <hben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: \c" > includes/prototypes.h

date "+%Y/%m/%d %H:%M:%S" | tr -d '\n' >> includes/prototypes.h

echo " by hben-yah          #+#    #+#             */
/*   Updated: \c" >> includes/prototypes.h

date "+%Y/%m/%d %H:%M:%S" | tr -d '\n' >> includes/prototypes.h

echo " by hben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

/*
** Prototypes
*/

" >> includes/prototypes.h
find srcs -name '*.c' ! -name 'old_*.c' -exec cat {} \; | grep -v static | grep -v -E "^const" | grep -A 1 -E "^[a-z]+" | grep -v -E "(;|	return|	while|	if|=|->|\?|:|{|}|\-\-)" |
sed -e s/\)' '*\$/\)\;/g | sed -e s/\)\$/\)\;/g | tr -s '\n' '?' | sed -e s/\;\?/\;\!/g | tr -s '!' '\n' | tr -d '?' | tr -s '	' '	' |
sed -e 's/	/			/g' | sed -e 's/^int[^0-9m]/int		/g' | sed -e 's/^	/			/g' >> includes/prototypes.h
echo "
#endif" >> includes/prototypes.h
#find srcs -name '*.c' -exec cat {} \; | tr -s '\t\n' ' ' | grep -E "([a-z0-9_*]+ )?[a-z0-9_*]+ [a-z0-9_*]+\([a-z0-9_,() *]+\) {" -o | sed -e 's/ {//g' | sed -e 's/ /                            /'
#find srcs -name '*.c' -exec cat {} \; | grep -A 1 -E "([a-z0-9_()*]+[       \n]+)?([a-z0-9_()*]+[    \n]+)\([a-z0-9_(), *]+\)"
#find srcs -name '*.c' -exec cat {} \; | grep -v static | grep -A 1 -E "^[a-z]+" | grep -v -E "(;|return|while|if|=|->|\?|:|{|}|\-\-)" | tr -d '\n' | sed -e s/\)/\)\;%/g | sed -e s/,/,%/g | tr % '\n'

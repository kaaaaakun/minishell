/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:55:42 by tokazaki          #+#    #+#             */
/*   Updated: 2023/06/22 18:49:55 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdio.h>     // For printf
#include <stdlib.h>    // For calloc, exit
#include <string.h>    // For memset
#include <limits.h>    // For INT_MAX

int main ()
{
	char	*str;

	str = "Hello, world!";
	ft_printf("aaaa%c %c %c %c\n", '1', 'B', 'C', 'D');
	printf("aaaa%c %c %c %c\n", 'A', 'B', 'C', 'D');
	printf("\n");
	ft_printf("%s\n", str);
	printf("%s\n", str);
	printf("\n");
	ft_printf("%p\n", &str[0]);
	printf("%p\n", &str[0]);
	printf("\n");
	ft_printf("%d\n", INT_MIN);
	printf("%d\n", INT_MIN);
	printf("\n");
	ft_printf("%i\n", 1 + 1);
	printf("%i\n", 1 + 1);
	printf("\n");
	ft_printf("%x\n", 42);
	printf("%x\n", 42);
	printf("\n");
	ft_printf("%X\n", 4242);
	printf("%X\n", 4242);
	printf("\n");
	printf("%d %c %s %p\n", 4, '1', "11", &str[3]);
	ft_printf("%d %c %s %p\n", 4, '1', "11", &str[3]);
	printf("\n");
	ft_printf("Hello, %d, %d, %i, %i.\n", INT_MAX, INT_MIN, INT_MAX, INT_MIN);
	printf("Hello, %d, %d, %i, %i.\n", INT_MAX, INT_MIN, INT_MAX, INT_MIN);
	printf("\n");
	ft_printf("Hello, %u, %u, %u\n", 0x7fffffff, 0x80000000, 0xffffffff);
	printf("Hello, %u, %u, %u\n", 0x7fffffff, 0x80000000, 0xffffffff);
	printf("\n");
	ft_printf("Hello, %x, %x, %x\n", 0x7fffffff, 0x80000000, 0xffffffff);
	printf("Hello, %x, %x, %x\n", 0x7fffffff, 0x80000000, 0xffffffff);
	ft_printf("Hello, %X, %X, %X\n", 0x7fffffff, 0x80000000, 0xffffffff);
	printf("Hello, %X, %X, %X\n", 0x7fffffff, 0x80000000, 0xffffffff);
	printf("\n");
	ft_printf("Hello, %p, %p, %p\n", &str[0], &str[1], &str[2]);
	printf("Hello, %p, %p, %p\n", &str[0], &str[1], &str[2]);
	printf("\n");

	//通常の文字の出力
	int i = printf("aaa\n");
	int j = ft_printf("aaa\n");
	printf("%d:%d\n\n",i,j);

	//空文字の出力
	i = printf("");
	j = ft_printf("");
	printf("%d:%d\n\n",i,j);

	//%の出力
	i = printf("%%\n");
	j = ft_printf("%%\n");
	printf("%d:%d\n\n",i,j);

	//cの出力
	int c = '5';
	i = printf("%c%c\n",c,c);
	j = ft_printf("%c%c\n",c,c);
	printf("%d:%d\n\n",i,j);

	//sでNULLの出力
	char *n = NULL;
	i = printf("%s%s\n",n,n);
	j = ft_printf("%s%s\n",n,n);
	printf("%d:%d\n\n",i,j);
	
	//inの出力
	int in = 123456789;
	i = printf("ex:%d:%i\n",in,in);
	j = ft_printf("ft:%d:%i\n",in,in);
	printf("%d:%d\n\n",i,j);

	//xの出力
	int x = -123456789;
	i = printf("ex:%x%X\n",x,x);
	j = ft_printf("ft:%x%X\n",x,x);
	printf("%d:%d\n\n",i,j);

	//uの出力
	unsigned int u = -1;
	i = printf("ex:%u:%u\n",u,u);
	j = ft_printf("ft:%u:%u\n",u,u);
	printf("%d:%d\n\n",i,j);

	//pの出力
	i = printf("ex:%p:%p\n",u,x);
	j = ft_printf("ft:%p:%p\n",u,x);
	printf("%d:%d\n\n",i,j);

	//pの出力
	i = printf("ex:%p:%p\n",LONG_MIN, LONG_MAX);
	j = ft_printf("ft:%p:%p\n",LONG_MIN, LONG_MAX);
	printf("pの出力longMAX:%u:%d:%d\n\n",LONG_MAX,i,j);


	//pの出力
	i = printf("ex:%p:%p\n",-ULONG_MAX, ULONG_MAX);
	j = ft_printf("ft:%p:%p\n",-ULONG_MAX, ULONG_MAX);
	printf("pの出力UlongMAX:%u:%d:%d\n\n",ULONG_MAX,i,j);
	
	//pの出力
	i = printf("ex:%p:%p\n",90000, 0);
	j = ft_printf("ft:%p:%p\n",90000, 0);
	printf("pの出力%d:%d\n\n",i,j);

	//ulの出力
	i = printf("ex:%u:%x\n",ULONG_MAX, ULONG_MAX);
	j = ft_printf("ft:%u:%x\n",ULONG_MAX, ULONG_MAX);
	printf("ulの出力%d:%d\n\n",i,j);

	//INT_MAX超えの出力
	i = printf("ex:%u:%x\n",ULONG_MAX, ULONG_MAX);
	j = ft_printf("ft:%u:%x\n",ULONG_MAX, ULONG_MAX);
	printf("%d:%d\n\n",i,j);

    char *sss = (char *)calloc(1, (size_t)INT_MAX + 10);
    memset(sss, 'a', (size_t)INT_MAX + 5);
    i = printf("%s\n", sss);
    j = ft_printf("%s\n", sss);
	printf("INT_MAX超えの出力%d:%d\n\n",i,j);

	//INT_MAX超えの出力
    sss = (char *)calloc(1, (size_t)INT_MAX + 10);
    memset(sss, 'a', (size_t)INT_MAX -3);
    i = printf("aaa%s\n", sss);
    j = ft_printf("aaa%s\n", sss);
	printf("%d:%d\n\n",i,j);

	exit (0);
}

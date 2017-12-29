#include <stdio.h>
#include "libft.h"

#define CLS "\033[H\033[J"

void	ft_lstpop(t_list **dest)
{
	t_list	*tmp;

	tmp = (*dest)->next;
	ft_memdel((void **)&(*dest)->content);
	ft_memdel((void **)dest);	
	*dest = tmp;
}

size_t	ft_lstsize(t_list *lst)
{
	size_t	s;

	s = 0;
	while (lst && ++s)
		lst = lst->next;
	return (s);
}

int	blocksCount;

void	draw(t_list *cols[3])
{
	char	border[blocksCount * 3 + 13];
	char	*s[3];
	int	size[3];
	t_list	*cols_t[3];

	for (int i = 0; i < 3; i++)
	{
		cols_t[i] = cols[i];
		size[i] = ft_lstsize(cols_t[i]);
	}
	printf("%s", CLS);
	ft_memset(border, '*', blocksCount * 3 + 12);
	border[blocksCount * 3 + 12] = 0;
	printf("|%s|\n|%*s|\n", border, blocksCount * 3 + 12, "");
	for (int i = 0; i < blocksCount; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			s[j] = size[j] >= blocksCount - i ? cols_t[j]->content : "";
			size[j] >= blocksCount - i ? cols_t[j] = cols_t[j]->next : 0;
		}
		printf("|  %*s    %*s    %*s  |\n",
			  blocksCount, s[0], blocksCount, s[1], blocksCount, s[2]);
	}
	printf("|%*s|\n|%s|\n", blocksCount * 3 + 12, "", border);
}

void	hanoe(int number, t_list *cols[3], int delay, int d[3])
{
	if (!number)
		return ;
	hanoe(number - 1, cols, delay, (int [3]){d[0], d[2], d[1]});
	ft_lstadd(&cols[d[1]], ft_lstnew(cols[d[0]]->content, cols[d[0]]->content_size));
	ft_lstpop(&cols[d[0]]);
	draw(cols);
	usleep(delay ? 500000 : 200);
	hanoe(number - 1, cols, delay, (int [3]){d[2], d[1], d[0]});
}

void	get_input(char *delay)
{
	char	tmp;

	while (1)
	{
		ft_printf("{cyan}Enter high of the tower: {nc}");
		scanf("%d", &blocksCount);
		ft_printf("{cyan}Set delay? (y/n): {nc}");
		scanf(" %c", &tmp);
		*delay = tmp == 'y' ? 1 : 0;
		if (blocksCount < 1 || blocksCount > 32)
			ft_printf("{red}Incorect high of the tower! [1 - 32]\nTry again.\n{nc}");
		else
			break;
	}
}

void	solve(int delay)
{
	t_list	*cols[3];
	char	*s_tmp;

	for (int i = 0; i < 3; i++)
	  cols[i] = NULL;
	s_tmp = ft_strnew(blocksCount);
	for (int i = 1; i <= blocksCount; i++)
	{
		ft_memset(s_tmp, '-', i);
		ft_lstadd_back(&cols[0], ft_lstnew(s_tmp, ft_strlen(s_tmp) + 1));
	}
	ft_memdel((void **)&s_tmp);
	draw(cols);
	usleep(delay ? 500000 : 200);
	hanoe(blocksCount, cols, delay, (int[3]){0, 2, 1});
}

int	main(void)
{
	char	delay;

	ft_printf("{green}Copyright\n2017 - CoZZ\nHanoe towers problem \
implementation on C\n\n{nc}");
	get_input(&delay);
	solve(delay);
	return (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	nb(char *b, int w, int h, int i)
{
	int	n;
	int	x;
	int	y;
	int	dx;
	int	dy;

	n = 0;
	x = i % w;
	y = i / w;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (!(dy == 0 && dx == 0)
				&& y + dy >= 0 && y + dy < h
				&& x + dx >= 0 && x + dx < w
				&& b[(y + dy) * w + (x + dx)])
				n++;
			dx++;
		}
		dy++;
	}
	return (n);
}

void	step(char *b, int w, int h)
{
	char	*cp;
	int		i;
	int		n;
	int		sz;

	sz = w * h;
	cp = malloc(sz);
	i = 0;
	while (i < sz)
	{
		cp[i] = b[i];
		i++;
	}
	i = 0;
	while (i < sz)
	{
		n = nb(cp, w, h, i);
		b[i] = (n == 3 || (n == 2 && cp[i]));
		i++;
	}
	free(cp);
}

void	draw(char *b, int w, int h)
{
	int		x;
	int		y;
	int		pen;
	char	c;

	x = 0;
	y = 0;
	pen = 0;
	while (read(0, &c, 1) == 1)
	{
		if (c == 'x')
			pen = !pen;
		else if (c == 'w' && y > 0)
			y--;
		else if (c == 's' && y < h - 1)
			y++;
		else if (c == 'a' && x > 0)
			x--;
		else if (c == 'd' && x < w - 1)
			x++;
		if (pen)
			b[y * w + x] = 1;
	}
}

void	print(char *b, int w, int h)
{
	int	i;

	i = 0;
	while (i < w * h)
	{
		if (b[i])
			putchar('O');
		else
			putchar(' ');
		if ((i + 1) % w == 0)
			putchar('\n');
		i++;
	}
}

int	main(int ac, char **av)
{
	int		w;
	int		h;
	int		n;
	char	*b;

	if (ac != 4)
		return (1);
	w = atoi(av[1]);
	h = atoi(av[2]);
	n = atoi(av[3]);
	b = calloc(w * h, 1);
	draw(b, w, h);
	while (n > 0)
	{
		step(b, w, h);
		n--;
	}
	print(b, w, h);
	free(b);
	return (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int ac, char **av) {
	if (ac != 4) return 1;

	int w, h, n, pen, px, py, *b;
	char ch;

	w = atoi(av[1]);
	h = atoi(av[2]);
	n = atoi(av[3]);

	pen = px = py = 0;

	b = calloc(w * h, sizeof(int));
	if (!b) return 1;

	while (read(0, &ch, 1) == 1) {
		if (ch == 'x') {
			pen = !pen;
			if (pen)
				b[py * w + px] = 1;
		}
		if (ch == 'w' && py > 0) py--;
		if (ch == 'a' && px > 0) px--;
		if (ch == 's' && py < h - 1) py++;
		if (ch == 'd' && px < w - 1) px++;
		if (pen) b[py * w + px] = 1;
	}

	int x, y;
	y = -1;
	while (++y < h) {
		x = -1;
		while (++x < w) {
			putchar(b[y * w + x] ? '0' : ' ');
		}
		putchar('\n');
	}
	return (0);
}

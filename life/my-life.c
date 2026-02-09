#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av) {
	if (ac != 4) return 1;

	int w, h, n, x, y, pen, *b;
	w = atoi(av[1]);
	h = atoi(av[2]);
	n = atoi(av[3]);
	b = calloc(w * h, sizeof(int));
	if (!b) return 1;

	char ch;
	pen = 0;
	x = 0;
	y = 0;
	while (read(0, &ch, 1) == 1) {
		if (ch == 'x') {
			pen = !pen;
			if (pen) b[y * w + x] = 1;
		}
		if (ch == 'w' && y > 0) y--;
		if (ch == 'a' && x > 0) x--;
		if (ch == 's' && y < h - 1) y++;
		if (ch == 'd' && x < w - 1) x++;
		if (pen) b[y * w + x] = 1;
	}
	int *t, *tmp;
	t = calloc(w * h, sizeof(int));
	int ty, tx, my, mx;
	while (n-- > 0) {
		ty = -1;
		while (++ty < h) {
			tx = -1;
			while (++tx < w) {
				int c = 0;
				my = -2;
				while (++my <= 1) {
					mx = -2;
					while (++mx <= 1) {
						if ((mx != 0 || my != 0) && tx + mx < w && ty + my < h && tx + mx >= 0 && ty + my >= 0)
							c += b[(ty+my) * w + tx + mx];
					}
				}
				t[ty * w + tx] = (c == 3 || (c == 2 && b[ty * w + tx]));
			}
		}
		tmp = b; b = t; t = tmp;
	}

	int px, py;
	py = -1;
	while (++py < h) {
		px = -1;
		while (++px < w) {
			putchar(b[py * w + px] ? 'O' : ' ');
		}
		putchar('\n');
	}
	free(b);
	free(t);
	return (0);
}

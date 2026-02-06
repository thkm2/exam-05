# life - Cheat Sheet

## Structure : 3 phases dans main()

### Phase 1 : Lecture stdin
- `calloc(w * h, 4)` pour board `b` et temp `t`
- pen = 0 (UP), px/py = 0
- `x` : toggle pen, si pen DOWN -> marquer cellule
- `w/a/s/d` : deplacer (clampe), si pen DOWN -> marquer
- else : ignorer

### Phase 2 : Game of Life (n iterations)
- Double boucle y/x, compter 8 voisins avec dy/dx (-1 a 1)
- Skip self : `(dx || dy)`
- Regle : `t[i] = (c == 3 || (c == 2 && b[i]))`
- Swap pointeurs b/t (pas de memcpy)

### Phase 3 : Affichage
- `putchar('O')` ou `putchar(' ')` + `putchar('\n')`

## Points cles
- Index tableau plat : `y * w + x`
- dy/dx commencent a -2 avec ++pre dans le while
- Bornes : `y+dy >= 0 && y+dy < h && x+dx >= 0 && x+dx < w`
- `calloc` initialise a 0 (pas besoin de memset)
- Includes : `stdio.h` (putchar) + `stdlib.h` (atoi, calloc) + `unistd.h` (read)

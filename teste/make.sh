TREE = tree.h / tree.c
HEAP = heap.h p_queue / heap.c
TYPE = type.h
MAIN = main.c
	gcc $(TREE)  $(HEAP) $(TYPE) -o MAIN -lm -w
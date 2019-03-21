TREE = tree.h tree.c
MAIN = main.c
P_QUEUE = p_queue.c p_queue.h
HASH = hash.c hash.h
COMPRESS = compress.c compress.h
DESCOMPRESS = decompress.c decompress.h
UTI = utilities.c utilities.h
TEST = CUnitTest.c

de_comprimir:
	gcc $(P_QUEUE)	$(HASH)	$(TREE)	$(MAIN)	$(COMPRESS)	$(DESCOMPRESS)	$(UTI) -o	main -lm

test:
		gcc $(P_QUEUE)	$(HASH)	$(TREE)	$(COMPRESS)	$(DESCOMPRESS)	$(UTI) $(TEST) -o	test -lm -lcunit

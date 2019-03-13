graf<-read.table("amostra.txt", header = TRUE, sep = " ")
plot(graf$ABB~graf$Valor, main="Árvore Balanceada X Árvore Desbalanceada", xlab="Valores", ylab="Comparações", col="blue")
points(graf$AVL~graf$Valor, col="red")
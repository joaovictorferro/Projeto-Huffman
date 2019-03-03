void writeTree(HuffmanTree *tree, FILE *outputFile) {
    if(isLeaf(tree)) {
        if(*(byte*)(tree->treeByte) == '*' || *(byte*)(tree->treeByte) == '\\') {
            byte aux = '\\';
            fprintf(outputFile, "%c", aux);
        }
        fprintf(outputFile, "%c", *(byte*)(tree->treeByte));
        return;
    }
    fprintf(outputFile, "%c", *(byte*)(tree->treeByte));
    if(tree->left != NULL)
        writeTree(tree->left, outputFile);
    if(tree->right != NULL)
        writeTree(tree->right, outputFile);
}

void getSizeUtil(HuffmanTree* tree, int* sizePointer) {
    if(isLeaf(tree)) {
        if(*(byte*)(tree->treeByte) == '\\' || *(byte*)(tree->treeByte) == '*')
            (*sizePointer)++;
        (*sizePointer)++;
        return;
    }
    (*sizePointer)++;
    if(tree->left != NULL)
        getSizeUtil(tree->left, sizePointer);
    if(tree->right != NULL)
        getSizeUtil(tree->right, sizePointer);
}
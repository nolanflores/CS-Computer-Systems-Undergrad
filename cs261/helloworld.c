#include <stdio.h>
#include <malloc.h>

struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};

int main(int argc, char *argv[]){
    struct Node root;
    root.data = 3;
    root.left = NULL;
    root.right = NULL;

    printf("%d\n", root.data);
    printf("%p, %p\n", root.left, root.right);

    return 0;
}
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include"list_queue.h"

typedef struct _treenode{
    int data;
    struct _treenode* lchild;
    struct _treenode* rchild;
}Tnode, Tree;

void binarytree_create(Tree **Root){
    int a = 0;
    printf("\r\n 输入节点数值(当输入100 表示节点创建完成):");
    scanf("%d",&a);

    if(a == 100){
        // (*Root)->lchild = NULL;
        // (*Root)->rchild = NULL;
        *Root = NULL;
       
    }
    else
    {
        (*Root) = (Tree*)malloc(sizeof(Tree));//*root 相当于是root节点
        printf("the address is :OX%p\n",Root);
        if((*Root) == NULL)
            return;
        (*Root)->data = a;
        printf("\r\n create %d left child",a);
        binarytree_create(&((*Root)->lchild));
        printf("\r\n create %d right child",a);
        binarytree_create(&((*Root)->rchild)); 
    }
    return;
}

void binarytree_destory(Tree* Root){
    if(Root == NULL)
        return;
    binarytree_destory(Root->lchild);
    binarytree_destory(Root->rchild);
    free(Root);

}

/*preorder iteration*/
void Btree_preorder(Tree* Root){
    if(Root == NULL)
        return;
    printf(" %d ",Root->data);
    Btree_preorder(Root->lchild);
    Btree_preorder(Root->rchild);
}

/*inorder iteration*/
void Btree_inorder(Tree* Root){
    if(Root == NULL)
        return;
    Btree_inorder(Root->lchild);
    printf(" %d ",Root->data);
    Btree_inorder(Root->rchild);
    return;
}

/*postorder*/
void Btree_postorder(Tree* Root){
    if(Root== NULL)
        return;
    Btree_postorder(Root->lchild);
    Btree_postorder(Root->rchild);
    printf(" %d ",Root->data);
}

/*binarytree_levelorder*/
void Btree_levelorder(Tree* root){
    list_queue *queue = NULL;
    Tnode* node = NULL;
    if(root == NULL)
        return;
    queue = list_queue_create();
    //root enqueue first
    list_queue_enqueue(queue,(void *)root);
    while(!queue_is_empty(queue))
    {
        list_queue_dequeue(queue,(void *)&node);//root
        printf(" %d ",node->data);

        if(node->lchild != NULL){
            list_queue_enqueue(queue,(void*)node->lchild);
        }
        if(node->rchild != NULL){
            list_queue_enqueue(queue,(void *)node->rchild);
        }
    }
    free(queue);
}

/*print num of leaves*/
int print_Tnodes(Tree* root){
    if(root == NULL)
        return 0;
    if((root->lchild == NULL)&&(root->rchild == NULL)){
        return 1;
    }
    return print_Tnodes(root->lchild) + print_Tnodes(root->rchild);
}

/*print leave nodes*/
void Btree_printleaf(Tree* root){
    if(root == NULL)
        return;
    if(root->lchild==NULL && root->rchild== NULL)
        printf(" %d ",root->data);
    else{
        Btree_printleaf(root->lchild);
        Btree_printleaf(root->rchild);
    }
}

/*print the height of nodes*/
int Btree_height(Tree* root){
    int lhigh = 0;
    int rhigh = 0;
    if(root == NULL)
        return 0;
    lhigh = Btree_height(root->lchild);
    rhigh = Btree_height(root->rchild);

    return (lhigh > rhigh)?(lhigh +1):(rhigh+1);
}

int main(){
	Tree *root = NULL;

	// setenv("MALLOC_TRACE","1.txt",1);
    // mtrace();
	
	printf("\r\n创建二叉树:");
	binarytree_create(&root);
    printf("the address is :OX%p\n",root);

	// printf("\r\n先序遍历二叉树:");
	// Btree_preorder(root);
	// printf("\r\n中序遍历二叉树:");
	// Btree_inorder(root);
	// printf("\r\n后序遍历二叉树:");
	// Btree_postorder(root);
	printf("\r\n层次遍历二叉树:");
	Btree_levelorder(root);

	printf("\r\n打印二叉树叶子节点:");
	Btree_printleaf(root);
	printf("\r\n打印二叉树叶子节点个数:%d",print_Tnodes(root));
	printf("\r\n打印二叉树高度:%d",Btree_height(root));

	binarytree_destory(root);

    // muntrace();
	return 0;    
}

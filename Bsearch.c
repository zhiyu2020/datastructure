#include<assert.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include "Bsearch.h"

bstree *bstree_create(compare_func compare,destory_func destory){
    bstree * tree = NULL;
    tree = (bstree*)malloc(sizeof(bstree));
    if(tree == NULL)
        return NULL;
    tree->size = 0;
    tree->compare = compare;
    tree->destory = destory;
    tree->root = NULL;
    return tree;
}

bstree_node* bstree_search(bstree* tree,int data){
    bstree_node* node = NULL;
    int res = 0;
    if(tree==NULL ||(bstree_is_empty(tree)))
        return NULL;
    node = tree->root;

    while(node != NULL){
        res = tree->compare(data,node->data);
        if(res == 0){
            return node;
        }
        else if(res > 0){
            node = node->rchild;
        }
        else{//res < 0
            node = node->lchild;
        }
    }
    return NULL;
}
//??????????????????????
int bstree_insert(bstree* tree,int data){
    bstree_node* node = NULL;
    bstree_node* tmp = NULL;
    int res = 0;
    if(tree== NULL)
        return -1;
    node = (bstree_node*)malloc(sizeof(bstree_node));
    node->data = data;
    node->lchild = NULL;
    node->rchild = NULL;
    /*如果二叉树为空 直接挂到根节点*/
    if(bstree_is_empty(tree)){
        tree->root = node;
        tree->size++;
        return 0;
    }
    tmp = tree->root;

    while(tmp != NULL){
        res = tree->compare(data,tmp->data);
        if(res>0)/*右孩子查找*/{
            if(tmp->rchild==NULL){
                tmp->rchild = node;
                tree->size++;
                return 0;
            }
            tmp = tmp->rchild;//update node
        }
        else/*左孩子查找*/{
            if(tmp->lchild == NULL){
                tmp->lchild = node;
                tree->size++;
                return 0;
            }
            tmp = tmp->lchild;
        }
    }
    return -3;
}

int bstree_delete(bstree* tree,int data){
    bstree_node* node = NULL;
    bstree_node* pnode = NULL;
    bstree_node* minnode = NULL;
    bstree_node* pminnode = NULL;
    //int tmp = 0;
    int res = 0;

    if((tree == NULL)||(bstree_is_empty(tree)))
        return -1;
    node = tree->root;
    while((node!=NULL) && ((res = tree->compare(data,node->data))!=0)){
        pnode = node;
        if(res>0)
            node = node->rchild;
        else
        {
            node = node->lchild;
        }
    }
    /*要删除的节点不存在*/
    if(node == NULL)
        return -2;
    /*1.如果要删除node有2个子节点 需要找到右子树的最小节点minnode,
     *更新minnode和node节点数据 这样minnode节点就是要删除的节点
     * 再更新node和pnode节点指向要删除的节点*/
    if((node->lchild != NULL) &&(node->rchild != NULL)){
        minnode = node->rchild;
        pminnode = node;
        while(minnode->lchild != NULL){
            pminnode = minnode;
            minnode = minnode->lchild;
        }
        //replace the node data
        node->data = minnode->data;
        //delete the node
        node = minnode;
        pnode = pminnode;
    }

    /*2.当前要删除的节点只有左孩子或者右孩子 直接父节点指向删除的节点*/
    if(node->lchild != NULL)
        minnode = node->lchild;
    else if(node->rchild != NULL)
        minnode = node->rchild;
    else 
        minnode = NULL;
    if(pnode == NULL)//当要删除的是root
        tree->root = minnode;
    else if(pnode->lchild == node)//node is leftchild
        pnode->lchild = minnode;
    else //node is the right child
        pnode->rchild = minnode;
    tree->size--;
    free(node);
    
    return 0;
}

void bstree_destory_node(bstree* tree,bstree_node* root){
    if(root == NULL)
        return;
    bstree_destory_node(tree,root->lchild);
    bstree_destory_node(tree,root->rchild);
    free(root);
}

/*binary tree destory*/
void bstree_destory(bstree* tree){
    bstree_destory_node(tree,tree->root);
    free(tree);
    return;
}

/*中序遍历打印树节点*/
void bstree_inorder_node(bstree_node* root){
    if(root == NULL)
        return;
    bstree_inorder_node(root->lchild);
    printf(" %d ",root->data);
    bstree_inorder_node(root->rchild);
    return;
}

void bstree_dump(bstree* tree){
    if((tree == NULL)||(bstree_is_empty(tree)))
        printf("\r\n 当前是空树");
    printf("\r\nSTART--------------%d------------\r\n",tree->size);
    bstree_inorder_node(tree->root);
    printf("\r\nEND-------------------------",tree->size);
}

int bstree_compare(int key1,int key2){
    if(key1 == key2)
        return 0;
    else if(key1 > key2)
        return 1;
    else 
        return -1;
}

int main()
{
	bstree *tree = NULL;
	bstree_node *node = NULL;
	mytype data = 0;
	int res = 0;

	// setenv("MALLOC_TRACE","1.txt",1);
    // mtrace();

	tree = bstree_create(bstree_compare,NULL);
	assert(tree != NULL);

    while(1)
	{
		printf("\r\n插入一个数字，输入100时退出：");
		scanf("%d",&data);
		if(data == 100)break;
		res = bstree_insert(tree,data);
		printf("\r\n %d 插入%s成功",data,(res != 0)?("不"):(" "));
	}
	bstree_dump(tree);

    while(1)
	{
		printf("\r\n查询一个数字，输入100时退出：");
		scanf("%d",&data);
		if(data == 100)break;
		node = bstree_search(tree,data);
		printf("\r\n %d %s存在树中",data,(node == NULL)?("不"):(" "));
	}
	bstree_dump(tree);
    while(1)
	{
		printf("\r\n删除一个数字，输入100时退出：");		scanf("%d",&data);
		if(data == 100)break;
		res = bstree_delete(tree,data);
		printf("\r\n %d 删除%s成功",data,(res != 0)?("不"):(" "));
	    bstree_dump(tree);
	}

	bstree_destory(tree);

    //muntrace();

	return 0;
}

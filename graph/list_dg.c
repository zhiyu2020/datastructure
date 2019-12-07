/*邻接表示的有向图*/
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define MAX 100
#define isLetter(a) ((((a)>='a')&&((a)<='z'))||(((a)>='A')&&((a)<='Z')))
#define LEN(a)   (sizeof(a)/sizeof(a[0]))

//邻接表中对应的链表的顶点
typedef struct _ENode{
    int ivex;  //该边指向的顶点的位置
    struct _ENode * next_edge; //指向下一个指针
}ENode, *PENode;

//邻接表中表的顶点
typedef struct _VNode{
    char data;  //顶点信息
    ENode* first_edge;  //指向第一条依附该顶点的弧
}VNode;

//邻接表
typedef struct _LGraph{
    int vexnum;
    int edgenum;
    VNode vexs[MAX];
}LGraph;

/*返回ch在matrix矩阵的位置*/
int get_position(LGraph g,char ch){
    int i;
    for(i=0;i<g.vexnum;i++){
        if(g.vexs[i].data == ch)
            return i;
    }
    return -1;
}

/*读取一个输入字符*/
static char read_char(){
    char ch;

    do{
        ch = getchar();
    }while(!isLetter(ch));

    return ch;
}

/*将node link to the tail part*/
static void link_last(ENode* list, ENode* node){
    ENode* p = list;
    while(p->next_edge){
        p = p->next_edge;
    }
    p->next_edge = node;
    p->next_edge->next_edge = NULL;
}

/*create 邻接表对应的图 自己输入*/
LGraph* create_lgraph(){
    char c1,c2;
    int v,e;
    int i,p1,p2;
    ENode *node1,*node2;
    LGraph* pG;
    //输入顶点数 和 边数
    printf("input vertex number:");
    scanf("%d",&v);
    printf("input edge number:");
    scanf("%d",&e);
    if(v<1 || e < 1 || (e>(v*(v-1)))){
        printf("input error: invalid parameters\n");
        return NULL;
    }

    pG = (LGraph*)malloc(sizeof(LGraph));
    if(pG == NULL)
        return NULL;
    memset(pG,0,sizeof(LGraph));

    //初始化 边数 顶点数
    pG->vexnum = v;
    pG->edgenum = e;
    //初始化 邻接表的顶点
    for(i=0;i<pG->vexnum;i++){
        printf("vertex(%d)",i);
        pG->vexs[i].data = read_char();
        pG->vexs[i].first_edge = NULL;
    }

    //初始化""邻接表"的边
    for(i=0;i<pG->vexnum;i++){
        printf("edge(%d)",i);
        c1 = read_char();
        c2 = read_char();

        p1 = get_position(*pG,c1);
        p2 = get_position(*pG,c2);
        //init node1
        node1 = (ENode*)malloc(sizeof(ENode));
        node1->ivex = p2; //node1 为p2节点
        //将node1连接到p1所在链表的末尾
        if(pG->vexs[p1].first_edge == NULL){
            pG->vexs[p1].first_edge = node1;
            pG->vexs[p1].first_edge->next_edge = NULL;
        }
        else{
            link_last(pG->vexs[p1].first_edge,node1);
            pG->vexs[p1].first_edge->next_edge = NULL;
        }
    }
    return pG;
}

/*create linked table graph(used data)*/
LGraph* create_example_lgraph(){
    char c1,c2;
    char vexs[] = {'A','B','C','D','E','F','G'};
    char edges[][2] ={
        {'A','C'},
        {'A','D'},
        {'A','F'},
        {'B','C'},
        {'C','D'},
        {'E','G'},
        {'F','G'}};
    int vlen = LEN(vexs);
    int elen = LEN(edges);
    int i,p1,p2;
    ENode* node1,*node2;
    LGraph* pG;

    pG = (LGraph*)malloc(sizeof(LGraph));
    if(pG == NULL)  
        return NULL;
    memset(pG,0,sizeof(LGraph));

    //init 顶点数  边数
    pG->vexnum = vlen;
    pG->edgenum = elen;
    //init 邻接表的顶点
    for(i=0;i<pG->vexnum;i++){
        pG->vexs[i].data = vexs[i];
        pG->vexs[i].first_edge = NULL;
    }

    //init 邻接表的边
    for(i=0;i<pG->vexnum;i++){
        //读取边的起始顶点和结束顶点
        c1 = edges[i][0];
        c2 = edges[i][1];

        p1 = get_position(*pG,c1);
        p2 = get_position(*pG,c2);

        // init node1
        node1 = (ENode*)malloc(sizeof(ENode));
        node1->ivex = p2;
        if(pG->vexs[p1].first_edge == NULL){
            pG->vexs[p1].first_edge = node1;
            pG->vexs[p1].first_edge->next_edge = NULL;
        }
        else
            link_last(pG->vexs[p1].first_edge,node1);
    }
    return pG;
}

/*print linked tab graph*/
void print_graph(LGraph G){
    int i,j,k;
    ENode* node;
    printf("List Graph:\n");
    for(i=0;i<G.vexnum;i++){
        printf("%d(%c) ",i,G.vexs[i].data);//链表头结点
        node = G.vexs[i].first_edge;//first edge
        while(node){
            printf("%d(%c) ",node->ivex,G.vexs[node->ivex].data);
            node = node->next_edge;
        }
        printf("\n");
    }
}

int main(){
    LGraph* pG;
    pG = create_example_lgraph();
    print_graph(*pG);
    return 0;
}



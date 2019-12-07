/*c:邻接矩阵表示无向图*/

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define MAX 100
#define isLetter(a) ((((a)>='a')&&((a)<='z'))||(((a)>='A')&&((a)<='Z')))
#define LEN(a)   (sizeof(a)/sizeof(a[0]))

//邻接矩阵
typedef struct _grahp
{
    char vexs[MAX]; //vertex set
    int vexnum;   //vertex num
    int edgenum;  //edge num
    int matrix[MAX][MAX]; //adjacent matrix
}Graph, *PGraph;

/*return ch 在matrix中的位置*/
int get_position(Graph g, char ch){
    int i;
    for(i=0;i<g.vexnum;i++)
        if(g.vexs[i] == ch)
            return i;
    return -1;
}

/*read a input char*/
char read_char(){
    char ch;
    do{
        ch = getchar();
    }while(!isLetter(ch));

    return ch;
}

/*create a graph input by myself*/
Graph* create_graph(){
    char c1,c2;
    int v,e;
    int i,p1,p2;
    Graph* pG;
    printf("input vertex number:");
    scanf("%d",&v);
    printf("input edge number:");
    scanf("%d",&e);
    if(v<1 || e<1 ||(e>(v*(v-1)))){
        printf("input error: invalid parameters!\n");
        return NULL;
    }
    pG = (Graph*)malloc(sizeof(Graph));
    if( pG == NULL)
        return NULL;
    //initialize data
    memset(pG,0,sizeof(Graph));
    //初始化定点数 边数
    pG->vexnum = v;
    pG->edgenum = e;
    //初始化顶点
    for(i=0;i<pG->vexnum;i++){
        printf("vertex(%d): ",i);
        pG->vexs[i] = read_char();
    }
    //初始化边
    for(i=0;i<pG->edgenum;i++){
        printf("edge(%d):",i);
        // two different chars
        c1 = read_char();
        c2 = read_char();

        p1 = get_position(*pG,c1);
        p2 = get_position(*pG,c2);

        if(p1==-1||p2==-1){
            printf("input error: invalid edge!");
            free(pG);
            return NULL;
        }

        pG->matrix[p1][p2] = 1;
        pG->matrix[p2][p1] = 1;

    }
    return pG;
}

/*create graph using examples*/
Graph* create_example_graph(){
    char vexs[] = {'A','B','C','D','E','F','G'};//n个
    char edges[][2] = { //n rows 2 cols
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
    Graph* pG = (Graph*)malloc(sizeof(Graph));
    //输入顶点数 边数
    if(pG == NULL)
        return NULL;
    memset(pG,0,sizeof(Graph));

    //初始化顶点数和边数
    pG->vexnum = vlen;
    pG->edgenum = elen;
    //vertex
    for(i=0;i<vlen;i++){
        pG->vexs[i] = vexs[i];
    }
    //edge
    for(i=0;i<pG->edgenum;i++){
        p1 = get_position(*pG,edges[i][0]);
        p2 = get_position(*pG,edges[i][1]);

        pG->matrix[p1][p2] = 1;
        pG->matrix[p2][p1] = 1;
    }
    return pG;
}

/*返回顶点v的第一个邻接顶点的索引 失败则返回-1*/
static int first_vertex(Graph G,int v){
    int i;

    if(v<0||v>(G.vexnum-1))
        return -1;
    
    for(i=0;i< G.vexnum;i++){
        if(G.matrix[v][i] == 1)
            return i;
    }
    return -1;
}

/*返回顶点v相对于w的下一个邻接顶点的索引 失败返回-1*/
static int next_vetrix(Graph G,int v,int w){
    int i;
    if(v<0 || v>(G.vexnum-1)|| w<0 || w>(G.vexnum-1))
        return -1;
    
    for(i = w+1 ; i<G.vexnum ; i++){
        if(G.matrix[v][i] == 1)
            return i;
    }
    return -1;
}
/*
深度优先搜索遍历图的递归实现
*/
static void DFS(Graph g,int i,int *visited){
    int w;
    visited[i] = 1;
    printf("%c",g.vexs[i]);
    //遍历该顶点的所有邻接顶点 若没有访问过 继续往下走
    for(w= first_vertex(g,i);w>=0;w=next_vetrix(g,i,w)){
        if(!visited[w])
            DFS(g,w,visited);
    }
}
/*
DFS Traverse
*/
void DFSTraverse(Graph g){
    int i;
    int visited[MAX]; //顶点访问标记

    //初始化所有顶点都没有被访问
    for(i=0;i<g.vexnum;i++){
        visited[i] = 0;
    }
    printf("DFS: ");
    for(i = 0; i< g.vexnum ; i++){
        if(!visited[i])
            DFS(g,i,visited);
    }
    printf("\n");
}

/*广度优先搜索
use queue to search*/
void BFS(Graph g){
    int head = 0;
    int rear = 0;
    int queue[MAX];// 辅助队列
    int visited[MAX]; //顶点访问标记
    int i,j,k;

    for(i=0; i<g.vexnum;i++){
        visited[i] = 0;
    }

    printf("BFS:\n");
    for(i=0;i<g.vexnum;i++){
        if(!visited[i]){
            visited[i] = 1;
            printf("%c ",g.vexs[i]);
            queue[rear++] = i;
        }
        while( head!= rear){
            j = queue[head++]; // out queue
            for(k= first_vertex(g,j);k>=0;k= next_vetrix(g,j,k)){
                if(!visited[k]){
                    visited[k] = 1;
                    printf("%c ",g.vexs[k]);
                    queue[rear++] = k;
                }
            }
        }
    }
    printf("\n");
}

/*print the matrix*/
void print_graph(Graph G){
    int i,j,k;
    printf("Matrix Graph:\n");
    for(i=0;i<G.vexnum;i++){
        for(j=0;j<G.vexnum;j++)
            printf("%d ",G.matrix[i][j]);
        printf("\n");
    }
}

int main(){
    Graph * G;
    G = create_example_graph();
    // print_graph(*G);
    BFS(*G);

    DFSTraverse(*G);
    return 0;
}
/*邻接矩阵表示的有向图*/
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define MAX 100
#define isLetter(a) ((((a)>='a')&&((a)<='z'))||(((a)>='A')&&((a)<='Z')))
#define LEN(a)   (sizeof(a)/sizeof(a[0]))

typedef struct _graph{
    char vexs[MAX]; // 顶点集合
    int vexnum; //顶点数
    int edgenum; //边数
    int matrix[MAX][MAX];
}Graph, *PGraph;

/*返回ch在matrix矩阵的位置*/
static int get_position(Graph g,char ch){
    int i;
    for(i=0;i<g.vexnum;i++){
        if(g.vexs[i] == ch)
            return i;
    }
    return -1;
}

/*读入一个输入字符*/
static char read_char(){
    char ch;
    do{
        ch = getchar();
    }while(!isLetter(ch));
    return ch;
}

/*创建自己的图*/
Graph* create_graph(){
    char c1,c2;
    int v,e; // vertex and edge num
    int i,p1,p2;
    Graph* pG;
    //input vertex and edge num
    printf("input vertex number:");
    scanf("%d",&v);
    printf("input edge number:");
    scanf("%d",&e);
    if(v<1 || e<1 || (e>(v-1)*v)){
        printf("input error: invalid parameters!\n");
        return NULL;
    }

    pG = (Graph*)malloc(sizeof(Graph));
    if(pG == NULL)
        return NULL;
    memset(pG,0,sizeof(Graph));

    //init edge & vertex num
    pG->vexnum = v;
    pG->edgenum = e;
    //init vertex 
    for(i=0;i<pG->vexnum;i++){
        
        printf("vertex(%d):",i);
        pG->vexs[i] = read_char();
    }

    //init edge
    for(i=0;i<pG->vexnum;i++){
        //读取边的起始顶点和结束顶点
        printf("edge(%d)",i);
        c1 = read_char();
        c2 = read_char();

        p1 = get_position(*pG,c1);
        p2 = get_position(*pG,c2);

        if(p1 == -1 || p2 == -1){
            printf("input error:invalid edge!\n");
            free(pG);
            return NULL;
        }

        pG->matrix[p1][p2] = 1;
    }
    return pG;
}

Graph* create_example_graph(){
    char vexs[] = {'A','B','C','D','E','F','G'};
    char edges[][2] = {
        {'A','B'},
        {'B','C'},
        {'B','E'},
        {'B','F'},
        {'C','E'},
        {'D','C'},
        {'E','B'},
        {'E','D'},
        {'F','G'}
    };
    int vlen = LEN(vexs);
    int elen = LEN(edges);

    int i,p1,p2;
    Graph* pG;

    //输入 顶点数 边数
    pG = (Graph*)malloc(sizeof(Graph));
    if(pG == NULL){
        return NULL;
    }
    //INIT
    pG->vexnum = vlen;
    pG->edgenum = elen;

    //init vertex
    for(i=0;i<pG->vexnum;i++){
        pG->vexs[i] = vexs[i];
    }
    //init edges
    for(i=0;i<pG->vexnum;i++){
        p1 = get_position(*pG,edges[i][0]);
        p2 = get_position(*pG,edges[i][1]);

        pG->matrix[p1][p2] = 1;
    }
    return pG;
}

/*print matrix graph*/
void print_graph(Graph G){
    int i,j;
    printf("Matrix Graph:\n");
    for(i=0;i<G.vexnum;i++){
        for(j = 0;j<G.vexnum;j++){
            printf("%d ",G.matrix[i][j]);
        }
        printf("\n");
    }
}

int main(){
    Graph* g;
    g = create_example_graph();
    print_graph(*g);
    return 0;
}
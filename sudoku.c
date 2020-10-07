#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name)
{
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          fscanf (file, "%d", &n->sudo[i][j]);
       }
  }

  fclose (file);
  return n;
}


void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    int i,j,k,l,ii;

    //rows
    for(i=0;i<9;i++){
       int b[10]; for(ii=1;ii<10;ii++) b[ii]=0;
       for(j=0;j<9;j++){
         if( n->sudo[i][j]!= 0 && b[n->sudo[i][j]]==1) return 0;
         b[n->sudo[i][j]]=1;
       }
    }

    //cols
    for(j=0;j<9;j++){
       int b[10]; for(ii=1;ii<10;ii++) b[ii]=0;
       for(i=0;i<9;i++){
         if( n->sudo[i][j]!= 0 && b[n->sudo[i][j]]==1) return 0;
         b[n->sudo[i][j]]=1;
       }
    }

    //squares
    for(k=0;k<9;k++){
       int b[10]; for(ii=1;ii<10;ii++) b[ii]=0;
       for(l=0;l<9;l++){
           i=3*(k%3) + (l%3) ;
           j=3*(k/3) + (l/3) ;
         if( n->sudo[i][j]!= 0 && b[n->sudo[i][j]]==1) return 0;
         b[n->sudo[i][j]]=1;
       }
    }

    return 1;
}


List* get_adj_nodes(Node* n){
    int i, j, k;

    List* list=createList();
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
          if(n->sudo[i][j]==0){

            for(k=1; k<10; k++){
                n->sudo[i][j]=k;
                if(is_valid(n)){
                    Node* adj=copy(n);
                    pushBack(list,adj);
                }
            }
            n->sudo[i][j]=0;
            return list;
          }
        }
    }
    return list;
}


int is_final(Node* n){
    int i,j;

    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
          if(n->sudo[i][j]==0) return 0;

    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* S = createStack();
  push(S, initial);
  while(!is_empty(S)){
     Node* n= top(S); pop(S);
     (*cont)++;
     if(is_final(n)) return n;

     List* l=get_adj_nodes(n);

     Node* adj=first(l);

     while(adj){
        push(S,adj);
        adj=next(l);
     }
     free(n);
  }

  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/
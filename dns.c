#include "header.h"

//ar trebui sa elibereze lista de adrese pentru fiecare nod
//functioneaza doar pentru anumite exemple
void freeAddrListsFromTree(Tree *root){
  freeAddr(&((*root)->addr));
  Children p = (*root)->children;

  while(p){
    if((*root)->addr != NULL)
      freeAddr(&((*root)->addr));
    p = p->next;
  }
  p = (*root)->children;
  while(p){
    freeAddrListsFromTree(&p->child);
    p = p->next;
  }
}

//ar trebui sa stearga arborele
void delTree(Tree *root){

  Children p = (*root)->children;
  Children aux = p;
  (*root)->parent = NULL;


  while(p){
    aux = p->next;

    delTree(&p->child);
    free(p->child);
    p = aux;
  }
  free((*root)->children);
  free(*root);
}


int main(){
  Tree root = NULL;
  User user = NULL;

  root = makeTree("tree.in");
  user = makeUser("users.in");

  makeTreeOutFile(root);
  makeHierarchyOutFile(root);
  makeQueriesOutFile(root, user, "queries.in");
  freeUser(&user);

  //freeAddrListsFromTree(&root);
  //delTree(&root);

  return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>

#define BUFMAX 100000
#define BUF_NR 20

typedef struct address{
  int res_add;
  struct address *next;

}*Addr;

typedef struct children{
  struct tree *child;
  struct children *next;
}*Children;

typedef struct tree {
  int node_id, parent_id;
  Addr addr;
  Children children;
  struct tree* parent;
}*Tree;

typedef struct user{
  int user_id;
  int node_id;
  struct user *next;
}*User;

Addr initAddr(int value);
Addr addLastAddr(Addr head, int value);
int verificaDuplicat(Addr list1, int value);
Addr listCat(Addr list1, Addr list2);
int findAddr(Addr head, int adresa);
void printAddr(Addr head);
void printAddrInFile(Addr head);
void freeAddr(Addr *head);

Children initChildren();
Children addLastChildren(Children head, Tree child);
void freeChildren(Children *head);
Children childCat(Children list1, Children list2);
Children delChildren(Children head, int node_id_to_del);
Children changeParent(Children head, Tree new_parent);

Tree initTree(int parent_id, int node_id, Addr ip_addr);
Tree insertTree(Tree root, int node_id, int parent_id, Addr ip_addr);
void printParents(Tree root);
void printTreeCerinta1(Tree root);
void printTreeAddr(Tree root);
void initHierarchy(Tree node);
Tree makeTree(char *nume_fisier);
void returnTreeNode(Tree root, int node_id, Tree *node);
void printTrace(Tree node, int addr);
int delTreeNode(Tree root, int del_node);
void freeAddrListsFromTree(Tree *root);
void delTree(Tree *root);

void findParentInFile(int idToFind, char *nume, char *keep, int rand, int nr);
void sortFile(char *nume);
void makeTreeOutFile(Tree root);
void makeHierarchyOutFile(Tree root);
void makeQueriesOutFile(Tree root, User user, char *nume_fisier);
void queries(Tree root, User user, char *nume_fisier);

User initUser(int user_id, int node_id);
User addLastUser(User head, int user_id, int node_id);
int userServer(User head, int user_id);
User replaceNodeId(User head, int toReplace, int new_id);
void freeUser(User *head);
void printUser(User head);
User makeUser(char *nume_fisier);

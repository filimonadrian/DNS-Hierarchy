#include "header.h"

Tree initTree(int parent_id, int node_id, Addr ip_addr){
  Tree tree = malloc(sizeof(Tree));
  tree->node_id = node_id;
  tree->parent_id = parent_id;
  tree->children = NULL;
  tree->addr = ip_addr;

  return tree;
}

Tree insertTree(Tree root, int node_id, int parent_id, Addr ip_addr){
  Tree new = initTree(parent_id, node_id, ip_addr);
  if(root == NULL || parent_id < 0){
    return new;
  }
  Children p = root->children;
  Tree temp = root;

  //daca id-ul nodului este de fapt id-ul parintelui cautat se adauga aici
  if(temp->node_id == new->parent_id){
    temp->children = addLastChildren(temp->children, new);
    new->parent = temp;
    //dau lista de adrese a nodului si parintilor
    initHierarchy(new);
    return root;
  }
  while(p){
    if(p->child->node_id == parent_id){
      p->child->children = addLastChildren(p->child->children, new);
      new->parent = p->child;
      //dau lista de adrese a nodului si parintilor
      initHierarchy(new);
      return root;
    }
    p = p->next;
  }
  p = root->children;
  while(p){
    p->child = insertTree(p->child, node_id, parent_id, ip_addr);
    p = p->next;
  }

return root;
}

//plec de la nodul pe care il adaug
//merg pana la root si copiez adresele
//de jos in sus
//rezolvarea cerintei 2
void initHierarchy(Tree node){
  if(node->parent_id == -1)
    return;
  Tree temp_parent = node->parent;
  Tree temp_node = node;

  while(temp_parent->parent_id != -1){
    listCat(temp_parent->addr, temp_node->addr);
    temp_parent = temp_parent->parent;
    temp_node = temp_node->parent;
  }
  //temp_parent este acum parintele arborelui
  listCat(temp_parent->addr, temp_node->addr);
}

//returneaza node_id -ul parintelui nodului sters
int delTreeNode(Tree root, int del_node){
  Tree nodeToDel;
  //retin nodul pe care vreau sa il sterg
  returnTreeNode(root, del_node, &nodeToDel);
  if(nodeToDel == NULL)
    return -1;
  int parent_id = nodeToDel->parent_id;
  //p_children este lista de copii a tatalui
  Children p_children = nodeToDel->parent->children;
  //concatenez lista copiilor lui la cea a tatalui
  p_children = childCat(p_children, nodeToDel->children);
  //modific parent_id pentru fiecare fiu ce a fost concatenat
  p_children = changeParent(p_children, nodeToDel->parent);
  //sterg nodul din lista de copii a parintelui
  //practic am pus langa el copiii lui, dar acum il elimin
  p_children = delChildren(p_children, del_node);

  //freeChildren(&nodeToDel->children);
  //free(nodeToDel);

  return parent_id;
}
//afiseaza parintele si toti copiii
void printTreeCerinta1(Tree root){
  FILE *dest = fopen("tree.out", "a");
  if(dest == NULL){
    fprintf(stderr, "EROARE - deschidere tree.out(printTreeCerinta1)\n" );
    return;
  }

  fprintf(dest, "%d", root->node_id );
  if(root->children != NULL)
    fprintf(dest, " ");
  Children p = root->children;
  while(p){
    fprintf(dest, "%d", p->child->node_id);
    if(p->next != NULL)
      fprintf(dest, " ");
    p = p->next;
  }
  fprintf(dest, "\n");
  p = root->children;
  while(p){
    printTreeCerinta1(p->child);
    p = p->next;
  }
  fclose(dest);
}

//afiseaza nodul si adresele pe care le poate rezolva
void printTreeAddr(Tree root){
  FILE *dest = fopen("hierarchy.out", "a");
  if(dest == NULL){
    fprintf(stderr, "EROARE - deschidere hierarchy.out(printTreeAddr)\n");
    return;
  }

  fprintf(dest, "%d ", root->node_id );
  if(root->addr == NULL)
    return;
  Addr temp = root->addr;
  while(temp != NULL){
    fprintf(dest, "addr%d", temp->res_add);
    if(temp->next != NULL)
      fprintf(dest, " ");
    temp = temp->next;
  }

  Children p = root->children;
  fprintf(dest, "\n");
  p = root->children;
  while(p){
    printTreeAddr(p->child);
    p = p->next;
  }
  fclose(dest);
}

//citeste fisierul ordonat linie cu linie
//adauga valorile in arbore si il returneaza
Tree makeTree(char *nume_fisier){
  int parent_id = 0, node_id = 0, ip_addr = 0, c = 0;
  sortFile(nume_fisier);
  FILE *src = fopen("ord_tree", "r");
  char buffer [BUFMAX], *z;

  Addr adrese = NULL;
  Tree root = NULL;
  if (src == NULL)
    fprintf(stderr, "EROARE - deschidere ord_tree(makeTree)\n");
    else{
      //cat timp am linii in fisier
    while (fgets(buffer, BUFMAX, src) != NULL){
      c = 0;
      z = strtok(buffer, " ");
      //cat timp am cuvinte pe linie
      while(z != NULL){
        //daca este primul "cuvant" il iau ca id de nod
        if(c == 0)
          node_id = atoi(z);
        //daca este al doilea il iau ca parent_id
        if(c == 1){
          if(z[0] == 45)
            parent_id = -1;
            else
              parent_id = atoi(z);
          }
          //altfel este o adresa
        if(c > 2){
          ip_addr = atoi(z + 4);
          adrese = addLastAddr(adrese, ip_addr);
        }
        z = strtok(NULL, " ");
        c++;

      }
      root = insertTree(root, node_id, parent_id, adrese);
      adrese = NULL;
    }

fclose (src);
  }
  return root;
}


//primeste ca parametru id-ul nodului si returneaza nodul de tip tree
void returnTreeNode(Tree root, int node_id, Tree *node){
  if(root->node_id == node_id){
    (*node) = root;
    return;
  }

  Children p = root->children;

  while(p){
    if(p->child->node_id == node_id){
      (*node) = p->child;
      return;
    }
    returnTreeNode(p->child, node_id, node);
    p = p->next;
  }
}

//cauta cel mai apropiat nod ce contine adresa data
//afiseaza toate nodurile prin care trece
//adauga adresa in nod daca acesta nu o are
void printTrace(Tree node, int addr){
  FILE *dest = fopen("queries.out", "a");
  if(dest == NULL){
    fprintf(stderr, "EROARE - deschidere queries.out(printTrace)\n" );
    return;
  }
  if(node->parent_id == -1){
    fprintf(dest, "%d", node->node_id);
    fprintf(dest, "\n");
    fclose(dest);
    return;
  }
  Tree temp = node;
  //verific daca exista adresa il lista
  int check = findAddr(node->addr, addr);
  if(check == 0){
    fprintf(dest, "%d", node->node_id);
    fprintf(dest, "\n");
    fclose(dest);
    return;
  }
  //altfel inseamna ca check este 1
  while(check != 0){

    temp->addr = addLastAddr(temp->addr, addr);
    check = findAddr(temp->addr, addr);

    fprintf(dest, "%d", temp->node_id);
    if(temp->parent != 0 && check == 1)
      fprintf(dest, " ");
    if (temp->node_id == 0){
        fprintf(dest, "\n");
        fclose(dest);
      return;
    }
    temp = temp->parent;

  }

  fprintf(dest, "\n");
  fclose(dest);

}

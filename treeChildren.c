#include "header.h"

Children initChildren(Tree child){
  Children new = malloc(sizeof(Children));
  new->child = child;
  new->next = NULL;
  return new;
}

Children addLastChildren(Children head, Tree child){
  if(head == NULL){
    head = initChildren(child);
    return head;
  }

  Children new = initChildren(child);
  Children temp = head;

  while(temp->next != NULL){
    temp = temp->next;
  }
  new->next = NULL;
  temp->next = new;

  return head;
}
//concateneaza 2 liste de copii
//nu exista 2 servere cu acelasi id in ierarhie
Children childCat(Children list1, Children list2){
  Children temp = list2;
  while(temp != NULL){
    list1 = addLastChildren(list1, temp->child);
    temp = temp->next;
  }
  return list1;
}

Children delChildren(Children head, int node_id_to_del){
  Children temp = head;
  Children aux;
  if(temp->child->node_id == node_id_to_del){
    head = temp->next;
    //free(temp);
    return head;
  }

  while(temp->next){
    if(temp->next->child->node_id == node_id_to_del){
      aux = temp->next;
      temp->next = temp->next->next;
      aux->next = NULL;
      //free(aux);
      return head;
    }
    temp = temp->next;
  }
  return head;

}
//atribuie lista de copii unui alt parinte, dat ca parametru
Children changeParent(Children head, Tree new_parent){
  Children temp = head;
  while(temp){
    temp->child->parent_id = new_parent->node_id;
    temp->child->parent = new_parent;
    temp = temp->next;
  }
  return head;
}

void freeChildren(Children *head){
  if(head == NULL)
    return;
  Children current = *head;
  Children next;

  while(current != NULL){
    next = current->next;
    free(current);
    current = next;
  }
  head = NULL;
}

int existNext(Children head){
  if(head->next != NULL)
    return 1;
  return 0;
}

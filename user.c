#include "header.h"

User initUser(int user_id, int node_id){
  User user = malloc(sizeof(User));
  user->user_id = user_id;
  user->node_id = node_id;
  user->next = NULL;
  return user;
}

User addLastUser(User head, int user_id, int node_id){
  if(head == NULL){
    head = initUser(user_id, node_id);
    return head;
  }

  User new = initUser(user_id, node_id);
  User temp = head;

  while(temp->next != NULL){
    temp = temp->next;
  }
  new->next = NULL;
  temp->next = new;

  return head;
}

void freeUser(User *head){
  if(head == NULL)
    return;

  User current = *head;
  User next;

  while(current != NULL){
    next = current->next;
    free(current);
    current = next;
  }
  head = NULL;
}

void printUser(User head){
  if(head == NULL)
    return;
  User temp = head;
  while(temp){
    printf("%d %d\n", temp->user_id, temp->node_id);
    temp = temp->next;
  }
}
//returneaza serverul la care are acces un user
int userServer(User head, int user_id){
  User temp = head;
  while(temp){
    if(temp->user_id == user_id)
      return temp->node_id;
    temp = temp->next;
  }
  return -1;
}

User replaceNodeId(User head, int toReplace, int new_id){
  User temp = head;

  while(temp != NULL){
    if(temp->node_id == toReplace)
      temp->node_id = new_id;
    temp = temp->next;
  }
  return head;
}
//face lista de useri de la 0 =>citire si adaugare in lista
User makeUser(char *nume_fisier){
  int user_id = 0, node_id = 0, c = 0;
  FILE *src = fopen(nume_fisier, "r");
  char buffer[BUF_NR], *z;
  User head = NULL;
  if(src == NULL){
    fprintf(stderr, "NU se poate deschile al doilea parametru\n" );
  }
  fgets(buffer, BUF_NR, src);
  //int nr_useri = atoi(buffer);

  while (fgets(buffer, BUF_NR, src)){
    c = 0;
    z = strtok(buffer, " ");
    while (z != NULL){
      if(c == 0){
        user_id = atoi(z);
      }
      if(c == 1){
        node_id = atoi(z);
      }

    z = strtok(NULL, " ");
    c++;
    }
    head = addLastUser(head, user_id, node_id);
  }
  fclose(src);
  return head;
}

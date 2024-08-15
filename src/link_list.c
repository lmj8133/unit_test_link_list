#include "src/link_list.h"

void list_init_node(list_node_t *node)
{
    memset(node, 0, sizeof(list_node_t));
}

void far list_init(list_t *list)
{
    list->number_of_node = 0;
    list->end.val_of_insertion = ITEM_MAX_EXE_TIME;
    list->end.next = &list->end;
    list->end.prev = &list->end;
    list->end.owner = (void *)NULL;
    list->end.container = (void *)list;
}
 
uint16_t far list_insert(list_t *list, list_node_t *new_node)
{
    list_node_t *iterator;
   
    if(list->number_of_node >= SPM_TASK_NODE_TOTAL) return 0;
   
    for(iterator = &list->end;
        iterator->next->val_of_insertion <= new_node->val_of_insertion;
        iterator = iterator->next){}
   
    new_node->next = iterator->next;
    new_node->next->prev = new_node;
    new_node->prev = iterator;
    iterator->next = new_node;
 
    new_node->container = (void *)list;
 
    list->number_of_node++;
 
    return 1;
}

uint16_t list_get_number_of_node(list_t *list)
{
    return list->number_of_node;
}
 
uint8_t list_get_owner_of_node(list_node_t *node)
{
    return (*(uint8_t *)(node->owner));
}

void far list_remove_node(list_node_t *node_to_remove)
{
    list_t *list = (list_t *)node_to_remove->container;

    if (list == NULL) return;
 
    node_to_remove->next->prev = node_to_remove->prev;
    node_to_remove->prev->next = node_to_remove->next;
    node_to_remove->container = (void*)NULL;
 
    list->number_of_node--;
}
 
list_node_t* far list_shift(list_t *list)
{
    list_node_t *node_to_remove;
 
    if(!list->number_of_node) return NULL;
   
    node_to_remove = list->end.next;
    list_remove_node(node_to_remove);
    return node_to_remove;
}

bool list_return_true(void)
{
    return true;
}

bool list_return_false(void)
{
    return false;
}

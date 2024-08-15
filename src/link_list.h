#include "inc/types.h"
#include "inc/config.h"

#define ITEM_MAX_EXE_TIME 0xFFFFFFFFUL
#define SPM_TASK_NODE_TOTAL 20

typedef struct list_node_s{
    // public
    uint32_t val_of_insertion;
    void *owner;
    void *container;
 
    // private
    struct list_node_s *next;  // for spm main
    struct list_node_s *prev;  // for spm main
}list_node_t;

typedef struct list_s{
    uint16_t number_of_node; // total node
    list_node_t end;         // end node
}list_t;

void far list_init(list_t *list);
void list_init_node(list_node_t *node);
uint16_t far list_insert(list_t *list, list_node_t *new_node);
void far list_remove_node(list_node_t *node_to_remove);
list_node_t* far list_shift(list_t *list);

uint16_t list_get_number_of_node(list_t *list);
uint8_t list_get_owner_of_node(list_node_t *node);
 
bool list_return_true(void);
bool list_return_false(void);

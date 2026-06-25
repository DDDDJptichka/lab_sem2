#include <stdlib.h>

typedef struct Node{

    int value;
    struct Node *next;
    struct Node *prev;

}node_t;

int get(size_t index, node_t *head, int *error){

    node_t *curr = head;
    
    if (head == NULL){

        *error = 1;
        return 1;
    
    }

    for (size_t i = 0; (i < index); ++i){

        if (curr == NULL){
            
            *error = 1;
            return 1;
        
        }

        curr = curr->next;
    }

    if (curr == NULL){
        
        *error = 1;
        return 1;
    
    }

    *error = 0;
    return curr->value;

}

int insert_at(size_t index, int value, node_t **head){

    node_t *curr = *head;
    node_t *new_node = malloc(sizeof(node_t));
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->value = value;

    if ((curr == NULL) && (index != 0)){

        free(new_node);
        return 1;

    }

    if (index == 0){

        if (curr == NULL){

            *head = new_node;
            return 0;

        }

        new_node->next = *head;
        (*head)->prev = new_node;
        *head = new_node;
        return 0;

    }

    for (int i = 0; (i < index - 1) && (curr != NULL); ++i){

        curr = curr->next;

    }

    if (curr == NULL){

        free(new_node);
        return 1;

    }

    new_node->prev = curr;

    if (curr->next != NULL){

        curr->next->prev = new_node;
        new_node->next = curr->next;
        curr->next = new_node;

    }
    else{

        curr->next = new_node;

    }
    
    return 0;

}

int del(size_t index, node_t **head){

    if ((head == NULL) || (*head == NULL)){

        return 1;
        
    }

    node_t *curr = *head;

    if (index == 0){

        if ((*head)->next != NULL){

            *head = (*head)->next;
            (*head)->prev = NULL;
            free(curr);

            return 0;

        }

        free(curr);
        *head = NULL;
        return 0;

    }

    for (int i = 0; i < index; ++i){

        if (curr != NULL){

            curr = curr->next;

        }
        else{
        
            return 1;

        }
    }

    if (curr == NULL){

        return 1;
        
    }

    curr->prev->next = curr->next;

    if (curr->next != NULL){

        curr->next->prev = curr->prev;

    }

    free(curr);

    return 0;

}






//КОЛЬЦЕВОЙ ДВУСВЯЗНЫЙ

int c_get(size_t index, size_t size, node_t *head, int *error){

    if (head == NULL){

        *error = 1;
        return 1;

    }

    node_t *curr = head;

    for (size_t i = 0; i < index % size; ++i){

        curr = curr->next;

    }

    *error = 0;
    return curr->value;

}

int c_insert_at(size_t index, size_t size, int value, node_t **head) {
    
    if (head == NULL){

        return 1;
    
    }

    node_t *new_node = malloc(sizeof(node_t));
    new_node->value = value;

    // пустой список
    if (*head == NULL){

        if (size != 0) {
            
            free(new_node);
            return 1;
        
        }

        new_node->next = new_node;
        new_node->prev = new_node;
        *head = new_node;

        return 0;
    }

    // вставка в начало
    if (index == 0){

        new_node->prev = (*head)->prev;
        (*head)->prev->next = new_node;
        new_node->next = *head;
        (*head)->prev = new_node;
        *head = new_node;

        return 0;
    }

    // ищем узел перед местом вставки
    node_t *curr = *head;

    for (size_t i = 0; i < index - 1; ++i) {
        curr = curr->next;
    }

    new_node->prev = curr;
    new_node->next = curr->next;
    curr->next->prev = new_node;
    curr->next = new_node;

    return 0;
}

int c_del(size_t index, size_t size, node_t **head) {

    if (head == NULL || *head == NULL || size == 0){
        
        return 1;
    
    }

    if (index >= size) {
        return 1;
    }

    node_t *curr = *head;

    for (size_t i = 0; i < index; ++i){

        curr = curr->next;
    
    }

    // если в списке один элементы
    if (size == 1){
        
        free(curr);
        *head = NULL;
        
        return 0;
    }

    // связываем соседей удаляемого узла
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;

    // если удаляем голову, надо сдвинуть head
    if (curr == *head){

        *head = curr->next;

    }

    free(curr);

    return 0;
}



//ОЧЕРЕДЬ НА ДВУСВЯЗНОМ


int enqueue(int value, node_t **tail, node_t **head, int *error){

    node_t *new_node = malloc(sizeof(node_t));
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;

    if ((tail == NULL) || (head == NULL)){

        *error = 1;
        return 1;

    }

    if ((*head == NULL) && (*head == *tail)){

        *head = new_node;
        *tail = new_node;

        *error = 0;
        return 0;

    }

    new_node->next = *tail;
    (*tail)->prev = new_node;
    *tail = new_node;
    *error = 0;
    return 0;

}

int dequeue(node_t **head, node_t **tail, int *error){

    int val;

    if ((head == NULL) || (tail == NULL)){

        *error = 1;
        return 1;

    }

    if ((*head == NULL) && (*head == *tail)){

        *error = 0;
        return 0;

    }

    if (*head == *tail){

        val = (*head)->value;

        free(*head);
        *tail = NULL;
        *head = NULL;

        *error = 0;
        return val;

    }

    val = (*head)->value;

    node_t *new_head = (*head)->prev;
    new_head->next = NULL;

    free(*head);
    *head = new_head;

    *error = 0;
    return val;

}






// СТЕК НА ОДНОСВЯЗНОМ

typedef struct Snode{

    int value;
    struct Snode *next;

}snode_t;

int push(int value, snode_t **head, int *error){

    if (head == NULL){

        *error = 1;
        return 1;

    }

    snode_t *new_node = malloc(sizeof(snode_t));
    new_node->value = value;
    new_node->next = NULL;

    if (*head == NULL){

        *head = new_node;
        *error = 0;
        return 0;

    }

    new_node->next = *head;
    *head = new_node;
    *error = 0; 
    return 0;

}

int pop(snode_t **head, int *error){

    if ((head == NULL) || (*head == NULL)){

        *error = 1;
        return 1;

    }

    snode_t *new_head = (*head)->next;
    int value = (*head)->value;

    free(*head);
    *error = 0;
    
    *head = new_head;

    return value;

}





// ДЕК

int pop_back(node_t **head, node_t **tail, int *error){

    if ((head == NULL) || (*head == NULL)){

        *error = 1;
        return 1;

    }

    int value = (*tail)->value;

    if (*head == *tail){

        free(*tail);
        *head = NULL;
        *tail = NULL;

        *error = 0;
        return value;

    }

    node_t *new_tail = (*tail)->next;
    new_tail->prev = NULL;

    free(*tail);
    *tail = new_tail;

    *error = 0;
    return value;

}

int pop_front(node_t **head, node_t **tail, int *error){

    if ((head == NULL) || (*head == NULL)){

        *error = 1;
        return 1;

    }

    int value = (*head)->value;

    if (*head == *tail){

        free(*head);
        *head = NULL;
        *tail = NULL;

        *error = 0;
        return value;

    }

    node_t *new_head = (*head)->prev;
    new_head->next = NULL;

    free(*head);
    *head = new_head;

    *error = 0;
    return value;

}

int push_back(int value, node_t **head, node_t **tail){

    if ((head == NULL) || (tail == NULL)){

        return 1;

    }

    node_t *new_node = malloc(sizeof(node_t));
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (*tail == NULL){

        *tail = new_node;
        *head = new_node;

        return 0;

    }

    new_node->next = *tail;
    (*tail)->prev = new_node;
    *tail = new_node;

    return 0;

}

int push_front(int value, node_t **head, node_t **tail){

    if ((head == NULL) || (tail == NULL)){

        return 1;

    }

    node_t *new_node = malloc(sizeof(node_t));
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (*head == NULL){

        *head = new_node;
        *tail = new_node;

        return 0;

    }

    (*head)->next = new_node;
    new_node->prev = *head;
    *head = new_node;

    return 0;

}





// ДИНАМИЧЕСКИЙ МАССИВ


#include <stdlib.h>

typedef struct DynamicArray{

    int *data;
    size_t size;
    size_t capacity;

} DynamicArray;

int insert_att(DynamicArray *arr, size_t index, int item){

    if (arr == NULL){

        return 1;

    }

    if (index > arr->size){

        return 1;

    }

    if (arr->size >= arr->capacity){

        int *new_data = realloc(arr->data, (arr->capacity + arr->size) * sizeof(int));

        arr->data = new_data;
        arr->capacity += arr->size;

    }

    for (size_t i = arr->size; i > index; --i){

        arr->data[i] = arr->data[i - 1];

    }

    arr->data[index] = item;
    ++arr->size;

    return 0;

}

int dell(DynamicArray *arr, size_t index){

    if (arr == NULL){

        return 1;

    }

    if (index >= arr->size){

        return 1;

    }

    for (size_t i = index; i < arr->size - 1; ++i){

        arr->data[i] = arr->data[i + 1];

    }

    --arr->size;

    return 0;

}

int main(){

    return 0;

}
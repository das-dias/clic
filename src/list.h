#ifndef LIST_H
#define LIST_H

typedef struct 
{
  void* data;
} list_t;

#define list_init(var) {                \
  .data = &var                          \
}                                       \


#define array_list_init(var) {          \
    .data = var                         \
}                                       \

#endif // !LIST_H
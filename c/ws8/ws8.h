#include <stddef.h>

#define SUM_OF_OBJECT 3
#define SIZEOF_TYPE(type) (size_t) ((type *) 0 + 1 )
#define MAX2(a, b) (((a) > (b)) ? (a) : (b))
#define MAX3(a, b, C) (((a > b) && (a > c))? a : ((b > c) ? b : c ))

typedef struct {
    void *data;
    void (*Print)();
    void (*Add)();
    void (*Free)();
    
} object;

void CreateIntobject(object *objs, int input);
void CreateFloatObject(object *objs, float input);
void CreateStringobject(object *objs, char *str);

void PrintAllobjects(object *objs);
void AddToAllobjects(object *objs, int numberber);
void FreeAllobjects(object *objs);



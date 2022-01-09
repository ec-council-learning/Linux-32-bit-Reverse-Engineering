#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

struct object1 { //this shows up on heap first, hence the name object1
 char holder[64];
};

struct object2 { //this will be on the heap second and has a pointer, the int
 int (*object2)();
};

void var1()  //self explanatory, first variable
{
 printf("the first variable\n");
}

void var2()  //second variable
{
 printf("the second variable\n");
}

int main(int argc, char **argv)
{
 struct object1 *o;
 struct object2 *oo;

 o = malloc(sizeof(struct object1));  //memory allocation malloc is what allocates our space on the heap
 oo = malloc(sizeof(struct object2));
 oo->object2 = var2;  

 printf("object1 is at %p, object2 is at %p\n", o, oo);

 strcpy(o->holder, argv[1]);

 oo->object2();

}

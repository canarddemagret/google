#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct drone {
  int *objects;
  int x;
  int y;
};

struct customer{
  int *objects;
  int x;
  int y;
};

struct warehouse{
  int *objects;
  int x;
  int y;
};
  
  
struct map {
  int rows;
  int columns;
  int deadline;
  int maxLoad;
  
  int nDrones;
  int nWarehouses;
  int nCustomers;
  int nItems;
  
  int *itemWeigth;
  struct customer *C;
  struct warehouse *W;
  struct drone *D;

  int score;
};


struct map getMap(const char*);


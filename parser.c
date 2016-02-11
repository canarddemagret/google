#include "parser.h"


struct map getMap(const char* file) {
  struct map map;
  FILE *f = fopen(file,"r+");
  int cont = 1;
  int size,size2;

  
  fscanf(f,"%d %d %d %d %d\n",&map.rows,&map.columns,&map.nDrones,&map.deadline,&map.maxLoad);

  /** Items **/
  fscanf(f,"%d\n",&size);
  map.nItems=size;
  map.itemWeigth = malloc(sizeof(int)*size);
  for(int i=0;i<size;i++) {
    fscanf(f,"%d ",&map.itemWeigth[i]);
  }
  fscanf(f,"\n");


  
  /** Warehouses **/
  fscanf(f,"%d\n",&size2);
  map.nWarehouses = size2;
  map.W = malloc(sizeof(struct warehouse) * size);
  for(int i=0;i<size2;i++) {         //for warehouse

    fscanf(f,"%d %d\n",&map.W[i].x, &map.W[i].y);
    map.W[i].objects = malloc(sizeof(int) * size);
    
    for(int j=0;j<size;j++) {        //for objects
      fscanf(f,"%d ",&map.W[i].objects[j]);
    }
    fscanf(f,"\n");
  }

  
  map.D = malloc(sizeof(struct drone)*map.nDrones);
  for(int i=0;i<map.nDrones;i++) {
    map.D[i].objects = calloc(map.nItems*8,sizeof(char));
    map.D[i].x = map.W[0].x;
    map.D[i].y = map.W[0].y;
    map.D[i].isFree=1;
  }

  /** Customer **/
  fscanf(f,"%d\n",&map.nCustomers);
  map.C = malloc(sizeof(struct customer) * map.nCustomers);

  for(int i=0;i<map.nCustomers;i++) {
    map.C[i].objects = calloc(map.nItems*8,sizeof(char));
    map.C[i].weigth = 0;
    fscanf(f,"%d %d\n",&map.C[i].x,&map.C[i].y);
    
    int res;
    fscanf(f,"%d\n",&res);
    map.C[i].nbItems = res;
    
    for(int j=0;j<res;j++) {
      int pos;
      fscanf(f,"%d ",&pos);
      map.C[i].weigth += map.itemWeigth[pos];
      (map.C[i].objects[pos])++;
    }
  }
  return map;
}

void debug(struct map* map) {
  // printf("%d %d %d %d %d\n",map->rows,map->columns,map->nDrones,map->deadline,map->maxLoad);


  
  /* warehouse ok
  for(int i=0;i<map->nItems;i++)
    printf("%d ",map->W[9].objects[i]);
  */

  /*customer ok, except the 5 firsts */
  for(int i=0;i<map->nItems;i++) {
    if(map->C[5].objects[i] == 1) {
      printf("%d ",i);
    }
  }

  
  /*for(int i=0;i<map->nItems;i++) {
    printf("%d ",map->itemWeigth[i]);
    }*/
}


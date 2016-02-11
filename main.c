#include "parser.h"
#include <math.h>
#include <stdio.h>
#include <time.h>
char *tout;
int nbtot;

int rentableClient(struct map* map) {
  int best=-1;
  for(int i=0;i<map->nCustomers;i++) {
    if(map->C[i].nbItems == 1 ) {
      return i;
    }
  }
  
  for(int i=0;i<map->nCustomers;i++) {
    int min=map->nItems;
    if(map->C[i].weigth < map->maxLoad ) {
      if(min > map->C[i].weigth) {
	best = i;
      }
    }
  }
  if(best != -1) return best;

  for(int i=0;i<map->nCustomers;i++) {
    int min=map->nItems;
    if(min > map->C[i].weigth) {
      best = i;
    }
  }

  return best;
}

int dist(int x1, int y1, int x2, int y2) {
  double res;
  res = (x1-x2)*(x1-x2) + (y1-y2)*(y1*y2);
  res = sqrt(res);
  return (int) ceil(res);
}

void LancerOrdre(struct map *map,int client, int drone) {
  int tactuel[map->C[client].nbItems];
  int tbest[map->C[client].nbItems];
  int freeWeigth;
  int n;
  int bestn=0;
  for(int i=0;i<map->C[client].nbItems;i++) {
    freeWeigth = map->maxLoad;
    n=0;
    for(int j=0;j<map->nItems;j++) {
      if(map->C[client].objects[j] != 0) {
	if( rand() > map->itemWeigth[j]/(freeWeigth*1.0)) {
	  tactuel[n]=j;
	  freeWeigth-=map->itemWeigth[j];
	  n++;
	}
      }
    }
    if(n > bestn) {
      memcpy(tbest,tactuel,sizeof(tactuel));
      bestn=n;
    }
  }
  for(int i=0;i<bestn;i++) {
    
    for(int j=0;j<map->nWarehouses;j++) {
      if(map->W[j].objects[tbest[i]]) {
	printf("%d L %d %d %d\n",&tout,drone,j,tbest[i],1);
	nbtot++;
	map->D[drone].time+= dist(map->D[drone].x,map->D[drone].y,map->W[j].x,map->W[j].y)+1;
	map->W[j].objects[tbest[i]]--;
	map->C[client].nbItems--;
	map->C[client].nbItems-=map->itemWeigth[tbest[i]];
	map->C[client].objects[tbest[i]]--;
	j=map->nWarehouses+1;
	
      }
    }
  }

  
  for(int i=0;i<bestn;i++) {
    printf("%d D %d %d %d\n",drone,client,tbest[i],1);
    nbtot++;
    map->D[drone].time+= dist(map->D[drone].x,map->D[drone].y,map->C[i].x,map->C[i].y)+1;
  }
    
}


void IA(struct map* map) {
  int turn = map->deadline;
  while(turn>0) {
    
    for(int i = 0; i<map->nDrones; i++) {
      if(map->D[i].isFree == 1) {
	int bestclient = rentableClient(map);
	LancerOrdre(map,bestclient,i);
      }
    }

    for(int i = 0; i<map->nDrones; i++) {
      map->D[i].time--;
      if(map->D[i].time ==0 )
	map->D[i].isFree = 1;
    }  

    turn--;
  }
}


int main(int argc, char **argv) {
  nbtot = 0;
  srand(time(NULL));
  struct map* map= malloc(sizeof(map));
  //*map=getMap("./redundancy.in");
  *map = getMap(argv[1]);
  IA(map);
  //debug(map);
  return 0;
}

#include "parser.h"



int main(int argc, char **argv) {
  struct map* map= malloc(sizeof(map));
  //*map=getMap("./redundancy.in");
  *map = getMap(argv[1]);
  //debug(map);
  return 0;
}

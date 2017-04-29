#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"
#include "dijkstra.h"

void cli_dijkstra(char *cmdline, int *pos) {
  int i, total_vertices;
  char s[BUFSIZE];
  vertexid_t *vertices;

  memset(s, 0, BUFSIZE);
  nextarg(cmdline, pos, " ", s);
  if (strlen(s) == 0) {
    printf("Missing start vertex id\n");
    return;
  }
  i = atoi(s);
  
  total_vertices = find_number_of_vertices(current);
  vertices = get_vertices(current);
  dijkstra(current, vertices, i, total_vertices);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <ctype.h>
#include "graph.h"


int find_number_of_vertices(graph_t g) {
  int total_vertices = 0;

  for (vertex_t v = g->v; v != NULL; v = v->next)
    total_vertices++;

  return total_vertices;
}

vertexid_t *get_vertices(graph_t g) {
  int total_vertices, count = 0;
  vertexid_t *ids;

  total_vertices = find_number_of_vertices(g);
  ids = malloc(sizeof(vertexid_t) * total_vertices);

  for (vertex_t v = g->v; v != NULL; v = v->next)
    ids[count++] = v->id;

  return ids;
}

int get_min_vertex(int *distances, int *visited, int total_vertices) {
  int min = INT_MAX, index = -1;

  for (int i = 0; i < total_vertices; i++) {
    if (visited[i] == 0 && min > distances[i]) {
      min = distances[i];
      index = i;
    }
  }
  
  return index;
}

int get_edge_weight(tuple_t t, enum_list_t el) {
  
  attribute_t attr;
  int offset, val, weight, j;
  float fval;
  char *s;
  double dval;

  assert (t != NULL);
  assert (t->buf != NULL);

  attr = t->s->attrlist;
  offset = tuple_get_offset(t, attr->name);
  
  if (offset >= 0) {
    switch (attr->bt) {
    case CHARACTER:
      weight = tuple_get_char(t->buf + offset);
      break;

    case VARCHAR:
      //printf("\"%s\"",
        //(char *) (t->buf + offset));
      s = (char *) (t->buf + offset);
      j = 0, weight = 0;
      while (s[j] != '\0') {
        weight += tolower(s[j]) - 'a';
        j++;
      }
      break;

    case BOOLEAN:
      if ((val = tuple_get_bool(t->buf + offset)) == 0)
        weight = 1;
      else
        weight = 2;
      break;

    case ENUM:
      //tuple_print_enum(t, offset, el);
      weight = 1;
      break;

    case INTEGER:
      weight = tuple_get_int(t->buf + offset);
      break;

    case FLOAT:
      fval = tuple_get_float(t->buf + offset);
      weight = (int) fval;
      break;

    case DOUBLE:
      dval = tuple_get_double(t->buf + offset);
      weight = (int) dval;
      break;

    case DATE:
    {
      /*char s[base_types_len[DATE] + 1];

      memset(s, 0,
        base_types_len[DATE] + 1);
        tuple_get_date(t->buf + offset, s);
        printf("%s", s);
        NOT ACTUALLY IMPLEMENTED YET*/ 
      weight = 1;
    }
      break;

    case TIME:
    {
        /*char s[base_types_len[TIME] + 1];

        memset(s, 0,
          base_types_len[TIME] + 1);
        tuple_get_time(t->buf + offset, s);
        printf("%s", s);
        NOT ACTUALLY IMPLEMENTED YET*/
      weight = 1;
    }
      break;

      case BASE_TYPES_MAX:
        weight = 1;
        break;
      }
    }
  else {
    weight = 1;
  }

  return weight;
}

void print_distances(int *distances, int total_vertices, vertexid_t start, vertexid_t *vertices) {
  printf("Distances from node %llu:\n", start);
  
  for (int i = 0; i < total_vertices; i++)
    printf("Node %llu: %d ", vertices[i], distances[i]);

  printf("\n");
}

void dijkstra(graph_t g, vertexid_t *vertices,vertexid_t start, int total_vertices) {
  int distances[total_vertices], visited[total_vertices];
  edge_t e;

  for (int i = 0; i < total_vertices; i++) {
    distances[i] = INT_MAX;
    visited[i] = 0;
    if (vertices[i] == start)
      distances[i] = 0;
  }
      
  for (int i = 0; i < total_vertices; i++) {
    int min = get_min_vertex(distances, visited, total_vertices);
    visited[min] = 1;

    for (int j = 0; j < total_vertices; j++) {
      if (min == j) {
        continue;
      }
      else if ((e = graph_find_edge_by_ids(g, vertices[min], vertices[j]))) {
        int u = min;
        int v = j;
        int w = get_edge_weight(e->tuple, g->el); 
        
        if (distances[u] != INT_MAX && distances[v] > distances[u] + w) 
          distances[v] = distances[u] + w;
      }
    }
  }

  print_distances(distances, total_vertices, start, vertices);
}





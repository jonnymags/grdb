#ifndef __DIJKSTRA_H
#define __DIJKSTRA_H

#include "graph.h"

int find_number_of_vertices(graph_t g);
vertexid_t *get_vertices(graph_t g);
int get_min_vertex(int *distances, int *visited, int total_vertices);
int get_edge_weight(tuple_t t, enum_list_t el);
void print_distances(int *distances, int total_vertices, vertexid_t start, vertexid_t *vertices);
void dijkstra(graph_t g, vertexid_t *vertices, vertexid_t start, int total_vertices);

#endif

#ifndef OSM_PARSER_H
#define OSM_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "L_Graph.h"
#include "M_Graph.h"

typedef struct xml_node_t
{
    long id;
    double lon;
    double lat;
    int index;
}xml_node_t;

typedef struct xml_way_t
{
    char* name;
    xml_node_t* refs;
}xml_way_t;

long getID(xmlNode* cur);

double getLat(xmlNode* cur);

double getLon(xmlNode* cur);

void print_element_names(xmlNode * a_node);

void getAllNodes(xmlDoc* doc);

#endif

#ifndef OSM_PARSER_H
#define OSM_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/HTMLparser.h>
#include "L_Graph.h"
#include "M_Graph.h"
#include "uthash.h"

typedef struct xml_node_t
{
    long id;
    double lon;
    double lat;
}xml_node_t;

typedef struct xml_node_hash_table
{
    xml_node_t node;
    UT_hash_handle hh;
}xml_node_hash_table;

typedef struct xml_way_t
{
    long id;
    long* ref;
}xml_way_t;

xmlDocPtr getdoc (char *docname);

long getID(xmlNode* cur);

double getLat(xmlNode* cur);

double getLon(xmlNode* cur);

xmlXPathObjectPtr getnodeset (xmlDocPtr doc, xmlChar *xpath);

void getAllNodes(xmlDocPtr doc, xml_node_t** nodes, int* nb);

void getAllWay(xmlDoc* doc, xml_way_t** ways, int *nb);

void print_element_names(xmlNode * a_node);


#endif

#ifndef OSM_PARSER_H
#define OSM_PARSER_H

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#include "uthash.h"

typedef struct xml_node_t
{
    const char* id;
    const char* lon;
    const char* lat;
}xml_node_t;

typedef struct xml_node_ht
{
    const char* ref;
    int index;
    UT_hash_handle hh;
}xml_node_ht;


typedef struct xml_way_t
{
    const char* id;
    const char** ref;
    int nb_ref;
}xml_way_t;

xmlDocPtr getdoc (char *docname);

const char* getID(xmlNode* cur);

const char* getLat(xmlNode* cur);

const char* getLon(xmlNode* cur);

xmlXPathObjectPtr getnodeset (xmlDocPtr doc, xmlChar *xpath);

void getAllNodes(xmlDocPtr doc, xml_node_t** nodes, int* nb);

void getAllWay(xmlDoc* doc, xml_way_t** ways, int *nb);

double deg2rad(double deg);

double rad2deg(double rad);

double distance(xml_node_t x, xml_node_t y);


#endif
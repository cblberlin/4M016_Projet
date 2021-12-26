#include "osm_parser.h"

long getID(xmlNode* cur)
{
    long id = atol( (const char *) xmlGetProp(cur, (const xmlChar *) "id" ));
    return id;
}

double getLat(xmlNode* cur)
{
    char* ptr;
    double lat = strtod( (const char *) xmlGetProp(cur, (const xmlChar *) "lat" ), &ptr);
    return lat;
}

double getLon(xmlNode* cur)
{
    char* ptr;
    double lon = strtod( (const char *) xmlGetProp(cur, (const xmlChar *) "lon" ), &ptr);
    return lon;
}

void print_element_names(xmlNode * a_node)
{
    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) 
        {
            if(!(xmlStrcmp ( cur_node->name, ( const xmlChar * ) "node" )))
            {
                printf("node type: Element, name: %s ID is %ld\n", cur_node->name, getID(cur_node));
                //printf("node type: Element, name: %s ID is %ld\n", cur_node->name, xmlGetProp(cur_node, (const xmlChar *) "id"));
                printf("His latitude is %lf his lontitude is %lf\n", getLat(cur_node), getLon(cur_node));
            }
        }

        print_element_names(cur_node->children);
    }
}
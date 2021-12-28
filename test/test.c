#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
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
    UT_hash_handle hh;
}xml_node_ht;


typedef struct xml_way_t
{
    const char* id;
    const char** ref;
    int nb_ref;
}xml_way_t;

const char* getID(xmlNode* cur)
{
    const char* id = (const char *) xmlGetProp(cur, (const xmlChar *) "id" );
    return id;
}

const char* getLat(xmlNode* cur)
{
    const char* lat = (const char *) xmlGetProp(cur, (const xmlChar *) "lat" );
    return lat;
}

const char* getLon(xmlNode* cur)
{
    const char* lon = (const char *) xmlGetProp(cur, (const xmlChar *) "lon" );
    return lon;
}

xmlDocPtr
getdoc (char *docname) {
	xmlDocPtr doc;
	doc = xmlParseFile(docname);
	
	if (doc == NULL ) {
		fprintf(stderr,"Document not parsed successfully. \n");
		return NULL;
	}

	return doc;
}


xmlXPathObjectPtr getnodeset (xmlDocPtr doc, xmlChar *xpath)
{

    xmlXPathContextPtr context;
    xmlXPathObjectPtr result;

    context = xmlXPathNewContext(doc);

    if (context == NULL) {
        printf("Error in xmlXPathNewContext\n");
        return NULL;
    }

    result = xmlXPathEvalExpression(xpath, context);
    xmlXPathFreeContext(context);

    if (result == NULL) {
        printf("Error in xmlXPathEvalExpression\n");
        return NULL;
    }

    if(xmlXPathNodeSetIsEmpty(result->nodesetval)){
        xmlXPathFreeObject(result);
                printf("No result\n");
        return NULL;
    }

    return result;
}

void getAllNodes(xmlDocPtr doc, xml_node_t** nodes, int* nb)
{
    xmlChar* xpath = (xmlChar *) ("/osm/node");
    xmlXPathObjectPtr result;
    result = getnodeset(doc, xpath);
    xmlNodeSetPtr nodeset;
    //nb = (int *) malloc(sizeof(int));
    *nb = 0;
    if(result)
    {

        nodeset = result->nodesetval;
        nodes[0] = (xml_node_t *) malloc(sizeof(xml_node_t) * result->nodesetval->nodeNr);
        printf("size of node is %d\n", nodeset->nodeNr);
        for(int i = 0; i < nodeset->nodeNr; i++)
        {
            //printf("node id is: %s\n", xmlGetProp(nodeset->nodeTab[i], BAD_CAST "id"));
            
            xmlNodePtr cur = nodeset->nodeTab[i];
            
                if(cur->type == XML_ELEMENT_NODE)
                {
                    
                    //if(!(xmlStrcmp(cur->name, BAD_CAST "node")))
                    if(!(xmlStrcmp ( cur->name, ( const xmlChar * ) "node" )))
                    {
                        //printf("cur name is %s\n", cur->name);
                        nodes[0][i].id = getID(cur);
                        nodes[0][i].lat = getLat(cur);
                        nodes[0][i].lon = getLon(cur);
                        //printf("id is %ld\n", nodes[0][i].id);
  
                        (*nb)++;                 
                    }
                }
                //cur = cur->next;
            
        }
        xmlXPathFreeObject (result);
    }
}

void getAllWay(xmlDoc* doc, xml_way_t** ways, int *nb)
{
    xmlChar *xpath = (xmlChar*) ("/osm/way[tag/@k='highway']");
	xmlNodeSetPtr nodeset;
	xmlXPathObjectPtr result;
	int i;

    result = getnodeset(doc, xpath);


    if(result)
    {
        nodeset = result->nodesetval;
        ways[0] = (xml_way_t *) malloc(sizeof(xml_way_t) * result->nodesetval->nodeNr);

        nodeset = result->nodesetval;

        for(i = 0; i < nodeset->nodeNr; i++)
        {
            xmlNodePtr cur = nodeset->nodeTab[i]->children;
            ways[0][i].id = (const char *) malloc(sizeof(const char));
            ways[0][i].id = getID(nodeset->nodeTab[i]);
            ways[0][i].ref = (const char **) malloc(sizeof(const char *));

            ways[0][i].nb_ref = 0;

            printf("before while i = %d ways[0][%d].nb_ref = %d\n", i, i, ways[0][i].nb_ref);
            while(cur != NULL)
            {
                if(cur->type == XML_ELEMENT_NODE)
                {
                    if(!(xmlStrcmp(cur->name, BAD_CAST "nd")))
                    {
                        /* //printf("check for i = %d\n", i);
                        ways[0][i].ref[ ways[0][i].nb_ref ] = (const char *) xmlGetProp(cur, BAD_CAST "ref");
                        ways[0][i].ref = realloc(ways[0][i].ref, sizeof(const char **) * ways[0][i].nb_ref +2);
                        printf("check for realloc size of %d\n", ways[0][i].nb_ref + 2);
                        ways[0][i].ref[ways[0][i].nb_ref++] = (const char *) malloc(sizeof(const char));
                        
                        printf("check for i = %d, ways[0][%d].nb_ref = %d\n", i, i, ways[0][i].nb_ref); */
                        ways[0][i].ref[ ways[0][i].nb_ref ] = (const char *) malloc(sizeof(const char)); 
                        ways[0][i].ref[ ways[0][i].nb_ref ] = (const char *) xmlGetProp(cur, BAD_CAST "ref");
                        printf("\tcheck for i = %d ways[0][%d].nb_ref = %d\n", i, i, ways[0][i].nb_ref);
                        ways[0][i].ref = realloc(ways[0][i].ref, sizeof(const char *) * (ways[0][i].nb_ref + 2));
                        ways[0][i].nb_ref++;
                    }
                }
                
                cur = cur->next;
            }
            printf("\tafter while i = %d cnt_ref = %d\n\n", i,  ways[0][i].nb_ref);
            (*nb)++;
        }
    }
    xmlXPathFreeObject (result);
}

int
main(int argc, char **argv) {

	char *docname;
	xmlDocPtr doc;

		
	if (argc <= 1) {
		printf("Usage: %s docname\n", argv[0]);
		return(0);
	}

	docname = argv[1];
	doc = getdoc(docname);

    xml_node_t** nodes = (xml_node_t **) malloc(sizeof(xml_node_t*));
    nodes[0] = (xml_node_t *) malloc(sizeof(xml_node_t));
    int nb_node;
    getAllNodes(doc, nodes, &nb_node);

    printf("check for get Nodes, %d\n", nb_node);

    /* for(int i = 0; i < nb_node; i++)
    {
        printf("the node id is %s\n", nodes[0][i].id);
        printf("His latitude is %s his lontitude is %s\n", nodes[0][i].lat, nodes[0][i].lon);
    } */

    xml_way_t** ways = (xml_way_t **) malloc(sizeof(xml_way_t*));

    int nb_way = 0;
    //int *nb_ref = malloc(sizeof(int *) * nb_way);
    getAllWay(doc, ways, &nb_way);

    printf("\n\ncheck get ways started, way nb is %d\n", nb_way);

    for(int i = 0; i < nb_way; i++)
    {
        printf("way id is %s, nb of ref is %d\n", ways[0][i].id, ways[0][i].nb_ref);
        for(int j = 0; j < ways[0][i].nb_ref; j++)
        {
            printf("\t the ref is %s\n", ways[0][i].ref[j]);
        }
    }

    printf("\n\ncheck get ways completd\n");


 
    printf("\n\ncheck hash table\n");

    xml_node_ht l, node, *xml_node_hashtable = NULL;
    for(int i = 0; i < nb_way; i++)
    {
        node = (record_t *)malloc(sizeof *r);

        memset(r, 0, sizeof *r);
        node.ref = nodes[0][i].id;
        HASH_ADD(hh, ref, )
    }
    
    free(nodes);
	xmlFreeDoc(doc);
	xmlCleanupParser();

	return (1);
}
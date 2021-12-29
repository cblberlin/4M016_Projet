#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "osm_parser.h"

#define pi 3.14159265358979323846

xmlDocPtr getdoc (char *docname) {
	xmlDocPtr doc;
	doc = xmlParseFile(docname);
	
	if (doc == NULL ) {
		fprintf(stderr,"Document not parsed successfully. \n");
		return NULL;
	}

	return doc;
}

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
        //printf("size of node is %d\n", nodeset->nodeNr);
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

            //printf("before while i = %d ways[0][%d].nb_ref = %d\n", i, i, ways[0][i].nb_ref);
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
                        //printf("\tcheck for i = %d ways[0][%d].nb_ref = %d\n", i, i, ways[0][i].nb_ref);
                        ways[0][i].ref = realloc(ways[0][i].ref, sizeof(const char *) * (ways[0][i].nb_ref + 2));
                        ways[0][i].nb_ref++;
                    }
                }
                
                cur = cur->next;
            }
            //printf("\tafter while i = %d cnt_ref = %d\n\n", i,  ways[0][i].nb_ref);
            (*nb)++;
        }
    }
    xmlXPathFreeObject (result);
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This function converts decimal degrees to radians             :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double deg2rad(double deg) {
    return (deg * pi / 180);
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This function converts radians to decimal degrees             :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double rad2deg(double rad) {
    return (rad * 180 / pi);
}
double distance(xml_node_t x, xml_node_t y) {
    double theta, dist;

    char* ptr;
    double lat1 = strtod( x.lat , &ptr);
    double lat2 = strtod( y.lat , &ptr);
    double lon1 = strtod( x.lon , &ptr);
    double lon2 = strtod( y.lon , &ptr);

    if ((lat1 == lat2) && (lon1 == lon2)) {
        return 0;
    }
    else {
        theta = lon1 - lon2;
        dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
        dist = acos(dist);
        dist = rad2deg(dist);
        dist = dist * 60 * 1.1515;
        
        return (dist);
    }
}
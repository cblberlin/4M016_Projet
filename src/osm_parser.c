#include "osm_parser.h"

xml_node_t* nodes;

int nb_vertex = 0;

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
                //xmlChar* buff = xmlNodeGetContent(cur_node);
                //printf("%s\n", buff);

            }
        }
        print_element_names(cur_node->children);
    }
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

void getAllNodes(xmlNode * a_node)
{
    xmlNode *cur_node = NULL;
    //nodes = realloc(nodes, sizeof(xml_node_t) * cnt);
    //printf("test\n");
    nodes = realloc(nodes, nb_vertex++);
    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        //printf("node name is %s\n", cur_node->name);
        if (cur_node->type == XML_ELEMENT_NODE) 
        {
            if(!(xmlStrcmp ( cur_node->name, ( const xmlChar * ) "node" )))
            {
                nodes[nb_vertex - 1].id = getID(cur_node);
                nodes[nb_vertex - 1].lat = getLat(cur_node);
                nodes[nb_vertex - 1].lon = getLon(cur_node);
                
                nb_vertex++;

            }
        }
        getAllNodes(cur_node->children);
    }
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
            ways[0][i].id = getID(nodeset->nodeTab[i]);
            ways[0][i].ref = (long *) malloc(sizeof(long));
            while(cur != NULL)
            {
                if(cur->type == XML_ELEMENT_NODE)
                {
                    int cnt_ref = 1;
                    if(!(xmlStrcmp(cur->name, BAD_CAST "nd")))
                    {
                        ways[0][i].ref[cnt_ref - 1] = atol((const char *) xmlGetProp(cur, BAD_CAST "ref"));
                        cnt_ref++;
                        ways[0][i].ref = realloc(ways[0][i].ref, sizeof(long) * cnt_ref);
                    }
                }
                cur = cur->next;
            }
            (*nb)++;
        }
    }
    xmlXPathFreeObject (result);
}
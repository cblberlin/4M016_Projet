#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>

typedef struct xml_node_t
{
    long id;
    double lon;
    double lat;
}xml_node_t;


typedef struct xml_way_t
{
    long id;
    long* ref;
}xml_way_t;

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

int
main(int argc, char **argv) {

	char *docname;
	xmlDocPtr doc;
	xmlChar *xpath = (xmlChar*) ("/osm/way[tag/@k='highway']");
	xmlNodeSetPtr nodeset;
	xmlXPathObjectPtr result;
	int i;
	xmlChar *keyword;
		
	if (argc <= 1) {
		printf("Usage: %s docname\n", argv[0]);
		return(0);
	}

	docname = argv[1];
	doc = getdoc(docname);

    // print all nodes information
    xmlNode *root_element = NULL;
    root_element = xmlDocGetRootElement(doc);
    print_element_names(root_element);

    // print all ways information
	result = getnodeset (doc, xpath);
	if (result) {
		nodeset = result->nodesetval;
		for (i=0; i < nodeset->nodeNr; i++) {
            printf("way id: %s\n", xmlGetProp( nodeset->nodeTab[i], BAD_CAST "id" ));
            xmlNodePtr cur = nodeset->nodeTab[i]->children;
            while(cur != NULL)
            {
                if (cur->type == XML_ELEMENT_NODE) 
                {   
                    //printf("\t%s", cur->name);
                    if (!(xmlStrcmp(cur->name, BAD_CAST "nd")))
                    {
                        keyword = xmlGetProp(cur, BAD_CAST "ref");
                        printf("\tref is %s\n", keyword);
                    }
                    //cur = cur->next;
                }
                cur = cur->next;
            }
			//keyword = xmlGetProp(nodeset->nodeTab[i], BAD_CAST "ref");
		    //printf("keyword: %s\n", keyword);
		    //xmlFree(keyword);
		}
		xmlXPathFreeObject (result);
	}
	xmlFreeDoc(doc);
	xmlCleanupParser();
	return (1);
}
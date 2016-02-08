/**
 * section: Parsing
 * synopsis: Parse an XML file to a tree and free it
 * purpose: Demonstrate the use of xmlReadFile() to read an XML file
 *          into a tree and and xmlFreeDoc() to free the resulting tree
 * usage: parse1 test1.xml
 * test: parse1 test1.xml
 * author: Daniel Veillard
 * copy: see Copyright for the status of this software.
 */

#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>


int main(int argc, char **argv) {
    if (argc != 2)
        return(1);

    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    xmlDocPtr doc;
    xmlNodePtr cur;

    doc = xmlParseFile(argv[1]);
    if(doc==NULL){
      fprintf(stderr,"Erreur parse\n");
      return 1;
    }

    cur = xmlDocGetRootElement(doc);

    if(cur == NULL){
      fprintf(stderr,"Erreur tree\n");
      return 2;
    }

    printf("root = %s\n",cur->name);

    /*
     * Cleanup function for the XML library.
     */
    xmlCleanupParser();
    /*
     * this is to debug memory for regression tests
     */
    xmlMemoryDump();
    return(0);
}

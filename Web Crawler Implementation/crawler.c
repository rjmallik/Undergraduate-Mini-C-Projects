#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "crawler.h"
#include "pagedir.h"
#include "bag.h"
#include "hashtable.h"



static void crawl(char *seedURL, char *pageDirectory, const int maxDepth) {
    hashtable_t *pages_seen = hashtable_new(500);
    bag_t *pages_to_crawl = bag_new();

	static int docID = 1;

    webpage_t *seedPage = webpage_new(seedURL, 0); 
    bag_insert(pages_to_crawl, seedPage);

    while (!bag_is_empty(pages_to_crawl)) {
        webpage_t *page = bag_extract(pages_to_crawl);

        if (page->depth <= maxDepth) {
            pagedir_save(page, pageDirectory, docID);
        }

        int pos = 0;
        char *url = NULL;
        while ((pos = webpage_getNextURL(page, pos, &url)) > 0) {
            if (IsInternalURL(url)) {
                if (hashtable_insert(pages_seen, url, "")) {
                    webpage_t *newPage = webpage_new(url, page->depth + 1);
                    bag_insert(pages_to_crawl, newPage);
                }
            }
            free(url);
        }

        webpage_delete(page);
    }

    hashtable_delete(pages_seen, NULL);
    bag_delete(pages_to_crawl); 
}

extern void parseArgs(int argc, char *argv[], char **seedURL, char **pageDirectory, int *maxDepth);

int main(int argc, char *argv[]) {
    char *seedURL = NULL;
    char *pageDirectory = NULL;
    int maxDepth = 0;
    parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);

    if (!pagedir_init(pageDirectory)) {
        fprintf(stderr, "Failed to initialize page directory\n");
        exit(EXIT_FAILURE);
    }

    crawl(seedURL, pageDirectory, maxDepth);

    free(seedURL);
    free(pageDirectory);

    return 0;
}

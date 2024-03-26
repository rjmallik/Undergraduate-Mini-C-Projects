#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pagedir.h"
#include "crawler.h"

bool pagedir_init(const char *pageDirectory) {
	// Check if the pageDirectory is valid
	if (pageDirectory == NULL || strlen(pageDirectory) == 0) {
		fprintf(stderr, "Invalid page directory\n");
		return false;
	}

	// Create the .crawler file in the pageDirectory
	char *crawlerFilePath = malloc(strlen(pageDirectory) + strlen(".crawler") + 2);
	sprintf(crawlerFilePath, "%s/.crawler", pageDirectory);

	FILE *crawlerFile = fopen(crawlerFilePath, "w");
	if (crawlerFile == NULL) {
		fprintf(stderr, "Unable to create .crawler file\n");
		free(crawlerFilePath);
		return false;
	}

	free(crawlerFilePath);
	fclose(crawlerFile);
	return true;
}

void pagedir_save(const webpage_t *page, const char *pageDirectory, const int documentID) {
	// Create the filename for the webpage based on the document ID
	char *filename = malloc(strlen(pageDirectory) + 12); // "10" + ".txt" + '\0'
	sprintf(filename, "%s/%d.txt", pageDirectory, documentID);

	// Open the file for writing
	FILE *file = fopen(filename, "w");
	if (file == NULL) {
		fprintf(stderr, "Unable to create file %s\n", filename);
		free(filename);
		return;
	}

	// Write the URL, depth, and HTML content to the file
	fprintf(file, "%s\n", page->url);
	fprintf(file, "%d\n", page->depth);
	fprintf(file, "%s", page->html);

	fclose(file);
	free(filename);
}

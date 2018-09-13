#pragma once

#include "file_header.h"
#include "page.h"

/**
 *
 * @file pager.h 
 * @brief A Pager manages Pages in a database File.
 *
 * TODO XXX !!! HERE WRITE WHAT PAGER DOES
 *
 */

typedef struct thirlage_pager thirlage_pager;

struct thirlage_pager {
  thirlage_file_header file_header;
	// other members will follow for, e.g., number of pages to cache
};


// read header length bytes into a file_header - need function from file_header for this
int thirlage_init_pager(thirlage_pager *pager, FILE *file);

// read page function
// to begin, just read off disk; later use a cache (part of struct) 

// insert page function

// caching; don't malloc here; should be sent in

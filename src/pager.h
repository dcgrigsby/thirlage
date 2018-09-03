#include "page.h"

/**
 *
 * @file pager.h 
 * @brief A Pager manages Pages in a database file.
 *
 * A database file contains Pages, all of the same size.  The first page starts at the first position; the second follows size-of Page bytes later.
 *
 * The pager works with Pages' ids.  Page ids are not part of the Page struct; they're positional. The n-th page has an id of n.
 *
 * Page ids are fixed, so you cannot deleting a Page.  Instead, when it's no longer used, it's added to the Free List.  
 *
 * When a new page is needed, the Pager uses one in the Free List if available, removing it from the list in the process.  Else, one is appended to the file.
 *
 */

int read_page_from_file(FILE *file, page &page, u32 index);

int insert_page_in_file(FILE *file, page &page);

int update_page_in_file(FILE *file, page &page, u32 index);

// need delete|move-to-free-list


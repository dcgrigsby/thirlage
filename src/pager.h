#include "file.h"
#include "page.h"

/**
 *
 * @file pager.h 
 * @brief A Pager manages Pages in a database File.
 *
 * A database File contains Pages. 
 *
 * <Explain Free List>
 *
 * When a new Page is needed, the Pager uses one in the Free List if available, removing it from the list in the process. 
 *
 */

// need move-to-free-list


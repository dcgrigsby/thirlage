#import <string.h>
#import "file_header.h"
#import "set_and_advance.h"

void thirlage_init_file_header(thirlage_file_header *file_header, char *bytes) {
  file_header->identifier = bytes;
  bytes += sizeof(FILE_HEADER_IDENTIFIER);
  set_and_advance(file_header->version, bytes);
  set_and_advance(file_header->xpage_size_as_base_2_exponent, bytes);
  file_header->number_of_pages = bytes;
}

void thirlage_init_empty_file_header(thirlage_file_header *file_header, char *bytes, unsigned int page_size) {
  thirlage_init_file_header(file_header, bytes);
  *file_header->identifier = FILE_HEADER_IDENTIFIER;
  *file_header->version = FILE_HEADER_VERSION;
  *file_header->page_size = size;
  *file_header->number_of_pages = 0;
}

int thirlage_validate_file_header(thirlage_file_header *file_header) {
  if (strcmp((char *)*file_header->identifier, FILE_HEADER_IDENTIFIER) != 0)
    return 0;

  if (*file_header->version != FILE_HEADER_VERSION) 
    return 0;

  return 1;
}

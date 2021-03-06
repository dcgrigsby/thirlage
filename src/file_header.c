#import <string.h>
#import "file_header.h"

void thirlage_init_file_header(thirlage_file_header *file_header, char **bytes) {
  file_header->identifier = *bytes;
  *bytes += sizeof(FILE_HEADER_IDENTIFIER);

  file_header->version = (unsigned short *)*bytes;
  *bytes += sizeof(file_header->version);

  file_header->page_size = (unsigned int *)*bytes;
  *bytes += sizeof(file_header->page_size);

  file_header->number_of_pages = (unsigned int *)*bytes;
  *bytes += sizeof(file_header->number_of_pages);
}

void thirlage_init_empty_file_header(thirlage_file_header *file_header, char **bytes, size_t page_size) {
  thirlage_init_file_header(file_header, bytes);
  strcpy(file_header->identifier, FILE_HEADER_IDENTIFIER);
  *file_header->version = FILE_HEADER_VERSION;
  *file_header->page_size = page_size;
  *file_header->number_of_pages = 0;
}

int thirlage_validate_file_header(thirlage_file_header *file_header) {
  if (strcmp(file_header->identifier, FILE_HEADER_IDENTIFIER) != 0)
    return -1;

  if (*file_header->version != FILE_HEADER_VERSION) 
    return -1;

  return 0;
}

size_t thirlage_file_header_size(thirlage_file_header *file_header) {
  return 
    strlen(file_header->identifier) + 1 +
    sizeof(*file_header->version) +
    sizeof(*file_header->page_size) +
    sizeof(*file_header->number_of_pages);
}

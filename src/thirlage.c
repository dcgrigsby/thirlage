#import <string.h>
#import <stdio.h>
#include "page.h"

int main(void) {

  /*
  BYTE_TYPE bytes[512] = {0};
  BYTE_TYPE *b = &bytes[0];
  
  HEADER_TYPE number_of_rows = 2;
  memcpy(b, &number_of_rows, sizeof(HEADER_TYPE));
  b += sizeof(HEADER_TYPE);

  HEADER_TYPE positions_of_rows[] = { 512, 511 };
  memcpy(b, &positions_of_rows, sizeof(HEADER_TYPE) * 2);

  for (int i = 0; i < 512; i++) 
    printf("%hu ", bytes[i]);
  printf("\n");

  Page page;
  initPageFromBytes(&page, &bytes[0]);

  printf("Number of rows: %hu\n", *page.number_of_rows);
  printf("Position of row zero: %hu\n", page.positions_of_rows[0]);
  printf("Position of row one: %hu\n", page.positions_of_rows[1]);
  */

}

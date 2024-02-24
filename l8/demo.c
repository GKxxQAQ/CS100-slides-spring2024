#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_SIZE 8

char *read_string(void) {
  char c = getchar();
  while (isspace(c))
    c = getchar();

  char *buffer = malloc(INITIAL_SIZE);
  int capacity = INITIAL_SIZE;
  int cur_pos = 0;

  while (!isspace(c)) {
    if (cur_pos == capacity - 1) {
      char *new_buffer = malloc(capacity * 2);
      memcpy(new_buffer, buffer, cur_pos);
      free(buffer);
      capacity *= 2;
      buffer = new_buffer;
    }
    buffer[cur_pos++] = c;
    c = getchar();
  }

  // Now, c is a whitespace. This is not part of the contents we need.

  ungetc(c, stdin); // Put that whitespace back

  buffer[cur_pos] = '\0'; // Remember this!!

  return buffer;
}

int main(void) {
  char *content = read_string();
  puts(content);
  free(content);
}
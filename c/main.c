#include <bench_tools.h>
#include <coupon_generator.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));

  const int code_count = 10;

  char **codes = generate_coupons("ES#@", code_count);

  printf("[");
  for (int i = 0; i < code_count; i++) {
    if (i == code_count - 1) {
      printf("\"%s\"", codes[i]);
    } else {
      printf("\"%s\", ", codes[i]);
    }
  }
  printf("]");

  printf("\n");

  free_codes(codes, code_count);

  return 0;
}
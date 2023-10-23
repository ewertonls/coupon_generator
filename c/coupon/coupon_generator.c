#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char *NUMBERS = "0123456789";

typedef struct {
  bool is_under_limit;
  int limit;
} pattern_permutation;

char pick_random_char(char *source) { return source[rand() % strlen(source)]; }

pattern_permutation compute_pattern_permutation(char *pattern, int count) {

  int total = 1;
  for (int i = 0; i < strlen(pattern); i++) {
    switch (pattern[i]) {
    case '@':
      total *= strlen(LETTERS);
      break;
    case '#':
      total *= strlen(NUMBERS);
      break;
    default:
      break;
    }
  }

  return (pattern_permutation){
      .limit = total,
      .is_under_limit = count <= total,
  };
}

char *generate_code(char *pattern) {
  size_t pattern_len = strlen(pattern);
  char *buffer = (char *)malloc(pattern_len + 1);

  if (buffer == NULL) {
    fprintf(stderr, "failed to allocate memory for generating code: %s",
            strerror(errno));
    exit(1);
  }

  for (int i = 0; i < pattern_len; i++) {
    switch (pattern[i]) {
    case '@':
      buffer[i] = pick_random_char((char *)LETTERS);
      break;
    case '#':
      buffer[i] = pick_random_char((char *)NUMBERS);
      break;
    default:
      buffer[i] = pattern[i];
      break;
    }
  }

  buffer[pattern_len] = '\0';

  return buffer;
}

bool find_code_linear(char **arr, int arr_len, char *code) {
  for (int i = 0; i < arr_len; i++) {
    char *val = (char *)arr[i];
    if (val == NULL || code == NULL)
      continue;

    if (strcmp(val, code) == 0) {
      return true;
    }
  }

  return false;
}

char **generate_coupons(char *pattern, int count) {
  pattern_permutation permutation = compute_pattern_permutation(pattern, count);

  if (!permutation.is_under_limit) {
    fprintf(stderr,
            "the amount of coupons to generate (%d) is above the limit: %d",
            count, permutation.limit);
    exit(1);
  }

  char **generated_codes;

  generated_codes = (char **)calloc((size_t)count, sizeof *generated_codes);

  int inserted_codes_count = 0;

  for (; inserted_codes_count < count;) {
    char *code = generate_code(pattern);
    if (find_code_linear(generated_codes, count, code)) {
      free(code);
      continue;
    }

    generated_codes[inserted_codes_count] = code;

    inserted_codes_count++;
  }

  return generated_codes;
}

void free_codes(char **codes, int codes_len) {
  for (int i = 0; i < codes_len; i++) {
    free(codes[i]);
    codes[i] = NULL;
  }
  free(codes);
  codes = NULL;
}
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vector {
  double *entries;
  size_t dimension;
};

struct Vector create_vector(size_t n) {
  return (struct Vector){.entries = calloc(n, sizeof(double)), .dimension = n};
}

void destroy_vector(struct Vector *vec) { free(vec->entries); }

void vector_assign(struct Vector *to, const struct Vector *from) {
  if (to == from)
    return;
  free(to->entries);
  to->entries = malloc(from->dimension * sizeof(double));
  memcpy(to->entries, from->entries, from->dimension * sizeof(double));
  to->dimension = from->dimension;
}

bool vector_equal(const struct Vector *lhs, const struct Vector *rhs) {
  if (lhs->dimension != rhs->dimension)
    return false;
  for (size_t i = 0; i != lhs->dimension; ++i)
    if (lhs->entries[i] != rhs->entries[i])
      return false;
  return true;
}

struct Vector vector_add(const struct Vector *lhs, const struct Vector *rhs) {
  assert(lhs->dimension == rhs->dimension);
  struct Vector result = create_vector(lhs->dimension);
  for (size_t i = 0; i != lhs->dimension; ++i)
    result.entries[i] = lhs->entries[i] + rhs->entries[i];
  return result;
}

struct Vector vector_minus(const struct Vector *lhs, const struct Vector *rhs) {
  assert(lhs->dimension == rhs->dimension);
  struct Vector result = create_vector(lhs->dimension);
  for (size_t i = 0; i != lhs->dimension; ++i)
    result.entries[i] = lhs->entries[i] - rhs->entries[i];
  return result;
}

struct Vector vector_scale(const struct Vector *lhs, double scale) {
  struct Vector result = create_vector(lhs->dimension);
  for (size_t i = 0; i != lhs->dimension; ++i)
    result.entries[i] = lhs->entries[i] * scale;
  return result;
}

double vector_dot_product(const struct Vector *lhs, const struct Vector *rhs) {
  assert(lhs->dimension == rhs->dimension);
  double result = 0;
  for (size_t i = 0; i != lhs->dimension; ++i)
    result += lhs->entries[i] * rhs->entries[i];
  return result;
}

double vector_norm(const struct Vector *vec) {
  return sqrt(vector_dot_product(vec, vec));
}

double vector_distance(const struct Vector *lhs, const struct Vector *rhs) {
  struct Vector diff = vector_minus(lhs, rhs);
  return vector_norm(&diff);
}

void print_vector(const struct Vector *vec) {
  putchar('(');
  if (vec->dimension > 0) {
    printf("%lf", vec->entries[0]);
    for (size_t i = 1; i != vec->dimension; ++i)
      printf(", %lf", vec->entries[i]);
  }
  putchar(')');
}
#pragma once

#include "flint/nmod_poly.h"
#include "flint/fmpz_poly.h"

class Fpoly {
public:
  Fpoly() {
    fmpz_poly_init(poly);
  }

  ~Fpoly() {
    fmpz_poly_clear(poly);
  }

  Fpoly(const Fpoly& other) {
    fmpz_poly_init(poly);
    fmpz_poly_set(poly, other.poly);
  }

  void one() {
    fmpz_poly_one(poly);
  }

  void random(slong length, flint_rand_t state) {
    fmpz_poly_randtest_not_zero(poly, state, length, 16);
  }

  slong degree() const {
    return fmpz_poly_degree(poly);
  }

  ulong get_coeff(slong n) const {
    return fmpz_poly_get_coeff_ui(poly, n);
  }

  void print(const char* sym) {
    fmpz_poly_print_pretty(poly, sym);
  }

  void times(const Fpoly& other) {
    fmpz_poly_mul(poly, poly, other.poly);
  }

private:
  fmpz_poly_t poly{};
};


class Mpoly {
public:
  Mpoly() {
    nmod_poly_init(poly, 9223372036854775783);
  }

  ~Mpoly() {
    nmod_poly_clear(poly);
  }

  Mpoly(const Mpoly& other) {
    nmod_poly_init(poly, 9223372036854775783);
    nmod_poly_set(poly, other.poly);
  }

  void one() {
    nmod_poly_one(poly);
  }

  void set(const Fpoly& fpoly) {
    for(slong i = fpoly.degree(); i>=0; --i) {
      if (fpoly.get_coeff(i) != 0)
        nmod_poly_set_coeff_ui(poly, i, fpoly.get_coeff(i));
    }
  }

  void random(slong length, flint_rand_t state) {
    nmod_poly_randtest(poly, state, length);
  }

  void print(const char* sym) {
    nmod_poly_print_pretty(poly, sym);
  }

  void times(const Mpoly& other) {
    nmod_poly_mul_classical(poly, poly, other.poly);
  }

private:
  nmod_poly_t poly{};
};
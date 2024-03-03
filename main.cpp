#include <iostream>
#include <vector>
#include <chrono>

#include "ffpoly.h"

const slong POLYNUMBER = 1000;
const slong POLYDEGREE = 3;

int main() {
  flint_rand_t rand;
  flint_randinit(rand);

  // Fpoly
  std::vector<Fpoly> fpolys(POLYNUMBER);
  for(Fpoly& poly: fpolys) {
    poly.random(POLYDEGREE, rand);
  }

  Fpoly fres;
  fres.one();

  auto start = std::chrono::high_resolution_clock::now();
  for(const Fpoly& poly: fpolys) {
    fres.times(poly);
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> ftime = end - start;

  std::cout << "\n Fpoly: " << ftime.count()*1000 << "   ms" << std::endl;


  // Mpoly
  std::vector<Mpoly> mpolys(POLYNUMBER);
  for(unsigned i = 0; i < POLYNUMBER; ++i) {
    mpolys[i].set(fpolys[i]);
  }

  Mpoly mres;
  mres.one();

  start = std::chrono::high_resolution_clock::now();
  for(const Mpoly& poly: mpolys) {
    mres.times(poly);
  }
  end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> mtime = end - start;

  std::cout << " Mpoly: " << mtime.count()*1000 << "   ms" << std::endl;
  std::cout << " \n scale: " << mtime/ftime *100 << " %" << std::endl;

  return 0;
}
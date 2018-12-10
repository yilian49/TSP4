
#pragma once

#include "chromosome.hh"
#include "cities.hh"
#include "tournament_deme.hh"

#include <random>

class MultiDeme : public Deme {
 public:
  // Generate a Deme of the specified size with all-random chromosomes.
  // Also receives a mutation rate in the range [0-1].
  MultiDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate)
    : Deme(cities_ptr, pop_size, mut_rate)
  {}

  virtual ~MultiDeme() = default;
  void threaded_compute_next_generation(unsigned nthread);

// protected:
  // Randomly select a chromosome in the population based on fitness and
  // return a pointer to that chromosome.
//  virtual Chromosome* select_parent() override;
};

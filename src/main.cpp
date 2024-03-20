// This is an interactive demo, so feel free to change the code and click the 'Run' button.

// This simple program uses the mlpack::neighbor::NeighborSearch object
// to find the nearest neighbor of each point in a dataset using the L1 metric,
// and then print the index of the neighbor and the distance of it to stdout.

#include <mlpack.hpp>
#include <mlpack/methods/random_forest.hpp>
#include <iostream>
#include <vector>
#include "foo.h"
// AI-Toolbox basic seed generator for random engines.
#include <AIToolbox/Seeder.hpp>
// AI-Toolbox basic utility to generate mean and variance for data.
#include <AIToolbox/Tools/Statistics.hpp>
// ########################################################################
// #
// # LOGGING
// #
// # The code below is used in case AI-Toolbox has been compiled with logging
// # enabled. In this case, we create a simple printing function that will output
// # debug messages from AI-Toolbox.
// #
// ########################################################################
#ifdef AI_LOGGING_ENABLED
#include <AIToolbox/Logging.hpp>
void logger(int severity, const char * message) {
    std::cout << '[' << severity << "] " << message << '\n';
}
#endif

#include "GitHash.hpp"
using namespace mlpack;
using namespace mlpack::neighbor;
using namespace mlpack::metric;

int main()
{
  int c = add(10, 10);
  std::cout << c << std::endl;
  arma::mat dataset(1, 1000);
  dataset.row(0) = arma::linspace<arma::rowvec>(1000, 1999, 1000);
  for (size_t i = 0; i < dataset.n_elem; ++i)
  {
    std::cout << i;
  }

  std::cout <<  "# OUTPUT PRODUCED WITH HASH: " << GitHash::sha1 << std::endl;
  foo();
  // C++20 (and later) code
  #if __cplusplus > 201703L
    for (std::vector<int> v{ 1, 2, 3 }; auto& e : v) {
      std::cout << e;
    }
    std::cout << std::endl;
  #endif

  arma::mat data;
  data::Load("../data/data.csv", data, true);

  // Use templates to specify that we want a NeighborSearch object which uses
  // the Manhattan distance.
  NeighborSearch<NearestNeighborSort, ManhattanDistance> nn(data);

  // Create the object we will store the nearest neighbors in.
  arma::Mat<size_t> neighbors;
  arma::mat distances; // We need to store the distance too.

  // Compute the neighbors.
  nn.Search(1, neighbors, distances);

  // Write each neighbor and distance using Log.
  for (size_t i = 0; i < neighbors.n_elem; ++i)
  {
    std::cout << "Nearest neighbor of point " << i << " is point "
        << neighbors[i] << " and the distance is " << distances[i] << "." << std::endl;
  }

  return 0;
}
#ifndef RANDOM_STREAMS_H
#define RANDOM_STREAMS_H

#include <vector>
#include <stdlib.h>

using namespace std;

/* This class encapsulates the streams of random numbers used in state
 * transitions during simulations. It also provides random-number seeds
 * for different components of the system.
 */
class RandomStreams {
 public:
  RandomStreams(int num_streams, int length, unsigned seed);

  int NumStreams() const { return streams_.size(); }

  int Length() const { return streams_.size() > 0 ? streams_[0].size() : 0; }

  double Entry(int stream, int pos) const {
    return streams_[stream][pos];
  }

  unsigned WorldSeed() const {
    return seed_ ^ streams_.size();
  }

  unsigned BeliefUpdateSeed() const {
    return seed_ ^ (streams_.size() + 1);
  }

  unsigned ModelSeed() const {
    return seed_ ^ (streams_.size() + 2);
  }

private:
  unsigned StreamSeed(int stream_id) const {
    return seed_ ^ stream_id;
  }

  vector<vector<double>> streams_; // Each particle is associated with a single
                                   // stream of numbers.
  unsigned seed_;
};

#endif

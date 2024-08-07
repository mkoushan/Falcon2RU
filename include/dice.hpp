#ifndef DICE_HPP_INCLUDED
#define DICE_HPP_INCLUDED

#include <vector>
#include <random>


template <class T>
inline T roll(const std::vector<T> probabilities)
{
   // Create a random number generator
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<> distrib(0, probabilities.size() - 1);
   // Generate a random value to determine the outcome
   int rand_index= distrib(gen);

   return probabilities.at(rand_index);
}

inline int roll(const std::vector<int>& probabilities)
{
   // Create a random number generator
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<> distrib(0, probabilities.size() - 1);
   // Generate a random value to determine the outcome
   int rand_index= distrib(gen);

   return probabilities.at(rand_index);
}
#endif // DICE_HPP_INCLUDED

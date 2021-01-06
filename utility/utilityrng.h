#ifndef UTILITY_H
#define UTILITY_H
#include <random>

namespace utility
{
    using intervalvector = std::vector<std::vector<std::pair<double,double> > >;
    class RandomGenerator
    {
    public:
        static RandomGenerator& get_instance()
        {
            static RandomGenerator rg;
            return rg;
        }

        static uint get_unifrom_random_uint(uint from, uint to)
        {
            std::uniform_int_distribution<uint> uniformIntDistribution(from, to);
            return uniformIntDistribution(RandomGenerator::get_instance().rng);
        }

        static uint get_unifrom_random_uint(std::uniform_int_distribution<uint>& distribution)
        {
            return distribution(RandomGenerator::get_instance().rng);
        }

        static double get_uniform_random_double(double from, double to)
        {
            std::uniform_real_distribution<double> uniformRealDistribution(from, to);
            return uniformRealDistribution(RandomGenerator::get_instance().rng);
        }

        static double get_uniform_random_double(std::uniform_real_distribution<double>& distribution)
        {
            return distribution(RandomGenerator::get_instance().rng);
        }
        //Deleting copy constructor and copy assignment
        RandomGenerator(const RandomGenerator&) = delete;
        RandomGenerator& operator=(const RandomGenerator&) = delete;
    private:
        RandomGenerator() = default;
        std::random_device device{};
        std::mt19937 rng{device()};
    };
}
using rng = utility::RandomGenerator;
#endif //UTILITY_H

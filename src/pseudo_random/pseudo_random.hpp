/**
 * @file       <pseudo_random.hpp>
 * @brief      This header file holds implementation of PseudoRandomGenerator class. 
 * 
 *             This calss implements search algorithms needed for successfull completion of laboratory work 4.
 *
 * @author     Alexander Chudnikov (THE_CHOODICK)
 * @date       15-02-2023
 * @version    0.0.1
 * 
 * @warning    This library is under development, so there might be some bugs in it.  
 * @bug        Currently, there are no any known bugs. 
 * 
 *             In order to submit new ones, please contact me via admin@redline-software.xyz.
 * 
 * @copyright  Copyright 2023 Alexander. All rights reserved. 
 * 
 *             (Not really)
 */
#ifndef PSEUDO_RANDOM_HPP
#define PSEUDO_RANDOM_HPP

#include <memory>
#include <cmath>
#include <vector>
#include <iostream>
#include <numeric>
#include <unordered_map>


class PseusoRandom
{
public:

    /**
     * @brief      Generation of random line with length of n by using uniform distribution
     *
     * @tparam     N     Length of generated line
     *
     * @return     Pseuorandom line 
     *  with the lenght of N
     */
    template<typename T, std::size_t LINE>
        static std::vector<T> generate_uniform_n(std::size_t n)
        {
            std::vector<T> key;
            key.resize(n, 0);

            std::vector<T> distribution = uniform_distribution<T>(0, 2147483647, LINE, n);

            for (std::size_t i = 0; i < n; ++i) 
            {
                key[i] = distribution.at(i);
            }

            return key;
        }
    
    /**
     * @brief      Generation of random line with length of n by using normal distribution
     *
     * @tparam     N     Length of generated line
     *
     * @return     Pseuorandom line 
     *  with the lenght of N
     */
    template<typename T, std::size_t LINE>
        static std::vector<T> generate_normal_n(std::size_t n)
        {
            std::vector<T> key;
            key.resize(n, 0);

            std::vector<T> distribution = normal_distribution<T>(n);

            for (std::size_t i = 0; i < n; ++i) 
            {
                key[i] = distribution.at(i);
            }

            return key;
        }
    

    /**
     * @brief       uniform distribuion as an array
     *
     * @param[in]   min   Minimum distribution value
     * @param[in]   max   Maximum distribution value
     *
     * @tparam      T     Typename of min/max value
     * @tparam      SIZE  Size of normalized uniform distribution
     *
     * @return      std::array of uniformely distributed values in the range of [min, max] 
     */
    template <typename T>
        static std::vector<T> uniform_distribution(T min, T max, std::size_t line, std::size_t n)
        {
            std::vector<T> distribution;
            distribution.resize(n, 0);

            auto previous = int_seed(line);
            for (auto &element : distribution) 
            {
                element = static_cast<T>(uniform_distribution_n(previous) * (max - min) + min);
            }
            
            return distribution;
        }

    /**
     * @brief       normal distribuion as an array
     *              
     *              Normal distribution is being approximated by the Irwin-Hall distribution
     *
     * @param[in]  mean         Irwin-Hall mean
     * @param[in]  sigma        Irwin-Hall sigma
     *
     * @tparam     T            Typename of min/max value
     * @tparam     SIZE         Size of normalized uniform distribution
     * @tparam     IRWIN_NUM    Irwin distribution numbers
     *
     * @return     { description_of_the_return_value }
     */
    template <typename T, std::size_t IRWIN_NUM = 12>
        static std::vector<T> normal_distribution(std::size_t n)
        {
            std::vector<T> distribution;
            distribution.resize(n, 0);

            auto previous = int_seed(0);
            for (auto &element : distribution) 
            {
                double value = 0;
                for (std::size_t i = 0; i < IRWIN_NUM; ++i)
                {
                    value += uniform_distribution_n(previous);
                }

                element = value / std::sqrt(IRWIN_NUM / 12.0f) - IRWIN_NUM / 2.0f;
            }

            return distribution;
        }

    static std::vector<unsigned int> xor_generate_n(std::size_t n)
    {
        std::vector<unsigned int> key;
        key.resize(n, 0);

        auto previous = int_seed(0);
        for (std::size_t i = 0; i < n; ++i) 
        {
            key[i] = xor_generator(previous);
            previous = key[i];
        }

        return key;
    }

private:
    /**
     * @brief       implemenatation of ctoi
     *
     * @param[in]   str     String, that shoild be converted to ineger
     * @param[in]   offset  String offset
     *
     * @return      Converted integer
     */
    static unsigned int_ctoi(const char* str, int offset)
    {
        return static_cast<std::uint32_t>(str[offset] - '0') * 10 + static_cast<std::uint32_t>(str[offset + 1] - '0');
    }

    /**
     * @brief       implemenatation of creating seed from __TIME__ and __DATE__
     *
     * @return      Seed for pseudorandom generator
     */
    static unsigned int int_seed(std::size_t line)
    {
        auto compile_time = __TIME__;
        auto compile_date = __DATE__;
        return int_ctoi(compile_time, 0) * 60 * 60 + int_ctoi(compile_time, 3) * 60 + int_ctoi(compile_time, 6) + int_ctoi(compile_date, 5) * 24 * 60 * 60 - line;
    }

    /**
     * @brief       uniform distribuion
     *              
     *              Previous value is passed by refeerence due to the lack of static values
     *
     * @param[in]   previous    Previous value
     *
     * @return      Uniformely distributed value in the range of [0, 714025]
     */
    static std::uint32_t uniform_distribution(std::uint32_t &previous)
    {
        previous = ((lce_a * previous + lce_c) % lce_m);
        return previous;
    }

    /**
     * @brief       normalzed uniform distribuion
     * 
     *              Previous value is passed by refeerence due to the lack of static values
     *
     * @param       previous    Previous value
     *
     * @return      Uniformely distributed value in the range of [0.0, 1.0]
     */
    static double uniform_distribution_n(std::uint32_t &previous)
    {
        auto distribution = uniform_distribution(previous);
        return static_cast<double>(distribution) / lce_m;
    }

    static unsigned int xor_generator(unsigned int state) 
    {
        state ^= state << 13;
        state ^= state >> 17;
        state ^= state << 5;
        return state;
    }

protected:
    static const std::uint32_t lce_a = 4096;
    static const std::uint32_t lce_c = 150889;
    static const std::uint32_t lce_m = 714025;

    const unsigned long long lcg_m = 4294967296;
    const unsigned long long lcg_a = 1664525;
    const unsigned long long lcg_c = 1013904223; 
};

class PseusoRandomUtilities
{
public:
    template<typename T>
        static double calculate_mean(const std::vector<T>& sample)
        {
            double sum = 0.0;
            for (const auto& value : sample) 
            {
                sum += value;
            }
            return sum / sample.size();
        }

    template<typename T>
        static double calculate_standard_deviation(const std::vector<T>& sample, double mean)
        {
            double sum_sqrt_diff = 0.0;
            for (const auto& value : sample) 
            {
                double diff = value - mean;
                sum_sqrt_diff += diff * diff;
            }
            return std::sqrt(sum_sqrt_diff / sample.size());
        }

    template<typename T>
        static double calculate_coefficient_of_variation(T standard_deviation, double mean)
        {
            return (standard_deviation / mean) * 100.0;
        }

    /**
     * Perform the chi-square test to determine the uniformity of the given data.
     *
     * @tparam T The type of the elements in the data vector.
     * @param data The input data vector.
     * 
     * @return True if the data is deemed to have a uniform distribution, false otherwise.
     */
    template<typename T>
        static bool chi_square_test(const std::vector<T>& data) 
        {
            const int num_classes = 10; //< Number of classes for the chi-square test
            const int sample_size = data.size();

            std::unordered_map<int, int> observed; //< Map to store observed frequencies for each class
            for (const auto& value : data) 
            {
                int class_index = static_cast<int>(value * num_classes); //< Calculate the class index for the current value
                ++observed[class_index];  //< Increment the observed frequency for the corresponding class index
            }

            int total_observed = 0;  //< Total observed frequency
            for (const auto& pair : observed) 
            {
                total_observed += pair.second;  //< Accumulate the observed frequencies
            }

            std::vector<double> expected(num_classes, static_cast<double>(total_observed) / sample_size);

            double chi_square = 0.0;
            for (size_t i = 0; i < num_classes; ++i) 
            {
                int observed_freq = observed[i];
                double diff = observed_freq - expected[i];
                chi_square += (diff * diff) / expected[i];
            }

            const double critical_value = 16.919; //< Critical value for the chi-square test (can be modified)
            bool is_uniform = chi_square <= critical_value; //< Determine if the data is deemed to have a uniform distribution

            return is_uniform;
        }

    template<typename T>
        static bool is_random(const std::vector<T>& data) 
        {
            std::vector<T> unique_values = data;
            std::sort(unique_values.begin(), unique_values.end());
            unique_values.erase(std::unique(unique_values.begin(), unique_values.end()), unique_values.end());

            double expected_frequency = static_cast<double>(data.size()) / unique_values.size();
            double variance = 0.0;
            for (const auto& value : unique_values) 
            {
                int count = std::count(data.begin(), data.end(), value);
                variance += (count - expected_frequency) * (count - expected_frequency);
            }
            variance /= unique_values.size();

            const double critical_value = 11.070;
            bool is_random = variance <= critical_value;

            return is_random;
        }

    template<typename T>
        static void analyze_samples(const std::vector<T>& sample)
        {
            //bool is_random_ = is_random<T>(sample);
            bool is_uniform = chi_square_test<T>(sample);
            double mean = calculate_mean<T>(sample);
            double standard_deviation = calculate_standard_deviation<T>(sample, mean);
            double coefficient_of_variation = calculate_coefficient_of_variation<T>(standard_deviation, mean);
            
            std::cout << "Mean: " << mean << std::endl;
            std::cout << "Standard Deviation: " << standard_deviation << std::endl;
            std::cout << "Coefficient of Variation: " << coefficient_of_variation << "%" << std::endl;
            //std::cout << "Randomness: " << (is_random_ ? "Yes" : "No") << std::endl;
            std::cout << "Uniform distribution: " << (is_uniform ? "Yes" : "No") << std::endl;

        
            
            if (coefficient_of_variation < 10.0) 
            {
                std::cout << "The sample is homogeneous." << std::endl;
            } 
            else 
            {
                std::cout << "The sample is not homogeneous." << std::endl;
            }
            
            std::cout << std::endl;

            return;
        }

};

#endif // PSEUDO_RANDOM_HPP
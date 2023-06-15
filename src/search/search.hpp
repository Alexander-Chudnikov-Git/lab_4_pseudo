/**
 * @file       <sorting.hpp>
 * @brief      This header file holds implementation of Search class. 
 * 
 *             This calss implements search algorithms needed for successfull completion of laboratory work 2.
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
#ifndef SEARCH_HPP
#define SEARCH_HPP

#ifndef MODEL_HPP
#include "../model/model.hpp"
#endif // MODEL_HPP

#include <iostream>

/**
 * @class Search
 *
 * @brief A class that provides static searching methods for sorting a vector of Model objects based on a specific field.
 * 
 * @note Currently provides implementations for binary search.
 */
class Search
{
public:
    /**
     * @brief Performs binary search on a vector of Model objects based on a specific field.
     *
     * @tparam T The type of the search value.
     * @param model_vector The vector of Model objects to search in.
     * @param search_value The value to search for.
     * @param field The field on which to perform the search.
     * 
     * @return The index of the found element, or -1 if not found.
     */
    template<typename T>
        static int binary_search(std::vector<Model>& model_vector, T search_value, std::uint8_t field);

    /**
     * @brief Performs straight search on a vector of Model objects based on a specific field.
     *
     * @tparam T The type of the search value.
     * @param model_vector The vector of Model objects to search in.
     * @param search_value The value to search for.
     * @param field The field on which to perform the search.
     * 
     * @return The index of the found element, or -1 if not found.
     */
    template<typename T>
        static int straight_search(std::vector<Model>& model_vector, T search_value, std::uint8_t field); 
};


template<typename T>
int Search::binary_search(std::vector<Model>& model_vector, T search_value, std::uint8_t field) 
{
    int dummy = 0;
    int left = 0;
    int right = model_vector.size() - 1;
    uint8_t offset = field * 2;

    while (left <= right) 
    {
        int mid = (left + right) / 2;

        if (((int)model_vector.at(mid).compare_type<T>(field, search_value).get_type_masked(offset) == 0))
        {
            return mid;
        }

        else if (((int)model_vector.at(mid).compare_type<T>(field, search_value).get_type_masked(offset) == 1))
        {
            left = mid + 1;
        }

        else if (((int)model_vector.at(mid).compare_type<T>(field, search_value).get_type_masked(offset) == 2))
        {
            right = mid - 1; 
        }
    }
    return -1;
}

template<typename T>
int Search::straight_search(std::vector<Model>& model_vector, T search_value, std::uint8_t field) 
{
    uint8_t offset = field * 2;

    for (std::size_t index = 0; index < model_vector.size(); ++index) 
    {
        if (((int)model_vector.at(index).compare_type<T>(field, search_value).get_type_masked(offset) == 0))
        {
            return index;
        }
    }
    return -1;
}

#endif // SEARCH_HPP
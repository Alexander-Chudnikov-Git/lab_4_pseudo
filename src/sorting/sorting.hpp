/**
 * @file       <sorting.hpp>
 * @brief      This header file holds implementation of Sorting class. 
 * 
 *             This calss implements sorting algorithms needed for successfull completion of laboratory work 1.
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
#ifndef SORTING_HPP
#define SORTING_HPP

#ifndef MODEL_HPP
#include "../model/model.hpp"
#endif // MODEL_HPP

#include <iostream>

/**
 * @class Sorting
 *
 * @brief A class that provides static sorting methods for sorting a vector of Model objects based on a specific field.
 * 
 * @note Currently provides implementations for bubble sort, heap sort, and merge sort.
 */
class Sorting
{
public:
    static void bubble_sort(std::vector<Model>& model_vector, uint8_t field);
    static void heap_sort(std::vector<Model>& model_vector, uint8_t field);
    static void merge_sort(std::vector<Model>& model_vector, uint8_t field, std::size_t left = 0, std::size_t right = 0, bool initial = true);

private:
    static void make_heap(std::vector<Model>& model_vector, std::size_t index, uint8_t field, std::size_t last_index = 0);
    static void make_merge(std::vector<Model>& model_vector, uint8_t field, std::size_t left, std::size_t right, std::size_t middle);
};

#endif // SORTING_HPP
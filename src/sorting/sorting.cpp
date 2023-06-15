/**
 * @file       <sorting.cpp>
 * @brief      This source file holds implementation of Sorting class. 
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
#include "sorting.hpp"


/**
 * @brief Sorts the given vector of Model objects using bubble sort algorithm.
 * 
 * This function uses bubble sort algorithm to sort the given vector of Model objects
 * based on the field specified by the `field` parameter. The objects are compared
 * using the `compare_type()` method of the Model class.
 * 
 * @param model_vector The vector of Model objects to be sorted.
 * @param field The index of the field to be used for sorting the objects.
 *
 * @return void.
 *
 * @note This function modifies the original vector passed to it.
 * 
 * @note The `compare_type()` method of the Model class must return a Type object.
 * 
 * @note The Type object must have a method `get_type_masked()` that takes an
 *       offset and returns a boolean indicating whether the specified bit is set or not.
 * 
 * @note This function prints the number of iterations taken to sort the vector.
 */
void Sorting::bubble_sort(std::vector<Model>& model_vector, uint8_t field)
{
    bool has_changed;

    uint8_t offset = field * 2;

    std::size_t iteration_counter = 0;

    do
    {
        has_changed = false;

        for (std::size_t index = 0; index < model_vector.size() - 1; ++index)
        {
            if ((bool)(model_vector.at(index).compare_type(model_vector.at(index + 1), field)).get_type_masked(offset))
            {
                std::swap(model_vector[index], model_vector[index + 1]);
                has_changed = true;
            }
        }
        iteration_counter += 1;
    }   
    while (has_changed);

    //std::cout << "Sorting took " << iteration_counter << " iterations." << std::endl;

    return;
}

/**
 * @brief Performs heap sort on a vector of Model objects.
 * 
 * This function sorts a vector of Model objects using the heap sort algorithm. The function uses
 * the make_heap function to create a heap from the input vector, then sorts the heap by repeatedly
 * extracting the maximum element from the heap and placing it at the end of the vector.
 * 
 * @param model_vector The vector of Model objects to be sorted.
 * @param field The field of the Model object to sort by.
 *
 * @return void.
*/
void Sorting::heap_sort(std::vector<Model>& model_vector, uint8_t field)
{
    uint8_t offset = field * 2;

    for (std::int32_t index = (model_vector.size() / 2) - 1; index >= 0; --index)
    {
        Sorting::make_heap(model_vector, index, field);
    }
  
    for (std::int32_t index = model_vector.size() - 1; index >= 0; --index)
    {
        std::swap(model_vector[0], model_vector[index]);
        Sorting::make_heap(model_vector, 0, field, index);
    }    

    return;
}

/**
 * @brief Sorts a vector of Model objects using merge sort algorithm.
 * 
 * This function sorts a given vector of Model objects using merge sort algorithm.
 * It takes the field to be sorted as input, along with left and right indices of
 * the sub-vector to be sorted. If left and right indices are not provided, it sorts
 * the entire vector by setting left and right indices accordingly.
 *
 * @param model_vector The vector of Model objects to be sorted.
 * @param field The field to be sorted.
 * @param left The left index of the sub-vector to be sorted (default is 0).
 * @param right The right index of the sub-vector to be sorted (default is size-1).
 * @param initial A boolean flag indicating whether this is the initial call to the function (default is true).
 * 
 * @return void.
 */
void Sorting::merge_sort(std::vector<Model>& model_vector, uint8_t field, std::size_t left, std::size_t right, bool initial)
{
    if (initial)
    {
        left = 0;
        right = model_vector.size() - 1;
    }

    if(left >= right) 
    {
        return;
    }

    std::size_t middle = left + (right - left) / 2;

    Sorting::merge_sort(model_vector, field, left, middle, false);
    Sorting::merge_sort(model_vector, field, middle + 1, right, false);
    Sorting::make_merge(model_vector, field, left, right, middle);

    return;
}

/**
 * @brief Builds a heap from a vector of Model objects.
 * 
 * This function builds a heap from a vector of Model objects. The function starts at the root node of
 * a subtree and compares it with its left and right child nodes. If a child node is greater than the root
 * node, the function swaps the two nodes and continues recursively until the heap property is satisfied
 * for the entire subtree.
 * 
 * @param model_vector The vector of Model objects to build the heap from.
 * @param index The index of the root node of the subtree to build the heap from.
 * @param field The field of the Model object to sort by.
 * @param last_index The last index of the vector to consider when building the heap.
 * 
 * @return void.
 */
void Sorting::make_heap(std::vector<Model>& model_vector, std::size_t index, uint8_t field, std::size_t last_index)
{
    std::size_t biggest_index = index;
    std::size_t left_index = (2 * biggest_index) + 1;
    std::size_t right_index = (2 * biggest_index) + 2;

    if (last_index == 0)
    {
        last_index = model_vector.size();
    }

    if (left_index < last_index && (bool)(model_vector.at(left_index).compare_type(model_vector.at(biggest_index), field)).get_type_masked(field * 2))
    {
        biggest_index = left_index;
    }

    if (right_index < last_index && (bool)(model_vector.at(right_index).compare_type(model_vector.at(biggest_index), field)).get_type_masked(field * 2))
    {
        biggest_index = right_index;
    }

    if (biggest_index != index)
    {
        std::swap(model_vector[index], model_vector[biggest_index]);
  
        Sorting::make_heap(model_vector, biggest_index, field, last_index);
    }

    return;
}

/**
 * @brief Merges two sub-vectors in sorted order.
 * 
 * This function is called by the merge_sort function to merge two sub-vectors in
 * sorted order. It takes the field to be sorted as input, along with the left, right
 * and middle indices of the sub-vectors to be merged.
 * 
 * @param model_vector The vector of Model objects containing the two sub-vectors to be merged.
 * 
 * @param field The field to be sorted.
 * @param left The left index of the first sub-vector.
 * @param right The right index of the second sub-vector.
 * @param middle The middle index of the sub-vectors.
 * 
 * @return void.
 */
void Sorting::make_merge(std::vector<Model>& model_vector, uint8_t field, std::size_t left, std::size_t right, std::size_t middle)
{
    std::size_t left_length = middle - left + 1;
    std::size_t right_length = right - middle;

    std::vector<Model> left_array;
    std::vector<Model> right_array;

    for (std::size_t index = 0; index < left_length; ++index) 
    {
        left_array.push_back(model_vector.at(left + index));
    }

    for (std::size_t index = 0; index < right_length; ++index) 
    {
        right_array.push_back(model_vector.at(middle + index + 1));
    }

    std::size_t i = 0, j = 0, k = left;

    while (i < left_length && j < right_length) 
    {
        if ((bool)(right_array.at(j).compare_type(left_array.at(i), field)).get_type_masked(field * 2))
        {
            model_vector[k++] = left_array[i++];
        } 
        else 
        {
            model_vector[k++] = right_array[j++];
        }
    }

    while (i < left_length) 
    {
        model_vector[k++] = left_array[i++];
    }

    while (j < right_length) 
    {
        model_vector[k++] = right_array[j++];
    }
}
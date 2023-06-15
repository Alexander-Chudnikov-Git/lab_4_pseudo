/**
 * @file       <generator.hpp>
 * @brief      This header file holds implementation of Generator class. 
 * 
 *             This calss implements model generator needed for successfull completion of laboratory work 1.
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
#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <random>

#include <array>


#ifndef MODEL_HPP
#include "../model/model.hpp"
#endif // MODEL_HPP

/**
 * @class Generator
 * @brief A class that generates models.
 *
 * The Generator class is responsible for generating models with random data.
 * It uses a set of predefined lists for first names, last names, departments,
 * and job titles to create realistic models. The generated models include
 * information such as full name, department, job title, and a random date of
 * birth within a certain range.
 */
class Generator
{
public:
    /**
     * @brief Constructor for the Generator class.
     *
     * Initializes the lists of first names, last names, departments, and job
     * titles to empty lists. It also initializes the random number generator
     * and the distributions for generating random indices and dates.
     */
	Generator();

    /**
     * @brief Destructor for the Generator class.
     *
     * Cleans up any resources used by the Generator class.
     */
	~Generator();

    /**
     * @brief Generates a model.
     * @return The generated model.
     *
     * Generates a random model by selecting a random combination of first name,
     * last name, department, job title, and date of birth. The date of birth is
     * within a certain range of years, and the other attributes are randomly
     * selected from the predefined lists.
     */
    Model model_generator();

private:
    std::array<std::string, 2738> _first_name_list; /**< The list of first names. */
    std::array<std::string, 1000> _last_name_list;  /**< The list of last names. */
    std::array<std::string, 449> _department_list;  /**< The list of departments. */
    std::array<std::string, 357> _job_title_list;   /**< The list of job titles. */
    
    std::random_device       _random_device;        /**< The random number generator device. */
    std::mt19937             _generator;            /**< The random number generator. */

    std::uniform_int_distribution<uint32_t> _first_name_distribution;   /**< The distribution for first names. */
    std::uniform_int_distribution<uint32_t> _last_name_distribution;    /**< The distribution for last names. */
    std::uniform_int_distribution<uint32_t> _department_distribution;   /**< The distribution for departments. */
    std::uniform_int_distribution<uint32_t> _job_title_distribution;    /**< The distribution for job titles. */
    std::uniform_int_distribution<uint16_t> _year_distribution;         /**< The distribution for years. */
    std::uniform_int_distribution<uint16_t> _month_distribution;        /**< The distribution for months. */
    std::uniform_int_distribution<uint16_t> _sex_distribution;          /**< The distribution for sex. */
    std::uniform_int_distribution<uint16_t> _day_distribution;          /**< The distribution for days. */
};

#endif // GENERATOR_HPP
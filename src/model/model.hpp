/**
 * @file       <model.hpp>
 * @brief      This header file holds implementation of Model class. 
 * 
 *             This calss implements model needed for successfull completion of laboratory work 1.
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
#ifndef MODEL_HPP
#define MODEL_HPP


#include <chrono>
#include <cstddef>
#include <cstring> // strcmp has better performance 
#include <iomanip>
#include <iostream>
#include <optional>
#include <functional>
#include <list>
#include <optional>
#include <string>
#include <type_traits>
#include <vector>


#include <filesystem>
#include <fstream>
#include <boost/json.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <bitset>

#include "../pseudo_random/pseudo_random.hpp"

class Model;


/**
 * @class Hashing
 * @brief Contains static methods for hashing and related operations.
 */
class Hashing
{
public:
    /**
     * @brief      Basic hashing function for strings.
     *
     * @param[in]  value  The value to hash
     *
     * @return     The hash value
     */
    static std::uint32_t basic_hashing_function(const std::string& value);

    /**
     * @brief      djb2 hashing function for strings.
     *
     * @param[in]  value  The value to hash
     *
     * @return     The hash value
     */
    static std::uint32_t djb2_hashing_function(const std::string& value);

    /**
     * @brief      Advanced hashing function for strings.
     *
     * @param[in]  value  The value to hash
     *
     * @return     The hash value
     */
    static std::uint32_t advanced_hashing_function(const std::string& value);

    /**
     * @brief      Count the number of collisions in a hash table.
     *
     * @param[in]  hash_table  The hash table
     *
     * @return     The number of collisions
     */
    static std::uint32_t count_collisions(const std::vector<std::list<Model>>& hash_table);

    /**
     * @brief      Hash the models into a hash table.
     *
     * @param[in]  model_vector   The model vector
     * @param[in]  hash_function  The hash function
     *
     * @return     The hash table
     */
    static std::vector<std::list<Model>> hash_model(std::vector<Model>& model_vector, std::function<std::size_t(const std::string& value)> hash_function);

    /**
     * @brief      Find a model in a hash table.
     *
     * @param[in]  hash_table  The hash table
     * @param[in]  hash        The hash value
     * @param[in]  size        The size of the hash table
     *
     * @return     The model if found, otherwise an empty optional
     */
    static std::optional<Model> find_in_hash_table(const std::vector<std::list<Model>>& hash_table, std::uint32_t hash, std::size_t size);
};

class ModelComp;

/**
 * @class Model
 * @brief Represents an employee model.
 * 
 * The Model class represents an employee with attributes such as full name, department, job title,
 * employment date, model hash, and hash field.
 */
class Model
{
public:
   /**
     * @brief Constructor for the Model class.
     * 
     * @param full_name The full name of the model.
     * @param department The department of the model.
     * @param job_title The job title of the model.
     * @param employment_date The employment date of the model.
     * @param model_hash The hash value of the model.
     * @param hash_field The hash field of the model.
     * @param optional_func An optional hash function for the model.
     */
    Model(std::string full_name, std::string department, std::string job_title, std::chrono::year_month_day employment_date, std::uint32_t model_hash = 0, std::uint8_t hash_field = 255, const std::optional<std::function<std::size_t(const std::string& value)>>& optional_func = std::nullopt);
    
    /**
     * @brief Constructor for the Model class.
     * 
     * @param full_name The full name of the model.
     * @param department The department of the model.
     * @param job_title The job title of the model.
     * @param employment_date The employment date of the model.
     * @param model_hash The hash value of the model.
     * @param hash_field The hash field of the model.
     * @param optional_func An optional hash function for the model.
     */
    Model(std::string full_name, std::string department, std::string job_title, std::string employment_date, std::uint32_t model_hash = 0, std::uint8_t hash_field = 255, const std::optional<std::function<std::size_t(const std::string& value)>>& optional_func = std::nullopt);
    
    /**
     * @brief Constructor for the Model class.
     * 
     * @param decor_type The decoration type of the model.
     */
    Model(std::uint8_t decor_type);

    /**
     * @brief Copy constructor for the Model class.
     * 
     * @param other The other model to be copied.
     */
    Model(const Model& other) {
        try 
        {
            this->_full_name = other._full_name;
            this->_department = other._department;
            this->_job_title = other._job_title;
            this->_employment_date = other._employment_date;
            this->_decor_type = other._decor_type;
            this->_hash_field = other._hash_field;
            this->_model_hash = other._model_hash;
        } 
        catch (const std::exception& e) 
        {
            std::cout << e.what() << std::endl;
        }
    }

    /**
     * @brief Destructor for the Model class.
     */
    ~Model();

    /**
     * @brief Sets the properties of the model.
     * 
     * @param full_name The full name of the model.
     * @param department The department of the model.
     * @param job_title The job title of the model.
     * @param employment_date The employment date of the model.
     * @param model_hash The hash value of the model.
     * @param hash_field The hash field of the model.
     * @param optional_func An optional hash function for the model.
     */
    void set_model(std::string full_name, std::string department, std::string job_title, std::chrono::year_month_day employment_date, std::uint32_t model_hash = 0, std::uint8_t hash_field = 255, const std::optional<std::function<std::size_t(const std::string& value)>>& optional_func = std::nullopt);
    
    /**
     * @brief Sets the properties of the model.
     * 
     * @param full_name The full name of the model.
     * @param department The department of the model.
     * @param job_title The job title of the model.
     * @param employment_date The employment date of the model.
     * @param model_hash The hash value of the model.
     * @param hash_field The hash field of the model.
     * @param optional_func An optional hash function for the model.
     */
    void set_model(std::string full_name, std::string department, std::string job_title, std::string employment_date, std::uint32_t model_hash = 0, std::uint8_t hash_field = 255, const std::optional<std::function<std::size_t(const std::string& value)>>& optional_func = std::nullopt);
    
    /**
     * @brief Sets the decoration type of the model.
     * 
     * @param decor_type The decoration type.
     */
    void set_decor(std::uint8_t decor_type);

    /**
     * @brief Sets the hash function for the model.
     * 
     * @param hash_function The hash function to be set.
     */
    void set_hash_func(std::function<std::size_t(const std::string& value)> hash_fucntion);

    /**
     * @brief Sets the hash value for the model.
     * 
     * @param model_hash The hash value to be set.
     */
    void set_hash(std::uint32_t model_hash);

    /**
     * @brief Sets the hash field for the model.
     * 
     * @param hash_field The hash field to be set.
     */
    void set_hash_field(std::uint8_t hash_field);

    /**
     * @brief Compares the model with another model using specified comparison mode.
     * 
     * @param r_model The other model to compare with.
     * @param mode The comparison mode.
     * 
     * @return The comparison result as a ModelComp object.
     */
    ModelComp compare_type(const Model& r_model, std::uint8_t mode);

    /**
     * @brief Compares the model with a value of specified type using specified comparison mode.
     * 
     * @tparam T The type of the value to compare with.
     * @param mode The comparison mode.
     * @param r_value The value to compare with.
     * 
     * @return The comparison result as a ModelComp object.
     */
    template<typename T>
        ModelComp compare_type(std::uint8_t mode, T r_value);

    /**
     * @brief Gets the value of a specific field of the model.
     * 
     * @tparam T The type of the field.
     * @param field The field identifier.
     * 
     * @return The value of the field.
     */
    template<typename T>
        T get_field(std::uint8_t field) const;
    
    /**
     * @brief Sets the value of a specific field of the model.
     * 
     * @tparam T The type of the field.
     * @param field The field identifier.
     * 
     * @param value The value to set.
     */
    template<typename T>
        void set_field(std::uint8_t field, T value);

    /**
     * @brief Gets the hash value of the model.
     * 
     * @return The hash value.
     */
    std::uint32_t get_hash() const;

    /**
     * @brief Gets the hash field of the model.
     * 
     * @return The hash field.
     */
    std::uint8_t get_hash_field() const;

    /**
     * @brief Gets the hash field of the model.
     * 
     * @tparam T The type of the hash field.
     * 
     * @return The hash field.
     */
    template<typename T>
        T get_hash_field() const;

    /**
     * @brief Saves the model vector to a file.
     * 
     * @param model_vector The vector of models to be saved.
     * @param file_path The path of the file to save to.
     */
    static void save_model(const std::vector<Model>& model_vector, std::filesystem::path file_path);

    /**
     * @brief Loads models from a file into a model vector.
     * 
     * @param model_vector The vector to load the models into.
     * @param file_path The path of the file to load from.
     */
    static void load_model(std::vector<Model>& model_vector, std::filesystem::path file_path);

    /**
     * @brief Prints the models in the model vector.
     * 
     * @param model_vector The vector of models to print.
     */
    static void print_model(const std::vector<Model>& model_vector);

    /**
     * @brief Overloading the << operator for Model class.
     * 
     * @param stream The output stream.
     * @param model The model to be output.
     * 
     * @return The output stream after printing the model.
     */
    friend std::ostream& operator<< (std::ostream& stream, const Model& model);

    /**
     * @brief Overloaded less than operator for Model objects.
     *
     * @param l_model The left Model object.
     * @param r_model The right Model object.
     * 
     * @return The comparison result.
     */
    friend ModelComp     operator<  (const Model& l_model, const Model& r_model);

    /**
     * @brief Overloaded greater than operator for Model objects.
     *
     * @param l_model The left Model object.
     * @param r_model The right Model object.
     * 
     * @return The comparison result.
     */
    friend ModelComp     operator>  (const Model& l_model, const Model& r_model);

    /**
     * @brief Overloaded less than or equal to operator for Model objects.
     *
     * @param l_model The left Model object.
     * @param r_model The right Model object.
     * 
     * @return The comparison result.
     */
    friend ModelComp     operator<= (const Model& l_model, const Model& r_model);

    /**
     * @brief Overloaded greater than or equal to operator for Model objects.
     *
     * @param l_model The left Model object.
     * @param r_model The right Model object.
     * 
     * @return The comparison result.
     */
    friend ModelComp     operator>= (const Model& l_model, const Model& r_model);

    /**
     * @brief Overloaded equality operator for Model objects.
     *
     * @param l_model The left Model object.
     * @param r_model The right Model object.
     * 
     * @return The comparison result.
     */
    friend ModelComp     operator== (const Model& l_model, const Model& r_model);
    
    /**
     * @brief Overloaded inequality operator for Model objects.
     *
     * @param l_model The left Model object.
     * @param r_model The right Model object.
     * 
     * @return The comparison result.
     */
    friend ModelComp     operator!= (const Model& l_model, const Model& r_model);

private:
    std::string                     _full_name;
    std::string                     _department;
    std::string                     _job_title;
    std::chrono::year_month_day     _employment_date;

    std::uint8_t                    _decor_type;

    //HASHING
    std::uint8_t                    _hash_field;

    std::uint32_t                   _model_hash;
};

/**
 * @class ModelComp
 * @brief Represents the comparison result of two models.
 */
class ModelComp 
{
public:
    /**
     * @brief Constructor for ModelComp class.
     */
    ModelComp();

    /**
     * @brief Constructor for ModelComp class.
     *
     * @param value The value to initialize the ModelComp object.
     */
    ModelComp(std::uint8_t value);

    /**
     * @brief Destructor for ModelComp class.
     */
    ~ModelComp();

    /**
     * @brief Sets the type masked value at the given offset.
     *
     * @param value The value to set.
     * @param offset The offset at which to set the value.
     */
    void set_type_masked(std::uint8_t value, std::uint8_t offset);

    /**
     * @brief Sets the name type value.
     *
     * @param value The value to set.
     */
    void set_name_type(std::uint8_t value);

    /**
     * @brief Sets the department type value.
     *
     * @param value The value to set.
     */
    void set_dept_type(std::uint8_t value);

    /**
     * @brief Sets the job type value.
     *
     * @param value The value to set.
     */
    void set_jobt_type(std::uint8_t value);

    /**
     * @brief Sets the date type value.
     *
     * @param value The value to set.
     */
    void set_date_type(std::uint8_t value);

    /**
     * @brief Gets the type masked value at the given offset.
     *
     * @param offset The offset from which to retrieve the value.
     * 
     * @return The type masked value.
     */
    std::uint8_t get_type_masked(std::uint8_t offset) const;

    /**
     * @brief Gets the name type value.
     *
     * @return The name type value.
     */
    std::uint8_t get_name_type() const;

    /**
     * @brief Gets the department type value.
     *
     * @return The department type value.
     */
    std::uint8_t get_dept_type() const;

    /**
     * @brief Gets the job type value.
     *
     * @return The job type value.
     */
    std::uint8_t get_jobt_type() const;

    /**
     * @brief Gets the date type value.
     *
     * @return The date type value.
     */
    std::uint8_t get_date_type() const;

    /**
     * @brief Overloaded equality operator for ModelComp objects.
     *
     * @param l_bool The left ModelComp object.
     * @param r_bool The right ModelComp object.
     * 
     * @return The comparison result.
     */
    friend ModelComp operator== (const ModelComp& l_bool, const ModelComp& r_bool);

    /**
     * @brief Overloaded inequality operator for ModelComp objects.
     *
     * @param l_bool The left ModelComp object.
     * @param r_bool The right ModelComp object.
     * 
     * @return The comparison result.
     */
    friend ModelComp operator!= (const ModelComp& l_bool, const ModelComp& r_bool);

    /**
     * @brief Overloaded stream insertion operator for ModelComp objects.
     *
     * @param stream The output stream.
     * @param model The ModelComp object to insert.
     * 
     * @return The modified output stream.
     */
    friend std::ostream& operator<< (std::ostream& stream, const ModelComp& model);

    /**
     * @brief Overloaded logical NOT operator for ModelComp objects.
     *
     * @return The logical NOT of the ModelComp object.
     */
    ModelComp operator! () const; ///< The internal value of the ModelComp object.

private:
    std::uint8_t _value;
};


template<typename T>
ModelComp Model::compare_type(std::uint8_t mode, T r_value)
{
    int8_t comp_result = 4;
    ModelComp model_comp;
    
    if (mode > 3)
    {
        mode = 0;
    }

    switch (mode)
    {
    case 0:
        {
            if (std::is_same<T, decltype(this->_full_name)>::value)
            {
                comp_result = this->_full_name.compare(r_value);
                if (comp_result < 0)
                {
                    comp_result = 1;
                }
                else if(comp_result > 0)
                {
                    comp_result = 2;
                }
                else 
                {
                    comp_result = 0;
                }
            }
            else 
            {
                throw std::invalid_argument("r_value should be _full_name");
            }
            model_comp.set_name_type(comp_result);
            break;
        }
    case 1:
        {
            if (std::is_same<T, decltype(this->_department)>::value)
            {
                comp_result = this->_department.compare(r_value);
                if (comp_result < 0)
                {
                    comp_result = 1;
                }
                else if(comp_result > 0)
                {
                    comp_result = 2;
                }
                else 
                {
                    comp_result = 0;
                }
            }
            else 
            {
                throw std::invalid_argument("r_value should be _department");
            }
            model_comp.set_dept_type(comp_result);
            break;
        }
    case 2:
        {
            if (std::is_same<T, decltype(this->_job_title)>::value)
            {
                comp_result = this->_job_title.compare(r_value);
                if (comp_result < 0)
                {
                    comp_result = 1;
                }
                else if(comp_result > 0)
                {
                    comp_result = 2;
                }
                else 
                {
                    comp_result = 0;
                }
            }
            else 
            {
                throw std::invalid_argument("r_value should be _job_title");
            }
            model_comp.set_jobt_type(comp_result);
            break;
        }
    case 3:
        {

            throw std::invalid_argument("r_value should be _employment_date");
            model_comp.set_date_type(comp_result);
            break;
        }
    default:
        {
            break;
        }
    }

    return model_comp;
}

template<typename T>
T Model::get_field(std::uint8_t field) const
{
    switch (field)
    {
        
        case 1:
        {   if (std::is_same<T, decltype(this->_department)>::value)
            {
                return this->_department;
            }
            else 
            {
                throw std::invalid_argument("T should be _department");
            }
            break;
        }

        case 2:
        {   if (std::is_same<T, decltype(this->_job_title)>::value)
            {
                return this->_job_title;
            }
            else 
            {
                throw std::invalid_argument("T should be _job_title");
            }
            break;
        }

        case 3:
        {   
            throw std::invalid_argument("T should be _employment_date");
            break;
        }

        default:
        {   if (std::is_same<T, decltype(this->_full_name)>::value)
            {
                return this->_full_name;
            }
            else 
            {
                throw std::invalid_argument("T should be _full_name");
            }
            break;
        }

    }
}


template<typename T>
void Model::set_field(std::uint8_t field, T value)
{
    switch (field)
    {
        
        case 1:
        {   if (std::is_same<T, decltype(this->_department)>::value)
            {
                this->_department = value;
            }
            else 
            {
                throw std::invalid_argument("T should be _department");
            }
            break;
        }

        case 2:
        {   if (std::is_same<T, decltype(this->_job_title)>::value)
            {
                this->_job_title = value;
            }
            else 
            {
                throw std::invalid_argument("T should be _job_title");
            }
            break;
        }

        case 3:
        {   
            throw std::invalid_argument("T should be _employment_date");
            break;
        }

        default:
        {   if (std::is_same<T, decltype(this->_full_name)>::value)
            {
                this->_full_name = value;
            }
            else 
            {
                throw std::invalid_argument("T should be _full_name");
            }
            break;
        }

    }
}

template<typename T>
T Model::get_hash_field() const
{
    return this->get_field<T>(this->_hash_field);
}

#endif // MODEL_HPP
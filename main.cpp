/**
 * @file       <test.cpp>
 * @brief      This source file is an example of how to use sorting algorithms implemented for laboratory work 1. 
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
#include "./generator/generator.hpp"
#include <cstdint>

#ifndef MODEL_HPP
#include "../model/model.hpp"
#endif // MODEL_HPP

#include "./sorting/sorting.hpp"
#include "./search/search.hpp"

#include <iostream>
#include <random>
#include <boost/program_options.hpp>
#include <algorithm>
#include <bitset>
#include <string>
#include <thread>
#include <map>

namespace po = boost::program_options;

int main(int argc, char const *argv[])
{
	std::size_t amount;
    std::size_t iterations;
    std::size_t mode;
    bool silent;
    std::string file_path;
    std::string search_tag;

    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point finish;
    std::chrono::duration<double, std::milli> elapsed;

    po::options_description describtion("Default options");
    po::variables_map variable_map;

    describtion.add_options()
    	("help,H", 	"produces help message")
    	("amount,A", po::value<std::size_t>(&amount)->default_value(100), "determines how many lines does debug output prints")
        ("iteration,I", po::value<std::size_t>(&iterations)->default_value(10), "determines how many testion iterations there should be")
        ("mode,M", po::value<std::size_t>(&mode)->default_value(0), "determines wich row should be sorted")
        ("silent,S", po::value<bool>(&silent)->default_value(false), "mutes output of models")
        ("file_name,F", po::value<std::string>(&file_path)->default_value("./set_data/"), "specifies file path to write/load model without .json")
        ("value,V", po::value<std::string>(&search_tag)->default_value(" "), "specifies value, that should be searched for in the array")
        ("binary,B", "makes it so, that code runs lab 2")
        ("hashing,X", "makes it so, that code runs lab 3")
        ("random,R", "makes it so, that code runs lab 4")
        ("load,L", "loads model from file")
        ("generate,G", "generates model and writes it into file")
        ("test,T", "performs some tests on given data")
    	("debug,D", "prints out debug data");

    try 
    {
        po::store(po::parse_command_line(argc, argv, describtion), variable_map);
    }
    catch (std::exception const& exception)
    {
        std::cout << exception.what();
    }

    po::notify(variable_map);

    if (variable_map.count("help")) 
    {
        std::cout << describtion << std::endl;
        return 1;
    }

    std::vector<Model> model_vector;
    std::vector<std::vector<Model>> model_vector_set;

    std::filesystem::path avg_file_path(file_path);

    
    if (variable_map.count("generate"))
    {
        Generator generator;
        
        for (std::size_t iteration = 0; iteration < iterations; ++iteration)
        {
            start = std::chrono::high_resolution_clock::now();

            for (std::size_t index = 0; index < amount; ++index)
            {
                model_vector.push_back(generator.model_generator());
            }

            finish = std::chrono::high_resolution_clock::now();

            model_vector_set.push_back(model_vector);
            
            std::chrono::duration<double, std::milli> elapsed = finish - start;
            std::cout << "\t Iteration: " << iteration << "\t - Model generation took: " << elapsed.count() << " ms" << std::endl;

            if (variable_map.count("debug")) 
            {
                Model::print_model(model_vector);
            }

            if (avg_file_path.has_filename())
            {
                std::string file_extension = avg_file_path.extension().string();
                std::string new_filename = avg_file_path.filename().string();
                new_filename = new_filename.substr(0, new_filename.find_last_of("."));

                if (iterations != 1)
                {
                    new_filename += "_";
                    new_filename += std::to_string(iteration);
                }
    
                avg_file_path.replace_extension("");
                avg_file_path.replace_filename(new_filename + file_extension);

                Model::save_model(model_vector, avg_file_path);
            }
            else
            {
                Model::save_model(model_vector, std::filesystem::path(avg_file_path.string() + "model_data_" + std::to_string(iteration) + ".json"));
            }
        }
    }
    else if (variable_map.count("load"))
    {
        for (std::size_t iteration = 0; iteration < iterations; ++iteration)
        {
            if (avg_file_path.has_filename())
            {
                std::string file_extension = avg_file_path.extension().string();
                std::string new_filename = avg_file_path.filename().string();
                new_filename = new_filename.substr(0, new_filename.find_last_of("."));

                if (iterations != 1)
                {
                    new_filename += "_";
                    new_filename += std::to_string(iteration);
                }
    
                avg_file_path.replace_extension("");
                avg_file_path.replace_filename(new_filename + file_extension);

                Model::load_model(model_vector, avg_file_path);
            }
            else
            {
                std::cout << "Loading: " << std::filesystem::path(avg_file_path.string() + "model_data_" + std::to_string(iteration) + ".json") << std::endl;
                Model::load_model(model_vector, std::filesystem::path(avg_file_path.string() + "model_data_" + std::to_string(iteration) + ".json"));
            }

            model_vector_set.push_back(model_vector);

            if (variable_map.count("debug")) 
            {
                Model::print_model(model_vector);
            }
        }
    }

    if (variable_map.count("test"))
    {
        std::vector<Model> test_model_vector;

        // Bubble sorting
        std::cout << std::endl << "Bubble sorting: " << "\n";  

        for (std::size_t iteration = 0; iteration < iterations; ++iteration)
        {
            test_model_vector = model_vector_set.at(iteration);

            start = std::chrono::high_resolution_clock::now();

            Sorting::bubble_sort(test_model_vector, mode);

            finish = std::chrono::high_resolution_clock::now();
        
            elapsed = finish - start;
            std::cout << "\t Iteration: " << iteration << "\t - Sorting took: " << std::fixed << std::setprecision(6) << elapsed.count() << "\t ms" << std::endl;

            if (variable_map.count("debug")) 
            {
                Model::print_model(test_model_vector);
            }
        }

        // Heap sorting
        std::cout << "Heap sorting: " << "\n";  

        for (std::size_t iteration = 0; iteration < iterations; ++iteration)
        {
            test_model_vector = model_vector_set.at(iteration);

            start = std::chrono::high_resolution_clock::now();

            Sorting::heap_sort(test_model_vector, mode);

            finish = std::chrono::high_resolution_clock::now();
        
            elapsed = finish - start;
            std::cout << "\t Iteration: " << iteration << "\t - Sorting took: " << std::fixed << std::setprecision(6) << elapsed.count() << "\t ms" << std::endl;

            if (variable_map.count("debug")) 
            {
                Model::print_model(test_model_vector);
            }
        }

        // Merge sorting
        std::cout << "Merge sorting: " << "\n";  

        for (std::size_t iteration = 0; iteration < iterations; ++iteration)
        {
            test_model_vector = model_vector_set.at(iteration);

            start = std::chrono::high_resolution_clock::now();

            Sorting::merge_sort(test_model_vector, mode);

            finish = std::chrono::high_resolution_clock::now();
        
            elapsed = finish - start;
            std::cout << "\t Iteration: " << iteration << "\t - Sorting took: " << std::fixed << std::setprecision(6) << elapsed.count() << "\t ms" << std::endl;

            if (variable_map.count("debug")) 
            {
                Model::print_model(test_model_vector);
            }
        }
        
    }

    if (variable_map.count("binary"))
    {
        int serching_result = 0;
        std::vector<Model> test_model_vector;

        std::cout << "Straight searching: " << "\n";  

        for (std::size_t iteration = 0; iteration < iterations; ++iteration)
        {
            test_model_vector = model_vector_set.at(iteration);

            start = std::chrono::high_resolution_clock::now();

            serching_result = Search::straight_search<std::string>(test_model_vector, search_tag, mode);

            finish = std::chrono::high_resolution_clock::now();
        
            elapsed = finish - start;
            std::cout << "\t Iteration: " << iteration << " found at: " << serching_result << "\t - Searching took: " << std::fixed << std::setprecision(6) << elapsed.count() << "\t ms" << std::endl;

            if (variable_map.count("debug")) 
            {
                std::cout << search_tag << /*test_model_vector.at(serching_result)*/" " << std::endl;
            }
        }

        std::cout << "Binary searching (no sort): " << "\n";  

        for (std::size_t iteration = 0; iteration < iterations; ++iteration)
        {
            test_model_vector = model_vector_set.at(iteration);

            Sorting::heap_sort(test_model_vector, mode);

            start = std::chrono::high_resolution_clock::now();

            serching_result = Search::binary_search<std::string>(test_model_vector, search_tag, mode);

            finish = std::chrono::high_resolution_clock::now();
        
            elapsed = finish - start;
            std::cout << "\t Iteration: " << iteration << " found at: " << serching_result << "\t - Searching took: " << std::fixed << std::setprecision(6) << elapsed.count() << "\t ms" << std::endl;

            if (variable_map.count("debug")) 
            {
                std::cout << search_tag << /*test_model_vector.at(serching_result)*/" " << std::endl;
            }
        }

        std::cout << "Binary searching (sort): " << "\n";  

        for (std::size_t iteration = 0; iteration < iterations; ++iteration)
        {
            test_model_vector = model_vector_set.at(iteration);

            start = std::chrono::high_resolution_clock::now();

            Sorting::heap_sort(test_model_vector, mode);

            serching_result = Search::binary_search<std::string>(test_model_vector, search_tag, mode);

            finish = std::chrono::high_resolution_clock::now();
        
            elapsed = finish - start;
            std::cout << "\t Iteration: " << iteration << " found at: " << serching_result << "\t - Searching took: " << std::fixed << std::setprecision(6) << elapsed.count() << "\t ms" << std::endl;

            if (variable_map.count("debug")) 
            {
                std::cout << test_model_vector.at(serching_result) << std::endl;
            }
        }

        std::cout << "Map key searching: " << "\n"; 
        for (std::size_t iteration = 0; iteration < iterations; ++iteration)
        {
            test_model_vector = model_vector_set.at(iteration);
            std::map<std::string, std::size_t> test_model_map;
            std::map<std::string, std::size_t>::iterator test_model_iterator;

            for (std::size_t iteration = 0; iteration < test_model_vector.size(); ++iteration)
            {
                test_model_map.insert({test_model_vector.at(iteration).get_field<std::string>(mode), iteration});
            }

            start = std::chrono::high_resolution_clock::now();

            test_model_iterator = test_model_map.find(search_tag);

            finish = std::chrono::high_resolution_clock::now();
        
            elapsed = finish - start;

            std::cout << "\t Iteration: " << iteration << " found at: " << test_model_iterator->second << "\t - Searching took: " << std::fixed << std::setprecision(6) << elapsed.count() << "\t ms" << std::endl;

            if (variable_map.count("debug")) 
            {
                std::cout << test_model_vector.at(test_model_iterator->second) << std::endl;
            }
        }
    }

    if (variable_map.count("hashing"))
    {
        std::optional<Model> serching_result;
        std::vector<Model> test_model_vector;
        std::vector<std::list<Model>> hashing_table;
        
        std::uint32_t searching_hash = Hashing::basic_hashing_function(search_tag);

        std::cout << "Simple hash table search searching: " << "\n";  

        for (std::size_t iteration = 0; iteration < iterations; ++iteration)
        {
            test_model_vector = model_vector_set.at(iteration);

            start = std::chrono::high_resolution_clock::now();

            hashing_table = Hashing::hash_model(test_model_vector, &Hashing::basic_hashing_function);

            finish = std::chrono::high_resolution_clock::now();
        
            elapsed = finish - start;
            std::cout << "\t Hashing: " << iteration << "\t - Hashing took: " << std::fixed << std::setprecision(6) << elapsed.count() << "\t ms" << "\t There were total of: " << Hashing::count_collisions(hashing_table) << " collisions. " << std::endl;

            if (variable_map.count("debug")) 
            {
                std::cout << search_tag << /*test_model_vector.at(serching_result)*/" " << std::endl;
            }

            start = std::chrono::high_resolution_clock::now();

            serching_result = Hashing::find_in_hash_table(hashing_table, searching_hash, test_model_vector.size());

            finish = std::chrono::high_resolution_clock::now();
        
            elapsed = finish - start;
            
            std::cout << "\t Iteration: " << iteration << " found: " << ((serching_result.has_value() == true) ? serching_result.value().get_field<std::string>(0) : "\b\b\b\b\b\b\bnot found") << "\t - Searching took: " << std::fixed << std::setprecision(6) << elapsed.count() << "\t ms" << std::endl;

            if (variable_map.count("debug")) 
            {
                std::cout << search_tag << /*test_model_vector.at(serching_result)*/" " << std::endl;
            }
        }

        std::cout << "Djb2 hash table search searching: " << "\n";  

        searching_hash = Hashing::djb2_hashing_function(search_tag);

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        for (std::size_t iteration = 0; iteration < iterations; ++iteration)
        {
            test_model_vector = model_vector_set.at(iteration);

            start = std::chrono::high_resolution_clock::now();

            hashing_table = Hashing::hash_model(test_model_vector, &Hashing::djb2_hashing_function);

            finish = std::chrono::high_resolution_clock::now();
        
            elapsed = finish - start;
            std::cout << "\t Hashing: " << iteration << "\t - Hashing took: " << std::fixed << std::setprecision(6) << elapsed.count() << "\t ms" << "\t There were total of: " << Hashing::count_collisions(hashing_table) << " collisions. " << std::endl;

            if (variable_map.count("debug")) 
            {
                std::cout << search_tag << /*test_model_vector.at(serching_result)*/" " << std::endl;
            }

            start = std::chrono::high_resolution_clock::now();

            serching_result = Hashing::find_in_hash_table(hashing_table, searching_hash, test_model_vector.size());

            finish = std::chrono::high_resolution_clock::now();
        
            elapsed = finish - start;
            
            std::cout << "\t Iteration: " << iteration << " found: " << ((serching_result.has_value() == true) ? serching_result.value().get_field<std::string>(0) : "\b\b\b\b\b\b\bnot found") << "\t - Searching took: " << std::fixed << std::setprecision(6) << elapsed.count() << "\t ms" << std::endl;

            if (variable_map.count("debug")) 
            {
                std::cout << search_tag << /*test_model_vector.at(serching_result)*/" " << std::endl;
            }
        }

        std::cout << "Advanced hash table search searching: " << "\n";  
        
        searching_hash = Hashing::advanced_hashing_function(search_tag);

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        for (std::size_t iteration = 0; iteration < iterations; ++iteration)
        {
            test_model_vector = model_vector_set.at(iteration);

            start = std::chrono::high_resolution_clock::now();

            hashing_table = Hashing::hash_model(test_model_vector, &Hashing::advanced_hashing_function);

            finish = std::chrono::high_resolution_clock::now();
        
            elapsed = finish - start;
            std::cout << "\t Hashing: " << iteration << "\t - Hashing took: " << std::fixed << std::setprecision(6) << elapsed.count() << "\t ms" << "\t There were total of: " << Hashing::count_collisions(hashing_table) << " collisions. " << std::endl;

            if (variable_map.count("debug")) 
            {
                std::cout << search_tag << /*test_model_vector.at(serching_result)*/" " << std::endl;
            }

            start = std::chrono::high_resolution_clock::now();

            serching_result = Hashing::find_in_hash_table(hashing_table, searching_hash, test_model_vector.size());

            finish = std::chrono::high_resolution_clock::now();
        
            elapsed = finish - start;
            
            std::cout << "\t Iteration: " << iteration << " found: " << ((serching_result.has_value() == true) ? serching_result.value().get_field<std::string>(0) : "\b\b\b\b\b\b\bnot found") << "\t - Searching took: " << std::fixed << std::setprecision(6) << elapsed.count() << "\t ms" << std::endl;

            if (variable_map.count("debug")) 
            {
                std::cout << search_tag << /*test_model_vector.at(serching_result)*/" " << std::endl;
            }
        }
    }

    if (variable_map.count("random"))
    {

        std::size_t distribuion_length = 0;

        std::cout << "Pseudo random number generation (xor uniform): " << "\n";

        std::vector<std::size_t> rng_set_len = {50, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};

        for (std::size_t iteration = 0; iteration < iterations; ++iteration)
        {
            distribuion_length = rng_set_len[iteration];

            start = std::chrono::high_resolution_clock::now();

            std::vector<unsigned int> distibution_array = PseusoRandom::xor_generate_n(distribuion_length);

            finish = std::chrono::high_resolution_clock::now();
        
            elapsed = finish - start;

            std::cout << "\t Iteration: " << iteration << " with: " << distribuion_length << " generateed numbers took: " << std::fixed << std::setprecision(6) << elapsed.count() << "\t ms" << std::endl;

            if (variable_map.count("debug")) 
            {
                PseusoRandomUtilities::analyze_samples(distibution_array);
            }
        }

        std::cout << "Pseudo random number generation (normal): " << "\n";

        for (std::size_t iteration = 0; iteration < iterations; ++iteration)
        {
            distribuion_length = rng_set_len[iteration];

            start = std::chrono::high_resolution_clock::now();

            std::vector<int> distibution_array = PseusoRandom::generate_normal_n<int, 1>(distribuion_length);

            finish = std::chrono::high_resolution_clock::now();
        
            elapsed = finish - start;

            std::cout << "\t Iteration: " << iteration << " with: " << distribuion_length << " generateed numbers took: " << std::fixed << std::setprecision(6) << elapsed.count() << "\t ms" << std::endl;
            
            if (variable_map.count("debug")) 
            {
                PseusoRandomUtilities::analyze_samples(distibution_array);
            }
        }

        std::cout << "Pseudo random number generation (uniform): " << "\n";
        for (std::size_t iteration = 0; iteration < iterations; ++iteration)
        {
            distribuion_length = rng_set_len[iteration];

            start = std::chrono::high_resolution_clock::now();

            std::vector<int> distibution_array = PseusoRandom::generate_uniform_n<int, 1>(distribuion_length);

            finish = std::chrono::high_resolution_clock::now();
        
            elapsed = finish - start;
            std::cout << "\t Iteration: " << iteration << " with: " << distribuion_length << " generateed numbers took: " << std::fixed << std::setprecision(6) << elapsed.count() << "\t ms" << std::endl;

            if (variable_map.count("debug")) 
            {
                PseusoRandomUtilities::analyze_samples(distibution_array);
            }
        }

        std::cout << "Pseudo random number generation (STL): " << "\n";

        for (std::size_t iteration = 0; iteration < iterations; ++iteration)
        {
            distribuion_length = rng_set_len[iteration];

            start = std::chrono::high_resolution_clock::now();

            std::random_device rnd_device;
            std::mt19937 mersenne_engine {rnd_device()};
            std::uniform_real_distribution<double> dist {0, 2147483647};
    
            auto gen = [&dist, &mersenne_engine](){
                   return dist(mersenne_engine);
                };

            std::vector<double> distibution_array(distribuion_length);
            generate(begin(distibution_array), end(distibution_array), gen);

            finish = std::chrono::high_resolution_clock::now();
        
            elapsed = finish - start;
            std::cout << "\t Iteration: " << iteration << " with: " << distribuion_length << " generateed numbers took: " << std::fixed << std::setprecision(6) << elapsed.count() << "\t ms" << std::endl;

            if (variable_map.count("debug")) 
            {
                PseusoRandomUtilities::analyze_samples(distibution_array);
            }
        }
    }

	return 0;
}

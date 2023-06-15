/**
 * @file       <model.cpp>
 * @brief      This source file holds implementation of Model class. 
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
#include "model.hpp"

std::uint32_t Hashing::basic_hashing_function(const std::string& value)
{
    std::uint32_t hash = 0;

    for (char ch : value) 
    {
        hash = (hash * 31) + static_cast<std::uint32_t>(ch);
    }

    return hash;
}

std::uint32_t Hashing::djb2_hashing_function(const std::string& value)
{
    std::uint32_t hash = 5381; 

    for (char ch : value) 
    {
        hash = ((hash << 5) + hash) ^ static_cast<std::uint32_t>(ch); 
    }

    return hash;
}

std::uint32_t Hashing::advanced_hashing_function(const std::string& value)
{
    std::uint32_t hash = 0;

    for(std::size_t i = 0; i < value.length(); i++)
    {
        hash = ((((value[i] << 5) + hash) >> 7) * 976531);
    }

    return (hash & 0x7FFFFFFFFFFFFF);
}

std::uint32_t Hashing::count_collisions(const std::vector<std::list<Model>>& hash_table)
{
    std::uint32_t collisions = 0;

    for (auto object : hash_table) 
    {
        if (object.size() > 1)
        {
            collisions += (object.size() - 1);
        }
    }

    return collisions;
}

std::vector<std::list<Model>> Hashing::hash_model(std::vector<Model>& model_vector, std::function<std::size_t(const std::string& value)> hash_function)
{
    std::vector<std::list<Model>> table{model_vector.size()};

    for (std::size_t index = 0; index < model_vector.size(); ++index)
    {
        model_vector[index].set_hash_func(hash_function);
        std::uint32_t hash = model_vector[index].get_hash();
        table[hash % table.size()].push_back(model_vector[index]);
    }
    return table;
}


std::optional<Model> Hashing::Hashing::find_in_hash_table(const std::vector<std::list<Model>>& hash_table, std::uint32_t hash,  std::size_t size)
{
    std::uint32_t index = hash % size;

    if (index < size)
    {
        for (const Model& object : hash_table[index]) 
        {
            if (object.get_hash() == hash) 
            {   
                return object;
            }
        }
    }
    return std::nullopt;
}

Model::Model(std::string full_name, std::string department, std::string job_title, std::chrono::year_month_day employment_date, std::uint32_t model_hash, std::uint8_t hash_field, const std::optional<std::function<std::size_t(const std::string& value)>>& optional_func)
{
    this->set_model(full_name, department, job_title, employment_date, model_hash, hash_field, optional_func);
}

Model::Model(std::string full_name, std::string department, std::string job_title, std::string employment_date, std::uint32_t model_hash, std::uint8_t hash_field, const std::optional<std::function<std::size_t(const std::string& value)>>& optional_func)
{
    this->set_model(full_name, department, job_title, employment_date, model_hash, hash_field, optional_func);
}

Model::Model(std::uint8_t decor_type)
{
    this->set_decor(decor_type);
}

Model::~Model()
{
    return;
}

void Model::set_model(std::string full_name, std::string department, std::string job_title, std::chrono::year_month_day employment_date, std::uint32_t model_hash, std::uint8_t hash_field, const std::optional<std::function<std::size_t(const std::string& value)>>& optional_func)
{
    this->_full_name         = full_name;
    this->_department        = department;
    this->_job_title         = job_title;
    this->_employment_date   = employment_date;
    this->_decor_type        = 2; 
    this->_hash_field        = hash_field;

    if (!optional_func.has_value())
    {
        if (hash_field != 255)
        {
            this->_model_hash = model_hash;
        }
        else
        { 
            this->_model_hash = 0;
        }
    }
    else 
    {
        this->_model_hash = optional_func.value()(this->get_field<std::string>(hash_field));
    }
}

void Model::set_model(std::string full_name, std::string department, std::string job_title, std::string employment_date, std::uint32_t model_hash, std::uint8_t hash_field, const std::optional<std::function<std::size_t(const std::string& value)>>& optional_func)
{
    std::vector<std::string> splitted_date;

    std::string buffer;

    for (std::size_t index = 0; index < 3; ++index)
    {
        splitted_date.push_back(employment_date.substr(0, employment_date.find('/')));
        employment_date = employment_date.substr(employment_date.find('/') + 1, employment_date.end() - employment_date.begin());
    }

    std::chrono::year_month_day parced_employment_date(std::chrono::year(std::stoi(splitted_date[0])), std::chrono::month(std::stoi(splitted_date[1])), std::chrono::day(std::stoi(splitted_date[2])));

    this->set_model(full_name, department, job_title, parced_employment_date, model_hash, hash_field, optional_func);
}

void Model::set_decor(std::uint8_t decor_type)
{
    this->_decor_type = decor_type;
}

void Model::set_hash_func(std::function<std::size_t(const std::string& value)> hash_fucntion)
{
    this->_model_hash = hash_fucntion(this->get_field<std::string>(this->_hash_field));
}

void Model::set_hash(std::uint32_t model_hash)
{
    this->_model_hash = model_hash;
}

void Model::set_hash_field(std::uint8_t hash_field)
{
    this->_hash_field = hash_field;
}

ModelComp Model::compare_type(const Model& r_model, std::uint8_t mode)
{
    int8_t comp_result;
    ModelComp model_comp;
    
    if (mode > 3)
    {
        mode = 0;
    }

    switch (mode)
    {
    case 0:
        {
            comp_result = this->_full_name.compare(r_model._full_name);
            if (comp_result <= 0)
            {
                comp_result = 0;
            }
            else 
            {
                comp_result = 1;
            }
            model_comp.set_name_type(comp_result);
            break;
        }
    case 1:
        {
            comp_result = this->_department.compare(r_model._department);
            if (comp_result <= 0)
            {
                comp_result = 0;
            }
            else 
            {
                comp_result = 1;
            }
            model_comp.set_dept_type(comp_result);
            break;
        }
    case 2:
        {
            comp_result = this->_job_title.compare(r_model._job_title);
            if (comp_result <= 0)
            {
                comp_result = 0;
            }
            else 
            {
                comp_result = 1;
            }
            model_comp.set_jobt_type(comp_result);
            break;
        }
    case 3:
        {
            if (this->_employment_date <= r_model._employment_date)
            {
                comp_result = 0;
            }
            else 
            {
                comp_result = 1;
            }
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

void Model::save_model(const std::vector<Model>& model_vector, std::filesystem::path file_path)
{
    std::ofstream out(file_path);
    out << "{\"model_vecotr\":[";

    bool first = true;
    for (const auto& model : model_vector) 
    {
        if (!first) {
            out << ",";
        } else {
            first = false;
        }

        boost::json::object obj;

        obj.emplace("full_name", model._full_name);
        obj.emplace("department", model._department);
        obj.emplace("job_title", model._job_title);
        obj.emplace("employment_date_year", static_cast<int>(model._employment_date.year()));
        obj.emplace("employment_date_month", static_cast<unsigned>(model._employment_date.month()));
        obj.emplace("employment_date_day", static_cast<unsigned>(model._employment_date.day()));

        out << boost::json::serialize(obj);
    }

    out << "]}";
    out.close();
}

void Model::load_model(std::vector<Model>& model_vector, std::filesystem::path file_path) 
{
    std::ifstream in(file_path, std::ios::binary);
    
    if (!in.is_open()) 
    {
        throw std::runtime_error("Failed to open file: " + file_path.string());
    }

    boost::json::stream_parser parser;
    char buffer[4096];

    while (in.read(buffer, sizeof(buffer))) 
    {
        parser.write(buffer, sizeof(buffer));
    }

    if (in.gcount() > 0) 
    {
        parser.write(buffer, in.gcount());
    }

    in.close();

    boost::json::value value = parser.release();

    boost::json::object obj = value.as_object();
    boost::json::array rows = obj["model_vecotr"].as_array();

    model_vector.clear();
    for (const auto& row : rows) 
    {
        boost::json::object obj = row.as_object();

        std::string full_name = obj.at("full_name").as_string().c_str();
        std::string department = obj.at("department").as_string().c_str();
        std::string job_title = obj.at("job_title").as_string().c_str();
        int year = obj.at("employment_date_year").as_int64();
        unsigned month = obj.at("employment_date_month").as_int64();
        unsigned day = obj.at("employment_date_day").as_int64();

        std::chrono::year_month_day employment_date = std::chrono::year_month_day(std::chrono::year(year), std::chrono::month(month), std::chrono::day(day));

        model_vector.emplace_back(full_name, department, job_title, employment_date);
    }

    return;
}
std::uint32_t Model::get_hash() const
{
    return this->_model_hash;
}

std::uint8_t Model::get_hash_field() const
{
    return this->_hash_field;
}

void Model::print_model(const std::vector<Model>& model_vector)
{
    std::cout << Model(3) << std::endl;
    std::cout << Model(0) << std::endl;

    for (std::size_t index = 0; index < model_vector.size(); ++index)
    {
        if (index == model_vector.size() - 1)
        {
            Model temp = model_vector.at(index);
            temp.set_decor(1);
            std::cout << temp << std::endl;
        }
        else 
        {
            std::cout << model_vector[index] << std::endl;
        }
    }

    std::cout << Model(4) << std::endl;
}

std::ostream& operator<< (std::ostream& stream, const Model& model)
{
    if (model._decor_type == 0)
    {
        stream << "║                           FULL  NAME                           ║                 DEPARTMENT                 ║                 JOB  TITLE                 ║    DATE    ║";
    }
    else if (model._decor_type <= 2)
    {
        stream << "║ "  << std::setfill(' ') << std::setw(62) 
                   << model._full_name
                   << " ║ " << std::setfill(' ') << std::setw(42)
                   << model._department
                   << " ║ " << std::setfill(' ') << std::setw(42)
                   << model._job_title
                   << " ║ " << std::setfill('0') << std::setw(4)
                   << static_cast<int>(model._employment_date.year())
                   << "/"  << std::setfill('0') << std::setw(2)
                   << static_cast<unsigned>(model._employment_date.month())
                   << "/"  << std::setfill('0') << std::setw(2)
                   << static_cast<unsigned>(model._employment_date.day()) << " ║";
    }

    if (model._decor_type != 1)
    {
        std::string left_decor;
        std::string right_decor;
        std::string middle_decor;

        switch (model._decor_type)
        {
        case 0:
        case 2:
            {
                stream << "\n";
                left_decor      = "╠";
                right_decor     = "╣";
                middle_decor    = "╬";
                break;
            }
        case 3:
            {
                left_decor      = "╔";
                right_decor     = "╗";
                middle_decor    = "╦";
                break;
            }
        default:
            {
                left_decor      = "╚";
                right_decor     = "╝";
                middle_decor    = "╩";
            }
        }

        stream << left_decor;

        for (std::size_t index = 0; index < 64; ++index)
        {
            stream << "═";
        }

        for (std::size_t index = 0; index < 2; ++index)
        {
            stream << middle_decor;

            for (std::size_t index_in = 0; index_in < 44; ++index_in)
            {
                stream << "═";
            }
        }

        stream << middle_decor;

        for (std::size_t index = 0; index < 12; ++index)
        {
            stream << "═";
        }

        stream << right_decor;
    }

    return stream;
}

ModelComp operator< (const Model& l_model, const Model& r_model)
{
    std::uint8_t name_comp = 1;
    std::uint8_t dept_comp = 1;
    std::uint8_t jobt_comp = 1;
    std::uint8_t date_comp = 1;

    int8_t comp_result = l_model._full_name.compare(r_model._full_name);

    if (comp_result >= 0)
    {
        name_comp = 0;
    }

    comp_result = l_model._department.compare(r_model._department);

    if (comp_result >= 0)
    {
        dept_comp = 0;
    }

    comp_result = l_model._job_title.compare(r_model._job_title);

    if (comp_result >= 0)
    {
        jobt_comp = 0;
    }

    if (l_model._employment_date >= r_model._employment_date)
    {
        date_comp = 0;
    }
    ModelComp model_comp;
    model_comp.set_name_type(name_comp);
    model_comp.set_dept_type(dept_comp);
    model_comp.set_jobt_type(jobt_comp);
    model_comp.set_date_type(date_comp);

    return model_comp;
}

ModelComp operator>= (const Model& l_model, const Model& r_model)
{
    return (r_model < l_model);
}

ModelComp operator<= (const Model& l_model, const Model& r_model)
{
    return !(r_model < l_model);
}

ModelComp operator> (const Model& l_model, const Model& r_model)
{
    return !(l_model < r_model);
}

ModelComp operator== (const Model& l_model, const Model& r_model)
{
    std::uint8_t name_comp = 1;
    std::uint8_t dept_comp = 1;
    std::uint8_t jobt_comp = 1;
    std::uint8_t date_comp = 1;

    std::uint8_t comp_result = std::strcmp(l_model._full_name.c_str(), r_model._full_name.c_str());

    if (comp_result != 0)
    {
        name_comp = 0;
    }

    comp_result = std::strcmp(l_model._department.c_str(), r_model._department.c_str());

    if (comp_result != 0)
    {
        dept_comp = 0;
    }

    comp_result = std::strcmp(l_model._job_title.c_str(), r_model._job_title.c_str());

    if (comp_result != 0)
    {
        jobt_comp = 0;
    }

    if (l_model._employment_date != r_model._employment_date)
    {
        date_comp = 0;
    }

    ModelComp model_comp;
    model_comp.set_name_type(name_comp);
    model_comp.set_dept_type(dept_comp);
    model_comp.set_jobt_type(jobt_comp);
    model_comp.set_date_type(date_comp);

    return model_comp;
}

ModelComp operator!= (const Model& l_model, const Model& r_model)
{
    return !(l_model == r_model);
}


ModelComp::ModelComp()
{
    this->_value = 0;
}

ModelComp::ModelComp(std::uint8_t value)
{
    this->_value = value;
}

ModelComp::~ModelComp()
{

}

void ModelComp::set_type_masked(std::uint8_t value, std::uint8_t offset)
{
    this->_value = ((value & 0b00000011) << offset) ^ this->_value;
    return;
}

void ModelComp::set_name_type(std::uint8_t value)
{
    this->set_type_masked(value, 0);
    return;
}

void ModelComp::set_dept_type(std::uint8_t value)
{
    this->set_type_masked(value, 2);
    return;
}

void ModelComp::set_jobt_type(std::uint8_t value)
{
    this->set_type_masked(value, 4);
    return;
}

void ModelComp::set_date_type(std::uint8_t value)
{
    this->set_type_masked(value, 6);
    return;
}

std::uint8_t ModelComp::get_type_masked(std::uint8_t offset) const
{
    return (this->_value & (0b00000011 << offset)) >> offset;
}

std::uint8_t ModelComp::get_name_type() const
{
    return this->get_type_masked(0);
}

std::uint8_t ModelComp::get_dept_type() const
{
    return this->get_type_masked(2);
}

std::uint8_t ModelComp::get_jobt_type() const
{   
    return this->get_type_masked(4);
}

std::uint8_t ModelComp::get_date_type() const
{
    return this->get_type_masked(6);
}

ModelComp ModelComp::operator! () const
{
    ModelComp result(~this->_value);
    return result;
}

ModelComp operator== (const ModelComp& l_bool, const ModelComp& r_bool)
{
    ModelComp result(0);

    if (l_bool.get_name_type() == r_bool.get_name_type())
    {
        result.set_name_type(1);
    }

    if (l_bool.get_dept_type() == r_bool.get_dept_type())
    {
        result.set_dept_type(1);
    }

    if (l_bool.get_jobt_type() == r_bool.get_jobt_type())
    {
        result.set_jobt_type(1);
    }

    if (l_bool.get_date_type() == r_bool.get_date_type())
    {
        result.set_date_type(1);
    }

    return result;
}

ModelComp operator!= (const ModelComp& l_bool, const ModelComp& r_bool)
{
    return !(l_bool == r_bool);
}

std::ostream& operator<< (std::ostream& stream, const ModelComp& r_bool)
{
    stream << std::bitset<8>(r_bool._value);

    return stream;
}

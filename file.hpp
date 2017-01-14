#ifndef FILE_HPP
#define FILE_HPP

#include <iostream>
#include <stdio.h>
#include <stdexcept>
#include <memory>

namespace fileutils
{
class FileException : public std::exception
{
public:
    FileException(const std::string& msg) : _msg{msg}
    {}
    virtual const char* what() const throw()
    {
        return _msg.c_str();
    }
    virtual ~FileException() throw() {}
private:
    std::string _msg;
};

class File
{
public:
    File() : _file_path{""}, _mode{""}, _file{NULL}
    {}

    explicit File(const std::string& path, const std::string& mode) :
        _file_path{path}, _mode{mode}
    {
        std::cout << "[Constructor] BEGIN\n";
        _file = fopen(path.c_str(), mode.c_str());
        if( _file == NULL )
        {
            throw FileException("Could not open file" + _file_path);
        }
        std::cout << "[Constructor] END\n";
    }

    File( const File& other ) :
        _file_path{other._file_path},
        _mode{other._mode}
    {
        std::cout << "[Copy constructor] BEGIN\n";
        _file = fopen(_file_path.c_str(), _mode.c_str());
        if( _file == NULL )
        {
            throw FileException("Could not open file" + _file_path);
        }
        std::cout << "[Copy constructor] END\n";
    }

    File& operator=( const File& other)
    {
        std::cout << "[Copy assignment operator] BEGIN\n";
        if( this != &other )
        {
            if( _file != NULL )
            {
                fclose(_file);
            }

            _file_path = other._file_path;
            _mode = other._mode;
            _file = fopen(_file_path.c_str(), _mode.c_str());
            if( _file == NULL )
            {
                throw FileException("Could not open file" + _file_path);
            }
        }
        std::cout << "[Copy assignment operator] END\n";
        return *this;
    }

    File( File&& other) : _file(NULL)
    {
        std::cout << "[Move constructor] BEGIN\n";
        _file = other._file;
        other._file = NULL;
        std::cout << "[Move constructor] END\n";
    }

    File& operator=(File&& other)
    {
        std::cout << "[Move asignment operator] BEGIN\n";
        if( this != &other )
        {
            if( _file != NULL )
            {
                fclose(_file);
            }
            _file = other._file;
            _file_path = other._file_path;
            _mode = other._mode;
            other._file = NULL;
            other._file_path.clear();
            other._mode.clear();
        }
        std::cout << "[Move asignment operator] END\n";
        return *this;
    }

    const std::string getText()
    {
        if( _file == NULL )
        {
            throw FileException("File is NULL");
        }

        fseek(_file, 0, SEEK_END);
        long length = ftell(_file);
        fseek(_file, 0, SEEK_SET);
        std::unique_ptr<char> p{new char[length]};
        fread(p.get(), 1, length, _file);
        return std::string(p.get(), length);
    }

    ~File()
    {
        // std::cout << "[Destructor] BEGIN\n";
        if( _file != NULL )
        {
            fclose(_file);
            _file = NULL;
        }
        // std::cout << "[Destructor] END\n";
    }

private:
    std::string _file_path;
    std::string _mode;
    FILE* _file;
};
}
#endif // FILE_HPP

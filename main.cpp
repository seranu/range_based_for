#include <iostream>
#include <vector>
#include "file.hpp"
#include "container.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    fileutils::File f1("/home/serbanu/work/qt-projects/custom_iterator/1.txt", "r");
    fileutils::File f2("/home/serbanu/work/qt-projects/custom_iterator/2.txt", "r");
    fileutils::File f3(f2);
    fileutils::File f4;
//    string contents = f1.getText();
//    f2 = f1;
//    f4 = std::move(f1);
//    //cout << f1.getText();
    container::Container<fileutils::File> vect(2);
//    vect.push_back(f4);
//    vect.push_back(std::move(f2));
//    vect.push_back(std::move(f3));
    vector<fileutils::File> v;
    v.push_back(std::move(f1));
    v.push_back(std::move(f2));


    for( auto file : vect )
    {
        cout << file.getText();
    }
//    cout << vect[0].getText();
//    cout << "Hello World!" << endl;
    return 0;
}

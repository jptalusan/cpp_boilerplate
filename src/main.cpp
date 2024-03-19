#include <iostream>
// #include <mpi.h>
#include "foo.h"
#include "bar.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// https://eigen.tuxfamily.org/dox/GettingStarted.html
#include <Eigen/Dense>
using Eigen::MatrixXd;

void readCSV(const std::string& filename) {
    // Open the CSV file
    std::ifstream file(filename);

    // Check if the file is open
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Read and process each line in the CSV file
    std::string line;
    while (std::getline(file, line)) {
        // Use a stringstream to split the line into fields
        std::istringstream iss(line);
        std::string field;
        std::vector<std::string> fields;

        while (std::getline(iss, field, ',')) {
            fields.push_back(field);
        }

        // Process each field as needed
        for (const auto& value : fields) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    // Close the file
    file.close();
}

// some C++11
void docpp11() {
    std::vector<std::string> testStrings {"this", "is", "just", "a", "test"};

    for(auto testString : testStrings) {
        std::cout << testString << std::endl;
    }
    
}

int main(int argc, char* argv[]) {
    
    std::cout << "Starting program." << std::endl;
    
    // Check if a filename argument is provided
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <csv_file_path>" << std::endl;
        return 1;
    }
    docpp11();
    foo();
    bar();
    std::cout << "Hello, World!" << std::endl;

    // Pass the CSV file path as an argument to the function
    readCSV(argv[1]);

    MatrixXd m(2, 2);
    m(0, 0) = 3;
    m(1, 0) = 2.5;
    m(0, 1) = -1;
    m(1, 1) = m(1, 0) + m(0, 1);
    std::cout << m << std::endl;
    return 0;
}

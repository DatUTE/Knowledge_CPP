#include <stdio.h>
#include <iostream>

void write_data(uint8_t data, const std::string& file_path)
{
    // Open the file in write mode
    FILE *file = fopen(file_path.c_str(), "w+");
    // Check if the file was opened successfully
    if (file == NULL) {
        std::cout << "can not open file " << file_path << std::endl;
        return;
    }
    fwrite(&data, sizeof(uint8_t), 1, file);
    // fprintf(file, "%d", data);
    std::cout << "write data: " << data << " into file " << file_path << std::endl;

    // Close the file
    fclose(file);
}

uint16_t read_data(const std::string& file_path) {
    FILE *file = fopen(file_path.c_str(), "rb");
    if (file == NULL) {
        std::cout << "Cannot open file " << file_path << std::endl;
        return 0;
    }

    uint8_t buffer[1];
    fread(buffer, sizeof(uint8_t), 1, file);
    std::cout << "Data read from file: " << (uint16_t)buffer[0] << std::endl;

    fclose(file);
    return static_cast<uint16_t>(buffer[0]);
}

int main() {
    uint8_t data = 42;  // Data to write
    std::string file_path = "output.txt";  // File path

    // Call the function to write data to the file
    write_data(data, file_path);
    std::cout << "write ok\n";

    uint16_t res = read_data("output.txt");

    std::cout << "res: " << res << std::endl;
    return 0;
}

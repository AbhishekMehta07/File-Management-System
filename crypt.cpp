#include <iostream>
#include <unordered_map>
#include <string>

// Class to represent a file in the virtual file system
class File {
public:
    std::string name;
    std::string content;

    File(const std::string& fileName) : name(fileName), content("") {}
};

// Virtual File System class to manage file operations
class VirtualFileSystem {
private:
    std::unordered_map<std::string, File*> files;  // Map to store files

public:
    // Create a new file
    bool createFile(const std::string& fileName) {
        if (files.find(fileName) != files.end()) {
            std::cout << "Error: File \"" << fileName << "\" already exists.\n";
            return false;
        }
        files[fileName] = new File(fileName);
        std::cout << "File \"" << fileName << "\" created successfully.\n";
        return true;
    }

    // Write data to a file
    bool writeFile(const std::string& fileName, const std::string& content) {
        if (files.find(fileName) == files.end()) {
            std::cout << "Error: File \"" << fileName << "\" does not exist.\n";
            return false;
        }
        files[fileName]->content = content;
        std::cout << "Data written to file \"" << fileName << "\" successfully.\n";
        return true;
    }

    // Read data from a file
    bool readFile(const std::string& fileName) {
        if (files.find(fileName) == files.end()) {
            std::cout << "Error: File \"" << fileName << "\" does not exist.\n";
            return false;
        }
        std::cout << "Reading from file \"" << fileName << "\":\n";
        std::cout << files[fileName]->content << "\n";
        return true;
    }

    // Delete a file
    bool deleteFile(const std::string& fileName) {
        if (files.find(fileName) == files.end()) {
            std::cout << "Error: File \"" << fileName << "\" does not exist.\n";
            return false;
        }
        delete files[fileName];
        files.erase(fileName);
        std::cout << "File \"" << fileName << "\" deleted successfully.\n";
        return true;
    }

    // List all files
    void listFiles() {
        if (files.empty()) {
            std::cout << "No files available in the system.\n";
        } else {
            std::cout << "Listing files:\n";
            for (const auto& pair : files) {
                std::cout << "- " << pair.first << "\n";
            }
        }
    }

    // Destructor to clean up file objects
    ~VirtualFileSystem() {
        for (auto& pair : files) {
            delete pair.second;
        }
    }
};

// Main function with a simple menu for the Virtual File System
int main() {
    VirtualFileSystem vfs;
    int choice;
    std::string fileName, content;

    while (true) {
        std::cout << "\nVirtual File System Menu:\n";
        std::cout << "1. Create File\n";
        std::cout << "2. Write to File\n";
        std::cout << "3. Read from File\n";
        std::cout << "4. Delete File\n";
        std::cout << "5. List Files\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter file name: ";
                std::cin >> fileName;
                vfs.createFile(fileName);
                break;
            case 2:
                std::cout << "Enter file name: ";
                std::cin >> fileName;
                std::cin.ignore();  // Ignore the newline left in the buffer
                std::cout << "Enter content: ";
                std::getline(std::cin, content);
                vfs.writeFile(fileName, content);
                break;
            case 3:
                std::cout << "Enter file name: ";
                std::cin >> fileName;
                vfs.readFile(fileName);
                break;
            case 4:
                std::cout << "Enter file name: ";
                std::cin >> fileName;
                vfs.deleteFile(fileName);
                break;
            case 5:
                vfs.listFiles();
                break;
            case 6:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

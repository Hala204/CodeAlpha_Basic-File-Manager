#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
using namespace std;
namespace fs = filesystem;

void listDirectory(const string& path)
{
    for (const auto& entry : fs::directory_iterator(path))
    {
        cout << entry.path().filename() << endl;
    }
}

void viewFile(const string& filePath)
{
    ifstream file(filePath);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            cout << line << "\n";
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file: " << filePath << endl;
    }
}

void createDirectory(const string& path, const string& dirName)
{
    fs::create_directory(path + "/" + dirName);
    cout << "Directory has been created " << endl;
}

void createFile(const string& fileName)
{
    ofstream file(fileName);
    if (file.is_open())
    {
        cout << "File has been created." << endl;
        file.close();
    }
    else
    {
        cerr << "Error creating file: " << fileName << endl;
    }
}

void copyFile(const string& sourcePath, const string& destPath)
{
    fs::copy(sourcePath, destPath, fs::copy_options::overwrite_existing);
    cout << "File copied from " << sourcePath << " to " << destPath << endl;
}

void moveFile(const string& sourcePath, const string& destPath)
{
    fs::rename(sourcePath, destPath);
    cout << "File moved from " << sourcePath << " to " << destPath << endl;
}

int main()
{
    string currentPath = ".";

    while (true)
    {
        cout << "Current Directory: " << currentPath << "\n";
        cout << "Commands:\n [ls] to list\n [view FILE] to view file\n [mkdir DIR] to make a new directory\n [cp SOURCE DEST] to copy\n [mv SOURCE DEST] to move\n [cd DIR] to change directory\n [mkfile FILE] to make a new file\n [exit] to exit\n";

        string input;
        getline(cin, input);

        istringstream iss(input);
        string command; 
        iss >> command;

        if (command == "ls") 
        {
            listDirectory(currentPath);
        }
        else if (command == "view") 
        {
            string fileName;
            iss >> fileName;
            viewFile(currentPath + "/" + fileName);
        }
        else if (command == "mkdir") 
        {
            string dirName;
            iss >> dirName;
            createDirectory(currentPath, dirName);
        }
        else if (command == "cp") 
        {
            string source, dest;
            iss >> source >> dest;
            copyFile(currentPath + "/" + source, currentPath + "/" + dest);
        }
        else if (command == "mv") 
        {
            string source, dest;
            iss >> source >> dest;
            moveFile(currentPath + "/" + source, currentPath + "/" + dest);
        }
        else if (command == "cd") 
        {
            string dirName;
            iss >> dirName;
            currentPath = currentPath + "/" + dirName;
        }
        else if (command == "mkfile") 
        {
            string fileName;
            iss >> fileName;
            createFile(fileName);
        }
        else if (command == "exit") 
        {
            break;
        }
        else
        {
            cout << "Invalid command. Try again." << endl;
        }
    }

    return 0;
}

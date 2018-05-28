/*
Copyright 2015-2017 Hermann Krumrey <hermann@krumreyh.com>

This file is part of xdcc-downloader.

xdcc-downloader is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

xdcc-downloader is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with xdcc-downloader.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * @author Hermann Krumrey <hermann@krumreyh.com>
 * Collection of methods to help with processing files
 */

#include <string.h>
#include <iostream>
#include "fileHandlers.h"


//Implementations

/*
 * Checks if a file exists
 * @param file - the path of the file to be checked
 */
bool isFile(string file) {

    ifstream ifile(file.c_str());
    if (ifile) {
        ifile.close();
        return true;
    }
    else {
        ifile.close();
        return false;
    }
}

/*
 * Reads a file and returns it as a vector of strings, which may be handled similarly to an array
 * @param file - the path of the file to be read
 * @throws 404 if the file is not found
 */
vector<string> readFile(string file) {

    vector<string> fileContent;

    if (!isFile(file)) {
        throw 404;
    }
    ifstream input(file);
    string line;

    while (getline(input, line)) {
        fileContent.push_back(line);
    }

    return fileContent;
}

/*
 * Reads a file and returns it as a vector of strings, which may be handled similarly to an array
 * Lines starting with # symbols are ommited
 * @param file - the path of the file to be read
 * @throws 404 if the file is not found
 */
vector<string> readFileNoHash(string file) {

    vector<string> fileContent;

    if (!isFile(file)) {
        throw 404;
    }

    ifstream input(file);
    string line;

    while (getline(input, line)) {
        if (!strncmp(line.c_str(), "#", 1)) { continue; }
        fileContent.push_back(line);
    }

    return fileContent;
}


/**
 * Creates a new, empty file.
 * @param file - the path to the file to be created
 * @throws 503 if the file already exists
 */
void createFile(string file) {
    if (isFile(file)) { throw 503; }
    ofstream output(file);
    output.close();
}

/**
 * Deletes a file
 * @param file - the file to be deleted
 */
void deleteFile(string file) {
    remove(file.c_str());
}

/**
 * Writes a vector of Strings to a newline seperated textfile
 * @param file - the path of the file to be written to
 * @param content - the content to be written to the file
 * @throws 503 if the file already exists
 */
void writeToFile(string file, vector<string> content) {
    deleteFile(file);
    createFile(file);
    ofstream output(file);
    for (int i = 0; i < content.size(); i++) {
        string line = content[i] + "\n";
        output.write(line.c_str(), content[i].size() + 1);
    }
    output.close();
}

/**
 * Appends a line to a text file
 * @param line - the line to be appended
 * @param file - the path to the file to which the line shall be appended to
 */
void appendLine(string line, string file) {

    if (!isFile(file)) {
        throw 404;
    }
    ofstream output(file, ios::app);
    output << line + "\n";
    output.close();

}
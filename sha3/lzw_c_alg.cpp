#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Compresses a string using LZW compression
vector<int> compress(const string& input) {
    unordered_map<string, int> dictionary;
    for (int i = 0; i < 256; i++) {
        dictionary[string(1, i)] = i;
    }

    string current;
    vector<int> output;
    for (char c : input) {
        string next = current + c;
        if (dictionary.count(next)) {
            current = next;
        }
        else {
            output.push_back(dictionary[current]);
            dictionary[next] = dictionary.size();
            current = string(1, c);
        }
    }

    if (!current.empty()) {
        output.push_back(dictionary[current]);
    }

    return output;
}

// Decompresses a vector of integers using LZW decompression
string decompress(const vector<int>& input) {
    unordered_map<int, string> dictionary;
    for (int i = 0; i < 256; i++) {
        dictionary[i] = string(1, i);
    }

    string current = dictionary[input[0]];
    string output = current;
    for (int i = 1; i < input.size(); i++) {
        int code = input[i];
        if (dictionary.count(code)) {
            current = dictionary[code];
        }
        else if (code == dictionary.size()) {
            current = current + current[0];
        }
        else {
            throw "Bad compressed code";
        }

        output += current;
        dictionary[dictionary.size()] = current.substr(0, current.size() - 1) + current[0];
    }

    return output;
}

int main() {
    // Reading input file into string
    ifstream input_file("input.txt");
    string input_string((istreambuf_iterator<char>(input_file)), istreambuf_iterator<char>());

    // Compressing and writing to output file
    vector<int> compressed_data = compress(input_string);
    ofstream output_file("output.bin", ios::out | ios::binary);
    for (int code : compressed_data) {
        output_file.write((char*)&code, sizeof(code));
    }
    output_file.close();

    // Reading from output file and decompressing
    vector<int> compressed_input;
    ifstream compressed_file("output.bin", ios::binary);
    while (true) {
        int code;
        compressed_file.read((char*)&code, sizeof(code));
        if (compressed_file.eof()) {
            break;
        }
        compressed_input.push_back(code);
    }
    compressed_file.close();

    string decompressed_data = decompress(compressed_input);

    // Writing decompressed data to output file
    ofstream decompressed_file("decompressed.txt", ios::out);
    decompressed_file << decompressed_data;
    decompressed_file.close();

    return 0;
}


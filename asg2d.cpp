#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

#include <huffman.h> // Header file containing generateHuffmanCodes function

using namespace std;
using namespace std::chrono;

int main() {
    // Read input from file
    ifstream infile("large_document.txt");
    string input((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());

    // Generate Huffman codes
    auto start = high_resolution_clock::now();
    vector<HuffmanCode> codes = generateHuffmanCodes(input);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    // Print the codes and their frequencies
    for (const auto& code : codes) {
        cout << "Symbol: " << code.symbol << " Frequency: " << code.frequency << " Code: " << code.code << endl;
    } 
    cout << "Time taken: " << duration.count() << " ms" << endl;

    return 0;
}
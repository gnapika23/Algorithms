#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "huffman.h" // Header file containing generateHuffmanCodes function

using namespace std;

// Function to calculate compression ratio given input size and compressed size
double calculateCompressionRatio(size_t inputSize, size_t compressedSize) {
    return static_cast<double>(compressedSize) / static_cast<double>(inputSize);
}

int main() {
    // Read input from files
    ifstream infile1("document1.txt");
    string input1((istreambuf_iterator<char>(infile1)), istreambuf_iterator<char>());
    ifstream infile2("document2.txt");
    string input2((istreambuf_iterator<char>(infile2)), istreambuf_iterator<char>());

    // Generate Huffman codes for both documents
    vector<HuffmanCode> codes1 = generateHuffmanCodes(input1);
    vector<HuffmanCode> codes2 = generateHuffmanCodes(input2);

    // Calculate sizes of compressed data for both documents
    size_t compressedSize1 = 0;
    for (const auto& code : codes1) {
        compressedSize1 += code.frequency * code.code.size();
    }
    compressedSize1 = ceil(static_cast<double>(compressedSize1) / 8);
    size_t compressedSize2 = 0;
    for (const auto& code : codes2) {
        compressedSize2 += code.frequency * code.code.size();
    }
    compressedSize2 = ceil(static_cast<double>(compressedSize2) / 8);

    // Calculate compression ratios for both documents
    double compressionRatio1 = calculateCompressionRatio(input1.size(), compressedSize1);
    double compressionRatio2 = calculateCompressionRatio(input2.size(), compressedSize2);

    // Print the compression ratios
    cout << "Compression ratio for document1.txt: " << compressionRatio1 << endl;
    cout << "Compression ratio for document2.txt: " << compressionRatio2 << endl;
    return 0;
}


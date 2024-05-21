#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// Structure to store symbol frequency and code
struct HuffmanCode {
    char symbol;
    int frequency;
    string code;
};

// Comparison function for min-heap
struct Compare {
    bool operator()(const pair<int, char>& a, const pair<int, char>& b) const {
        return a.first > b.first;
    }
};

// Function to generate Huffman codes
vector<HuffmanCode> generateHuffmanCodes(const string& input) {
    unordered_map<char, int> freqMap;

    // Calculate symbol frequencies
    for (char c : input) {
        ++freqMap[c];
    }

    // Create a min-heap of symbol frequencies
    priority_queue<pair<int, char>, vector<pair<int, char>>, Compare> minHeap;
    for (const auto& entry : freqMap) {
        minHeap.push({entry.second, entry.first});
    }

    // Build the Huffman tree
    while (minHeap.size() > 1) {
        auto left = minHeap.top();
        minHeap.pop();
        auto right = minHeap.top();
        minHeap.pop();
		minHeap.push({left.first + right.first,left.second});
		minHeap.push({left.first + right.first, right.second});
		}
	// Traverse the Huffman tree to generate codes
	unordered_map<char, string> codeMap;
	string currentCode;
	auto root = minHeap.top().second;
	function<void(char, string)> traverseTree = [&](char symbol, string code) {
		if (symbol != root) {
			codeMap[symbol] = code;
		}
		if (symbol == root) {
			currentCode = "";
		} else {
			currentCode.pop_back();
		}
	};
	function<void(char, string)> traverseNode = [&](char symbol, string code) {
		currentCode += code;
		traverseTree(symbol, currentCode);
		currentCode.pop_back();
	};
	function<void(char, string)> traverseLeft = [&](char symbol, string code) {
		currentCode += code;
		traverseNode(symbol, "0");
		currentCode.pop_back();
	};
	function<void(char, string)> traverseRight = [&](char symbol, string code) {
		currentCode += code;
		traverseNode(symbol, "1");
		currentCode.pop_back();
	};
	traverseTree(root, "");
	for (const auto& entry : freqMap) {
		char symbol = entry.first;
		string code = codeMap[symbol];
		codeMap[symbol] = string(code.rbegin(), code.rend());
	}

	// Convert code map to vector of Huffman codes
	vector<HuffmanCode> codes;
	for (const auto& entry : codeMap) {
		codes.push_back({entry.first, freqMap[entry.first], entry.second});
	}

	return codes;
}
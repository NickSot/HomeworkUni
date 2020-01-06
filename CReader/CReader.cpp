#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>

using namespace std;

class CFileIO {
private:
	ifstream reader;
	ofstream writer;

	string readCFile() {
		string line;
		string returnValue = "";

		if (reader.is_open()) {
			while (getline(reader, line)) {
				returnValue += line + "\n";
			}
		}
		else {
			cout << "unable to open file..." << endl;
			return "";
		}

		return returnValue;
	}

public:
	CFileIO() {
	
	}

	CFileIO(string filePath) {
		reader = ifstream(filePath);
	}

	void setStream(string fileName) {
		reader = ifstream(fileName);
	}

	void writeToFile(string filePath, string content) {
		writer = ofstream();

		writer.open(filePath);

		writer << content << endl;

		writer.close();
	}

	int getBlockCount() {
		string fileContents = readCFile();

		stack<int> blockChecker = stack<int>();

		istringstream stringStream(fileContents);
		int blockCounter = 0;
		string line;

		while (getline(stringStream, line)) {
			if (line.find("{") != string::npos) {
				blockCounter++;
				blockChecker.push(1);
			}
			else if (line.find("}") != string::npos) {
				if (blockChecker.empty()) {
					return -1;
				}
				
				blockChecker.pop();
			}
		}

		if (!blockChecker.empty()) {
			return -1;
		}

		return blockCounter;
	}

	int getLoopCount() {
		if (getBlockCount() == -1)
			return -1;

		string fileContents = readCFile();
		istringstream stringStream(fileContents);
		int loopCounter = 0;
		string line;

		while (getline(stringStream, line)) {
			if (line.find("while") != string::npos || line.find("for") != string::npos || line.find("do") != string::npos) {
				loopCounter++;
			}
		}

		return loopCounter;
	}
};

void option1(CFileIO& CFileOperation) {
	string filePath, exportFilePath;

	cout << "File to read: ";

	cin >> filePath;

	cout << "File to write to: ";

	cin >> exportFilePath;

	CFileOperation = CFileIO(filePath);
	
	int blocks = CFileOperation.getBlockCount();
	int loops = CFileOperation.getLoopCount();

	if (blocks == -1) {
		cout << "Error: Cannot parse the code..." << endl;
	}
	else {
		string content = "Block count: " + to_string(blocks) + "\n" + "Loop count: " + to_string(loops);

		CFileOperation.writeToFile(exportFilePath, content);
	}
}

void option2(CFileIO& CFileReader) {
	string filePath;

	cout << "File to read: " << endl;

	cin >> filePath;

	CFileReader = CFileIO(filePath);

	int blocks = CFileReader.getBlockCount();
	int loops = CFileReader.getLoopCount();

	if (blocks == -1) {
		cout << "Error: Cannot parse the code..." << endl;
	}
	else {
		cout << "Blocks: " << blocks << endl;
		cout << "Loops: " << loops << endl;
	}
}

void option3(CFileIO& CFileOperation) {
	string exportFilePath, code;

	cout << "Write the code: " << endl;

	while (!cin.eof()) {
		string temp;
		cin >> temp;
		code += temp;
	}

	CFileOperation = CFileIO();

	CFileOperation.writeToFile("temp.txt", code);
	CFileOperation.setStream("temp.txt");

	int blocks = CFileOperation.getBlockCount();
	int loops = CFileOperation.getLoopCount();

	if (blocks == -1) {
		cout << "Error: Cannot parse the code..." << endl;
	}
	else {
		string content = "Block count: " + to_string(blocks) + "\n" + "Loop count: " + to_string(loops);

		CFileOperation.writeToFile(exportFilePath, content);
	}
}

void option4(CFileIO& CFileOperation) {
	string code;

	cout << "Write the code: " << endl;

	while (!cin.eof()) {
		string temp;
		cin >> temp;
		code += temp;
	}

	CFileOperation = CFileIO();

	CFileOperation.writeToFile("temp.txt", code);
	CFileOperation.setStream("temp.txt");

	int blocks = CFileOperation.getBlockCount();
	int loops = CFileOperation.getLoopCount();

	if (blocks == -1) {
		cout << "Error: Cannot parse the code..." << endl;
	}
	else {
		cout << "Blocks: " << blocks << endl;
		cout << "Loops: " << loops << endl;
	}
}

int main()
{
	CFileIO CFileReader;

	while (true) {
		cout << "Options: " << endl;

		cout << "1) read file and write result to file " << endl;
		cout << "2) read file and print on stdout " << endl;
		cout << "3) read stdin and write result to a file" << endl;
		cout << "4) read stdin and print result on stdout " << endl;

		int option;

		cin >> option;

		switch (option) {
			case 1:
				option1(CFileReader);
				break;
			case 2:
				option2(CFileReader);
				break;
			case 3:
				option3(CFileReader);
				break;
			case 4:
				option4(CFileReader);
				break;
		}

		
	}
}
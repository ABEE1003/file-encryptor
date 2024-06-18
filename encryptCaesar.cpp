#include <iostream>
#include <fstream>
#include <string>
using namespace std;
string encryptCaesar(string plaintext, int shift) {
    string ciphertext = "";

    // Iterate through each character in the plaintext
    for (char& c : plaintext) {
        // Encrypt only alphabetic characters
        if (isalpha(c)) {
            // Determine the new character after shifting
            char shifted = c + shift;

            // Handle wrap-around for uppercase letters
            if (isupper(c) && shifted > 'Z')
                shifted = 'A' + (shifted - 'Z' - 1);
            // Handle wrap-around for lowercase letters
            else if (islower(c) && shifted > 'z')
                shifted = 'a' + (shifted - 'z' - 1);

            // Append the encrypted character to the ciphertext
            ciphertext += shifted;
        } else {
            // Append non-alphabetic characters unchanged
            ciphertext += c;
        }
    }

    return ciphertext;
}
void encryptFile(string inputFile, string outputFile, int shift) {
    ifstream input(inputFile);    // Input file stream
    ofstream output(outputFile);  // Output file stream

    if (!input) {
        cerr << "Error: Could not open input file!" << endl;
        return;
    }

    if (!output) {
        cerr << "Error: Could not create/open output file!" << endl;
        return;
    }

    string line;
    while (getline(input, line)) {
        // Encrypt each line read from input file
        string encrypted = encryptCaesar(line, shift);

        // Write encrypted line to output file
        output << encrypted << endl;
    }

    // Close files
    input.close();
    output.close();

    cout << "File encrypted successfully." << endl;
}
int main() {
    string inputFile, outputFile;
    int shift;

    // Get input from the user
    cout << "Enter input file name: ";
    getline(cin, inputFile);

    cout << "Enter output file name: ";
    getline(cin, outputFile);

    cout << "Enter shift value (positive integer): ";
    cin >> shift;
    cin.ignore(); // Ignore newline character left by cin

    // Encrypt the file
    encryptFile(inputFile, outputFile, shift);

    return 0;
}
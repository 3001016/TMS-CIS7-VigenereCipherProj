#include <iostream>
#include <regex>

using namespace std;

//////////////////Functions related to Encrypt/Decrypt Start //////
// This function is to generate the key to match the length of the plain text.
// This key will be based on user provided key.
string GenerateKey(string plainText, string key) {
  if (key.size() >= plainText.size())
    return key;
  for (int i = 0;; i++) {
    if (key.size() == plainText.size())
      break;
    key.push_back(key[i]);
  }
  return key;
}

// This function will perform encrypt functionality.
string Encrypt(string plainText, string key) {
  string cipherText;

  for (int i = 0; i < plainText.size(); i++) {
    char encrypt_char;
    if (plainText[i] == ' ') {
      encrypt_char = ' ';
    } else {
      encrypt_char = char(int(plainText[i] + key[i]) % 26 + 65);
    }
    cipherText.push_back(encrypt_char);
  }
  return cipherText;
}

// This function will perform Decrypt functionality.
string Decrypt(string cipherText, string key) {
  string plainText;

  for (int i = 0; i < cipherText.size(); i++) {
    char decrypt_char;

    if (cipherText[i] == ' ') {
      decrypt_char = ' ';
    } else {
      decrypt_char = char(int(cipherText[i] - key[i] + 26) % 26 + 65);
    }
    plainText.push_back(decrypt_char);
  }
  return plainText;
}
////////////////// Functions related to Encrypt/Decrypt END ///////

////////////////// Functions related to User input START ///////

// This function to convert all characters to upper case.
string ConvertToUpper(string inputVal) {
  transform(inputVal.begin(), inputVal.end(), inputVal.begin(), ::toupper);
  return inputVal;
}

// This function to get user input to get the value to Encrypt/Decrypt.
string GetPlainText() {
  string plaintext = "";
  for (;;) {
    cout << "Please enter the string to encrypt (Alphabets only): ";
    getline(cin, plaintext);

    bool contains_alpha =
        std::regex_match(plaintext, regex("^[a-zA-Z\\s]+(\\s[a-zA-Z]+)?$"));

    if (contains_alpha) // converToUpper(plaintext)
    {
      plaintext = ConvertToUpper(plaintext);
      break;
    } else
      cout << "Invalid input. Alphabets allowed only." << endl;
  }
  return plaintext;
}

// This function to get Key word.
string GetKeyword() {
  string keyword = "";
  for (;;) {
    cout << "Please enter the Key (Alphabets only): ";
    // getline(cin, keyword);
    cin >> keyword;

    bool contains_alpha =
        std::regex_match(keyword, regex("^[a-zA-Z]+([a-zA-Z]+)?$"));

    if (contains_alpha) {
      keyword = ConvertToUpper(keyword);
      break;
    } else
      cout << "Invalid input. Alphabets allowed only." << endl;
  }
  return keyword;
}

void clearCin() {
  string temp;
  getline(cin, temp);
}
////////////////// Functions related to User input END ///////
///////////////////////////////////////////////
// Main Function //
int main() {
  for (;;) {
    string plaintext = GetPlainText();
    string keyword = GetKeyword();
    string continue_or_not;

    string key = GenerateKey(plaintext, keyword);
    // cout << "KEY : " << key << "\n";
    string cipherText = Encrypt(plaintext, key);

    cout << "Encrypted text : " << cipherText << "\n";

    cout << "Decrypted Text : " << Decrypt(cipherText, key);
    cout << "\n\n";

    cout << "Do you want to continue ? (Y or any key to terminate) : ";
    cin >> continue_or_not;

    if (continue_or_not == "Y" || continue_or_not == "y")
      clearCin();
    else
      break;
  }
  return 0;
}
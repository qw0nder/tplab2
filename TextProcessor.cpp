#include "TextProcessor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>

void TextProcessor::findSentencesWithWord(const std::string& filename, const std::string& word) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    // Читаем весь файл
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string text = buffer.str();
    file.close();

    if (text.empty()) {
        std::cout << "File is empty!" << std::endl;
        return;
    }

    if (word.empty()) {
        std::cout << "Search word cannot be empty!" << std::endl;
        return;
    }

    std::cout << "\n=== SENTENCES CONTAINING WORD: \"" << word << "\" ===" << std::endl;

    // Разделяем текст на предложения
    std::vector<std::string> sentences;
    std::string currentSentence;
    bool sentenceFound = false;

    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];
        currentSentence += c;

        // Конец предложения: . ! ? или конец файла
        if (c == '.' || c == '!' || c == '?' || i == text.length() - 1) {
            // Ищем слово в предложении (регистронезависимо)
            std::string sentenceLower = currentSentence;
            std::string wordLower = word;

            // Приводим к нижнему регистру
            for (char& ch : sentenceLower) ch = std::tolower(ch);
            for (char& ch : wordLower) ch = std::tolower(ch);

            // Ищем слово целиком (не как подстроку)
            std::istringstream iss(sentenceLower);
            std::string currentWord;
            bool found = false;

            while (iss >> currentWord) {
                // Убираем знаки препинания
                std::string cleanedWord;
                for (char ch : currentWord) {
                    if (std::isalpha(ch) || std::isdigit(ch)) {
                        cleanedWord += ch;
                    }
                }

                if (cleanedWord == wordLower) {
                    found = true;
                    break;
                }
            }

            if (found) {
                // Убираем лишние пробелы
                size_t start = currentSentence.find_first_not_of(" \t\n");
                size_t end = currentSentence.find_last_not_of(" \t\n");
                if (start != std::string::npos && end != std::string::npos) {
                    std::string trimmedSentence = currentSentence.substr(start, end - start + 1);
                    std::cout << trimmedSentence << std::endl;
                    sentenceFound = true;
                }
            }

            currentSentence.clear();
        }
    }

    if (!sentenceFound) {
        std::cout << "No sentences found containing the word \"" << word << "\"" << std::endl;
    }
}
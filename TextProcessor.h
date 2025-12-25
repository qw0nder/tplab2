#pragma once
#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H

#include <string>

class TextProcessor {
public:
    static void findSentencesWithWord(const std::string& filename, const std::string& word);
};

#endif
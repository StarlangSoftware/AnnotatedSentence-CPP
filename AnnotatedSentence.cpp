//
// Created by Olcay Taner Yıldız on 2019-04-26.
//

#include "AnnotatedSentence.h"
#include "AnnotatedWord.h"
#include <istream>

/**
 * Reads an annotated sentence from a text file.
 * @param inputFile File containing the annotated sentence.
 */
AnnotatedSentence::AnnotatedSentence(istream &inputFile) {
    string word;
    while (inputFile.good()){
        inputFile >> word;
        words.emplace_back(new AnnotatedWord(word));
    }
}

/**
 * Converts a simple sentence to an annotated sentence
 * @param sentence Simple sentence
 */
AnnotatedSentence::AnnotatedSentence(string sentence) {
    vector<string> wordArray = Word::split(move(sentence));
    for (auto const& word : wordArray){
        if (!word.empty()){
            words.emplace_back(new AnnotatedWord(word));
        }
    }
}

bool AnnotatedSentence::containsPredicate() {
    for (Word* word : words){
        auto* annotatedWord = (AnnotatedWord*) word;
        if (annotatedWord->getArgument() != nullptr && annotatedWord->getArgument()->getArgumentType() == "PREDICATE"){
            return true;
        }
    }
    return false;
}

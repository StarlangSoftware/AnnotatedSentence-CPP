//
// Created by olcay on 2.05.2019.
//

#include "AnnotatedCorpus.h"
#include "AnnotatedSentence.h"
using std::filesystem::directory_iterator;

/**
 * A constructor of {@link AnnotatedCorpus} class which reads all {@link AnnotatedSentence} files with the file
 * name satisfying the given pattern inside the given folder. For each file inside that folder, the constructor
 * creates an AnnotatedSentence and puts in inside the list parseTrees.
 * @param folder Folder where all sentences reside.
 * @param fileList File list containing all sentences.
 */
AnnotatedCorpus::AnnotatedCorpus(const string& folder) {
    ifstream sentenceFile;
    string line;
    vector<string> files;
    for (const auto & file : directory_iterator(folder)) {
        if (!file.is_directory()) {
            files.emplace_back(file.path());
        }
    }
    sort(files.begin(), files.end());
    for (const string& file : files) {
        sentenceFile.open(file, ifstream::in);
        addSentence(new AnnotatedSentence(sentenceFile));
        sentenceFile.close();
    }
}

/**
 * An obsolete constructor of the {@link AnnotatedSentence} class. If the contents of all the sentences are inside
 * a single file, this constructor can be called. Each line in this file corresponds to a single AnnotatedSentence.
 * @param inputFile File containing the sentences.
 */
AnnotatedCorpus::AnnotatedCorpus(istream &inputFile) {
    string line;
    getline(inputFile, line);
    while (!line.empty()){
        addSentence(new AnnotatedSentence(line));
        getline(inputFile, line);
    }
}

/**
  * Creates a dictionary from the morphologically annotated words.
  * @return A dictionary containing root forms of the morphological annotations of words.
  */
TxtDictionary AnnotatedCorpus::createDictionary() const{
    TxtDictionary dictionary = TxtDictionary();
    for (int i = 0; i < sentenceCount(); i++){
        auto* sentence = (AnnotatedSentence*) getSentence(i);
        for (int j = 0; j < sentence->wordCount(); j++){
            auto* word = (AnnotatedWord*) sentence->getWord(j);
            if (word->getParse() != nullptr){
                MorphologicalParse* morphologicalParse = word->getParse();
                string pos = morphologicalParse->getRootPos();
                string name = morphologicalParse->getWord()->getName();
                if (pos == "NOUN"){
                    if (morphologicalParse->isProperNoun()){
                        dictionary.addProperNoun(name);
                    } else {
                        dictionary.addNoun(name);
                    }
                } else {
                    if (pos == "VERB"){
                        dictionary.addVerb(name);
                    } else {
                        if (pos == "ADJ"){
                            dictionary.addAdjective(name);
                        } else {
                            if (pos == "ADV"){
                                dictionary.addAdverb(name);
                            }
                        }
                    }
                }
            }
        }
    }
    return dictionary;
}

ParserEvaluationScore AnnotatedCorpus::compareParses(const AnnotatedCorpus& corpus) {
    ParserEvaluationScore result = ParserEvaluationScore();
    for (int i = 0; i < sentences.size(); i++){
        auto* sentence1 = (AnnotatedSentence*) sentences.at(i);
        auto* sentence2 = (AnnotatedSentence*) corpus.getSentence(i);
        result.add(sentence1->compareParses(sentence2));
    }
    return result;
}
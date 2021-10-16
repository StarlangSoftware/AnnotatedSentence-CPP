//
// Created by olcay on 2.05.2019.
//

#include "AnnotatedCorpus.h"
#include "AnnotatedSentence.h"

/**
 * A constructor of {@link AnnotatedCorpus} class which reads all {@link AnnotatedSentence} files with the file
 * name satisfying the given pattern inside the given folder. For each file inside that folder, the constructor
 * creates an AnnotatedSentence and puts in inside the list parseTrees.
 * @param folder Folder where all sentences reside.
 * @param fileList File list containing all sentences.
 */
AnnotatedCorpus::AnnotatedCorpus(string folder, string fileList) {
    ifstream corpusFile, sentenceFile;
    string line;
    corpusFile.open(fileList, ifstream::in);
    while (corpusFile.good()){
        corpusFile >> line;
        string fileName = folder;
        fileName += "/" + line;
        sentenceFile.open(fileName, ifstream::in);
        addSentence(new AnnotatedSentence(sentenceFile));
        sentenceFile.close();
    }
    corpusFile.close();
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
TxtDictionary AnnotatedCorpus::createDictionary() {
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

RootWordStatistics AnnotatedCorpus::extractRootWordStatistics(FsmMorphologicalAnalyzer fsm) {
    RootWordStatistics statistics = RootWordStatistics();
    CounterHashMap<string> rootWordStatistics;
    for (int i = 0; i < sentenceCount(); i++){
        auto* sentence = (AnnotatedSentence*) getSentence(i);
        for (int j = 0; j < sentence->wordCount(); j++){
            auto* word = (AnnotatedWord*) sentence->getWord(j);
            if (!word->getName().empty()){
                FsmParseList parseList = fsm.morphologicalAnalysis(word->getName());
                MorphologicalParse* parse = word->getParse();
                if (parseList.size() > 0 && parse != nullptr){
                    string rootWords = parseList.rootWords();
                    if (rootWords.find('$') != string::npos){
                        if (!statistics.containsKey(rootWords)){
                            rootWordStatistics = CounterHashMap<string>();
                        } else {
                            rootWordStatistics = statistics.get(rootWords);
                        }
                        rootWordStatistics.put(parse->getWord()->getName());
                        statistics.put(rootWords, rootWordStatistics);
                    }
                }
            }
        }
    }
    return statistics;
}

ParserEvaluationScore AnnotatedCorpus::compareParses(AnnotatedCorpus corpus) {
    ParserEvaluationScore result = ParserEvaluationScore();
    for (int i = 0; i < sentences.size(); i++){
        auto* sentence1 = (AnnotatedSentence*) sentences.at(i);
        auto* sentence2 = (AnnotatedSentence*) corpus.getSentence(i);
        result.add(sentence1->compareParses(sentence2));
    }
    return result;
}

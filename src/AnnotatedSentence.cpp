//
// Created by Olcay Taner Yıldız on 2019-04-26.
//

#include "AnnotatedSentence.h"
#include "AnnotatedWord.h"
#include <istream>
#include <FrameNet.h>

/**
 * Reads an annotated sentence from a text file.
 * @param inputFile File containing the annotated sentence.
 */
AnnotatedSentence::AnnotatedSentence(istream &inputFile) {
    string line;
    getline(inputFile, line);
    vector<string> wordArray = Word::split(line);
    for (auto const& word : wordArray){
        if (!word.empty()){
            words.emplace_back(new AnnotatedWord(word));
        }
    }
}

/**
 * Converts a simple sentence to an annotated sentence
 * @param sentence Simple sentence
 */
AnnotatedSentence::AnnotatedSentence(const string& sentence) {
    vector<string> wordArray = Word::split(sentence);
    for (auto const& word : wordArray){
        if (!word.empty()){
            words.emplace_back(new AnnotatedWord(word));
        }
    }
}

/**
 * The method checks all words in the sentence and returns true if at least one of the words is annotated with
 * PREDICATE tag.
 * @return True if at least one of the words is annotated with PREDICATE tag; false otherwise.
 */
bool AnnotatedSentence::containsPredicate() const{
    for (Word* word : words){
        auto* annotatedWord = (AnnotatedWord*) word;
        if (annotatedWord->getArgument() != nullptr && annotatedWord->getArgument()->getArgumentType() == "PREDICATE"){
            return true;
        }
    }
    return false;
}

/**
 * The method checks all words in the sentence and returns true if at least one of the words is annotated with
 * PREDICATE tag.
 * @return True if at least one of the words is annotated with PREDICATE tag; false otherwise.
 */
bool AnnotatedSentence::containsFramePredicate() const{
    for (Word* word : words){
        auto* annotatedWord = (AnnotatedWord*) word;
        if (annotatedWord->getFrameElement() != nullptr && annotatedWord->getFrameElement()->getFrameElementType() == "PREDICATE"){
            return true;
        }
    }
    return false;
}

bool AnnotatedSentence::updateConnectedPredicate(const string& previousId, const string& currentId) {
    bool modified = false;
    for (Word* word : words){
        auto* annotatedWord = (AnnotatedWord*) word;
        if (annotatedWord->getArgument() != nullptr && !annotatedWord->getArgument()->getId().empty() && annotatedWord->getArgument()->getId() == previousId){
            annotatedWord->setArgument(annotatedWord->getArgument()->getArgumentType() + "$" + currentId);
            modified = true;
        }
        if (annotatedWord->getFrameElement() != nullptr && !annotatedWord->getFrameElement()->getId().empty() && annotatedWord->getFrameElement()->getId() == previousId){
            annotatedWord->setFrameElement(annotatedWord->getFrameElement()->getFrameElementType() + "$" + annotatedWord->getFrameElement()->getFrame() + "$" + currentId);
            modified = true;
        }
    }
    return modified;
}

/**
 * The method constructs all possible shallow parse groups of a sentence.
 * @return Shallow parse groups of a sentence.
 */
vector<AnnotatedPhrase *> AnnotatedSentence::getShallowParseGroups() const{
    vector<AnnotatedPhrase *> result;
    AnnotatedWord* previousWord = nullptr;
    AnnotatedPhrase* current = nullptr;
    for (int i = 0; i < this->wordCount(); i++){
        auto* annotatedWord = (AnnotatedWord*) getWord(i);
        if (previousWord == nullptr){
            current = new AnnotatedPhrase(i, annotatedWord->getShallowParse());
        } else {
            if (!previousWord->getShallowParse().empty() && previousWord->getShallowParse() != annotatedWord->getShallowParse()){
                result.emplace_back(current);
                current = new AnnotatedPhrase(i, annotatedWord->getShallowParse());
            }
        }
        current->addWord(annotatedWord);
        previousWord = annotatedWord;
    }
    result.emplace_back(current);
    return result;
}

/**
 * The method returns all possible words, which is
 * 1. Verb
 * 2. Its semantic tag is assigned
 * 3. A frameset exists for that semantic tag
 * @param framesetList Frameset list that contains all frames for Turkish
 * @return An array of words, which are verbs, semantic tags assigned, and framesetlist assigned for that tag.
 */
vector<AnnotatedWord *> AnnotatedSentence::predicateCandidates(FramesetList& framesetList) const{
    vector<AnnotatedWord*> candidateList;
    for (Word* word : words){
        auto* annotatedWord = (AnnotatedWord*) word;
        if (annotatedWord->getParse() != nullptr && annotatedWord->getParse()->isVerb() && !annotatedWord->getSemantic().empty() && framesetList.frameExists(annotatedWord->getSemantic())){
            candidateList.emplace_back(annotatedWord);
        }
    }
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < words.size() - i - 1; j++){
            auto* annotatedWord = (AnnotatedWord*) words.at(j);
            auto* nextAnnotatedWord = (AnnotatedWord*) words.at(j + 1);
            if (find(candidateList.begin(), candidateList.end(), annotatedWord) == candidateList.end() && find(candidateList.begin(), candidateList.end(), nextAnnotatedWord) != candidateList.end() && !annotatedWord->getSemantic().empty() && annotatedWord->getSemantic() == nextAnnotatedWord->getSemantic()){
                candidateList.emplace_back(annotatedWord);
            }
        }
    }
    return candidateList;
}

/**
 * The method returns all possible words, which is
 * 1. Verb
 * 2. Its semantic tag is assigned
 * 3. A frameset exists for that semantic tag
 * @param framesetList Frameset list that contains all frames for Turkish
 * @return An array of words, which are verbs, semantic tags assigned, and framesetlist assigned for that tag.
 */
vector<AnnotatedWord *> AnnotatedSentence::predicateFrameCandidates(FrameNet& frameNet) const{
    vector<AnnotatedWord*> candidateList;
    for (Word* word : words){
        auto* annotatedWord = (AnnotatedWord*) word;
        if (annotatedWord->getParse() != nullptr && annotatedWord->getParse()->isVerb() && !annotatedWord->getSemantic().empty() && frameNet.lexicalUnitExists(annotatedWord->getSemantic())){
            candidateList.emplace_back(annotatedWord);
        }
    }
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < words.size() - i - 1; j++){
            auto* annotatedWord = (AnnotatedWord*) words.at(j);
            auto* nextAnnotatedWord = (AnnotatedWord*) words.at(j + 1);
            if (find(candidateList.begin(), candidateList.end(), annotatedWord) == candidateList.end() && find(candidateList.begin(), candidateList.end(), nextAnnotatedWord) != candidateList.end() && !annotatedWord->getSemantic().empty() && annotatedWord->getSemantic() == nextAnnotatedWord->getSemantic()){
                candidateList.emplace_back(annotatedWord);
            }
        }
    }
    return candidateList;
}

/**
 * Returns the i'th predicate in the sentence.
 * @param index Predicate index
 * @return The predicate with index index in the sentence.
 */
string AnnotatedSentence::getPredicate(int index) const{
    int count1  = 0, count2 = 0;
    string data;
    vector<AnnotatedWord*> word;
    vector<MorphologicalParse*> parse;
    if (index < wordCount()){
        for (int i = 0; i < wordCount(); i++) {
            word.emplace_back((AnnotatedWord*) getWord(i));
            parse.emplace_back(word.at(i)->getParse());
        }
        for (int i = index; i >= 0; i--) {
            if (parse.at(i) != nullptr && !parse.at(i)->getRootPos().empty() && !parse.at(i)->getPos().empty() && parse.at(i)->getRootPos() == "VERB" && parse.at(i)->getPos() == "VERB"){
                count1 = index - i;
                break;
            }
        }
        for (int i = index; i < wordCount() - index; i++) {
            if (parse.at(i) != nullptr && !parse.at(i)->getRootPos().empty() && !parse.at(i)->getPos().empty() && parse.at(i)->getRootPos() == "VERB" && parse.at(i)->getPos() == "VERB"){
                count2 = i - index;
                break;
            }
        }
        if (count1 > count2){
            data = word.at(count1)->getName();
        }
        else{
            data = word.at(count2)->getName();
        }
    }
    return data;
}

/**
 * Removes the i'th word from the sentence
 * @param index Word index
 */
void AnnotatedSentence::removeWord(int index) {
    words.erase(words.begin() + index);
}

/**
 * Creates a list of literal candidates for the i'th word in the sentence. It combines the results of
 * 1. All possible root forms of the i'th word in the sentence
 * 2. All possible 2-word expressions containing the i'th word in the sentence
 * 3. All possible 3-word expressions containing the i'th word in the sentence
 * @param wordNet Turkish wordnet
 * @param fsm Turkish morphological analyzer
 * @param wordIndex Word index
 * @return List of literal candidates containing all possible root forms and multiword expressions.
 */
vector<Literal> AnnotatedSentence::constructLiterals(WordNet& wordNet, FsmMorphologicalAnalyzer& fsm, int wordIndex) {
    auto* word = (AnnotatedWord*) getWord(wordIndex);
    vector<Literal> possibleLiterals;
    MorphologicalParse* morphologicalParse = word->getParse();
    MetamorphicParse* metamorphicParse = word->getMetamorphicParse();
    vector<Literal> added = wordNet.constructLiterals(morphologicalParse->getWord()->getName(), *morphologicalParse, *metamorphicParse, fsm);
    possibleLiterals.insert(possibleLiterals.end(), added.begin(), added.end());
    AnnotatedWord* firstSucceedingWord = nullptr;
    AnnotatedWord* secondSucceedingWord = nullptr;
    if (wordCount() > wordIndex + 1) {
        firstSucceedingWord = (AnnotatedWord*) getWord(wordIndex + 1);
        if (wordCount() > wordIndex + 2) {
            secondSucceedingWord = (AnnotatedWord*) getWord(wordIndex + 2);
        }
    }
    if (firstSucceedingWord != nullptr) {
        if (secondSucceedingWord != nullptr) {
            added = wordNet.constructIdiomLiterals(*(word->getParse()), *(firstSucceedingWord->getParse()), *(secondSucceedingWord->getParse()), *(word->getMetamorphicParse()), *(firstSucceedingWord->getMetamorphicParse()), *(secondSucceedingWord->getMetamorphicParse()), fsm);
            possibleLiterals.insert(possibleLiterals.end(), added.begin(), added.end());
        }
        added = wordNet.constructIdiomLiterals(*(word->getParse()), *(firstSucceedingWord->getParse()), *(word->getMetamorphicParse()), *(firstSucceedingWord->getMetamorphicParse()), fsm);
        possibleLiterals.insert(possibleLiterals.end(), added.begin(), added.end());
    }
    return possibleLiterals;
}

/**
 * Creates a list of synset candidates for the i'th word in the sentence. It combines the results of
 * 1. All possible synsets containing the i'th word in the sentence
 * 2. All possible synsets containing 2-word expressions, which contains the i'th word in the sentence
 * 3. All possible synsets containing 3-word expressions, which contains the i'th word in the sentence
 * @param wordNet Turkish wordnet
 * @param fsm Turkish morphological analyzer
 * @param wordIndex Word index
 * @return List of synset candidates containing all possible root forms and multiword expressions.
 */
vector<SynSet> AnnotatedSentence::constructSynSets(WordNet& wordNet, FsmMorphologicalAnalyzer& fsm, int wordIndex) {
    auto* word = (AnnotatedWord*) getWord(wordIndex);
    vector<SynSet> possibleSynSets;
    MorphologicalParse* morphologicalParse = word->getParse();
    if (morphologicalParse == nullptr){
        return possibleSynSets;
    }
    MetamorphicParse* metamorphicParse = word->getMetamorphicParse();
    vector<SynSet> added = wordNet.constructSynSets(morphologicalParse->getWord()->getName(), *morphologicalParse, *metamorphicParse, fsm);
    possibleSynSets.insert(possibleSynSets.end(), added.begin(), added.end());
    AnnotatedWord* firstPrecedingWord = nullptr;
    AnnotatedWord* secondPrecedingWord = nullptr;
    AnnotatedWord* firstSucceedingWord = nullptr;
    AnnotatedWord* secondSucceedingWord = nullptr;
    if (wordIndex > 0) {
        firstPrecedingWord = (AnnotatedWord*) getWord(wordIndex - 1);
        if (firstPrecedingWord->getParse() == nullptr){
            return possibleSynSets;
        }
        if (wordIndex > 1) {
            secondPrecedingWord = (AnnotatedWord*) getWord(wordIndex - 2);
            if (secondPrecedingWord->getParse() == nullptr){
                return possibleSynSets;
            }
        }
    }
    if (wordCount() > wordIndex + 1) {
        firstSucceedingWord = (AnnotatedWord*) getWord(wordIndex + 1);
        if (firstSucceedingWord->getParse() == nullptr){
            return possibleSynSets;
        }
        if (wordCount() > wordIndex + 2) {
            secondSucceedingWord = (AnnotatedWord*) getWord(wordIndex + 2);
            if (secondSucceedingWord->getParse() == nullptr){
                return possibleSynSets;
            }
        }
    }
    if (firstPrecedingWord != nullptr) {
        if (secondPrecedingWord != nullptr) {
            added = wordNet.constructIdiomSynSets(*(secondPrecedingWord->getParse()), *(firstPrecedingWord->getParse()), *(word->getParse()), *(secondPrecedingWord->getMetamorphicParse()), *(firstPrecedingWord->getMetamorphicParse()), *(word->getMetamorphicParse()), fsm);
            possibleSynSets.insert(possibleSynSets.end(), added.begin(), added.end());
        }
        added = wordNet.constructIdiomSynSets(*(firstPrecedingWord->getParse()), *(word->getParse()), *(firstPrecedingWord->getMetamorphicParse()), *(word->getMetamorphicParse()), fsm);
        possibleSynSets.insert(possibleSynSets.end(), added.begin(), added.end());
    }
    if (firstPrecedingWord != nullptr && firstSucceedingWord != nullptr) {
        added = wordNet.constructIdiomSynSets(*(firstPrecedingWord->getParse()), *(word->getParse()), *(firstSucceedingWord->getParse()), *(firstPrecedingWord->getMetamorphicParse()), *(word->getMetamorphicParse()), *(firstSucceedingWord->getMetamorphicParse()), fsm);
        possibleSynSets.insert(possibleSynSets.end(), added.begin(), added.end());
    }
    if (firstSucceedingWord != nullptr) {
        if (secondSucceedingWord != nullptr) {
            added = wordNet.constructIdiomSynSets(*(word->getParse()), *(firstSucceedingWord->getParse()), *(secondSucceedingWord->getParse()), *(word->getMetamorphicParse()), *(firstSucceedingWord->getMetamorphicParse()), *(secondSucceedingWord->getMetamorphicParse()), fsm);
            possibleSynSets.insert(possibleSynSets.end(), added.begin(), added.end());
        }
        added = wordNet.constructIdiomSynSets(*(word->getParse()), *(firstSucceedingWord->getParse()), *(word->getMetamorphicParse()), *(firstSucceedingWord->getMetamorphicParse()), fsm);
        possibleSynSets.insert(possibleSynSets.end(), added.begin(), added.end());
    }
    return possibleSynSets;
}

/**
 * The toStems method returns an accumulated string of each word's stems in words ArrayList.
 * If the parse of the word does not exist, the method adds the surfaceform to the resulting string.
 *
 * @return String result which has all the stems of each item in words ArrayList.
 */
string AnnotatedSentence::toStems() const{
    string result;
    AnnotatedWord* annotatedWord;
    if (!words.empty()) {
        annotatedWord = (AnnotatedWord*) words[0];
        if (annotatedWord->getParse() != nullptr){
            result = annotatedWord->getParse()->getWord()->getName();
        } else {
            result = annotatedWord->getName();
        }
        for (int i = 1; i < words.size(); i++) {
            annotatedWord = (AnnotatedWord*) words[i];
            if (annotatedWord->getParse() != nullptr){
                result += " " + annotatedWord->getParse()->getWord()->getName();
            } else {
                result += " " + annotatedWord->getName();
            }
        }
        return result;
    } else {
        return "";
    }
}

ParserEvaluationScore AnnotatedSentence::compareParses(AnnotatedSentence *sentence) const{
    ParserEvaluationScore score = ParserEvaluationScore();
    for (int i = 0; i < wordCount(); i++){
        UniversalDependencyRelation* relation1 = ((AnnotatedWord*) words.at(i))->getUniversalDependency();
        UniversalDependencyRelation* relation2 = ((AnnotatedWord*) sentence->getWord(i))->getUniversalDependency();
        if (relation1 != nullptr && relation2 != nullptr){
            score.add(relation1->compareRelations(relation2));
        }
    }
    return score;
}

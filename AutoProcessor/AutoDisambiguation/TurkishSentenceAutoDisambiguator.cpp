//
// Created by olcay on 2.05.2019.
//

#include "TurkishSentenceAutoDisambiguator.h"

/**
 * Constructor for the class.
 * @param rootWordStatistics The object contains information about the selected correct root words in a corpus for a set
 *                           of possible lemma. For example, the lemma
 *                           `günü': 2 possible root words `gün' and `günü'
 *                           `çağlar' : 2 possible root words `çağ' and `çağlar'
 */
TurkishSentenceAutoDisambiguator::TurkishSentenceAutoDisambiguator(FsmMorphologicalAnalyzer& morphologicalAnalyzer, RootWordStatistics& rootWordStatistics) : SentenceAutoDisambiguator(morphologicalAnalyzer, rootWordStatistics) {
}

/**
 * The method disambiguates the words with a single morphological analysis. Basically the
 * method sets the morphological analysis of the words with one possible morphological analysis. If the word
 * is already morphologically disambiguated, the method does not disambiguate that word.
 * @param sentence The sentence to be disambiguated automatically.
 */
void TurkishSentenceAutoDisambiguator::autoFillSingleAnalysis(AnnotatedSentence* sentence) {
    for (int i = 0; i < sentence->wordCount(); i++){
        auto* word = (AnnotatedWord*) sentence->getWord(i);
        if (word->getParse() == nullptr){
            FsmParseList fsmParseList = morphologicalAnalyzer.robustMorphologicalAnalysis(word->getName());
            if (fsmParseList.size() == 1){
                word->setParse(fsmParseList.getFsmParse(0).getTransitionList());
                word->setMetamorphicParse(fsmParseList.getFsmParse(0).getWithList());
            }
        }
    }
}

/**
 * If the words has only single root in its possible parses, the method disambiguates by looking special cases.
 * The cases are implemented in the caseDisambiguator method.
 * @param fsmParseList Morphological parses of the word.
 * @param word Word to be disambiguated.
 */
void TurkishSentenceAutoDisambiguator::setParseAutomatically(FsmParseList fsmParseList, AnnotatedWord *word) {
    if (fsmParseList.size() > 0 && fsmParseList.rootWords().find('$') == string::npos){
        FsmParse* disambiguatedParse = fsmParseList.caseDisambiguator();
        if (disambiguatedParse != nullptr){
            word->setParse(disambiguatedParse->getTransitionList());
            word->setMetamorphicParse(disambiguatedParse->getWithList());
        }
    }
}

/**
 * The method disambiguates words with multiple possible root words in its morphological parses. If the word
 * is already morphologically disambiguated, the method does not disambiguate that word. The method first check
 * for multiple root words by using rootWords method. If there are multiple root words, the method select the most
 * occurring root word (if its occurence wrt other root words occurence is above some threshold) for that word
 * using the bestRootWord method. If root word is selected, then the case for single root word is called.
 * @param sentence The sentence to be disambiguated automatically.
 */
void TurkishSentenceAutoDisambiguator::autoDisambiguateMultipleRootWords(AnnotatedSentence* sentence) {
    for (int i = 0; i < sentence->wordCount(); i++){
        auto* word = (AnnotatedWord*) sentence->getWord(i);
        if (word->getParse() == nullptr){
            FsmParseList fsmParseList = morphologicalAnalyzer.robustMorphologicalAnalysis(word->getName());
            if (fsmParseList.rootWords().find('$') != string::npos){
                string bestRootWord = rootWordStatistics.bestRootWord(fsmParseList, 0.0);
                if (!bestRootWord.empty()){
                    fsmParseList.reduceToParsesWithSameRoot(bestRootWord);
                }
            }
            setParseAutomatically(fsmParseList, word);
        }
    }
}

/**
 * The method disambiguates words with single possible root word in its morphological parses. If the word
 * is already morphologically disambiguated, the method does not disambiguate that word. Basically calls
 * setParseAutomatically method.
 * @param sentence The sentence to be disambiguated automatically.
 */
void TurkishSentenceAutoDisambiguator::autoDisambiguateSingleRootWords(AnnotatedSentence* sentence) {
    for (int i = 0; i < sentence->wordCount(); i++){
        auto* word = (AnnotatedWord*) sentence->getWord(i);
        if (word->getParse() == nullptr){
            FsmParseList fsmParseList = morphologicalAnalyzer.robustMorphologicalAnalysis(word->getName());
            setParseAutomatically(fsmParseList, word);
        }
    }
}

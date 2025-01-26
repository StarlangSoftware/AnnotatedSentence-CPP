//
// Created by Olcay Taner Yıldız on 2019-04-24.
//

#include "AnnotatedWord.h"
#include "NamedEntityType.h"
#include "StringUtils.h"

/**
 * Constructor for the AnnotatedWord class. Gets the word with its annotation layers as input and sets the
 * corresponding layers.
 * @param word Input word with annotation layers
 */
AnnotatedWord::AnnotatedWord(const string& word) {
    vector<string> splitLayers = StringUtils::split(word, "[\\{\\}]");
    for (const string& layer:splitLayers){
        if (layer.empty())
            continue;
        if (layer.find('=') == string::npos){
            name = layer;
            continue;
        }
        string layerType = Word::substring(layer, 0, layer.find('='));
        string layerValue = Word::substring(layer, layer.find('=') + 1);
        if (layerType == "turkish" || layerType == "english" || layerType == "persian"){
            name = layerValue;
            language = getLanguageFromString(layerType);
        } else {
            if (layerType == "morphologicalAnalysis"){
                parse = new MorphologicalParse(layerValue);
            } else {
                if (layerType == "metaMorphemes"){
                    metamorphicParse = new MetamorphicParse(layerValue);
                } else {
                    if (layerType == "semantics"){
                        semantic = layerValue;
                    } else {
                        if (layerType == "namedEntity"){
                            namedEntityType = new NamedEntityType(getNamedEntityType(layerValue));
                        } else {
                            if (layerType == "propbank" || layerType == "propBank"){
                                argumentList = new ArgumentList(layerValue);
                            } else {
                                if (layerType == "shallowParse"){
                                    shallowParse = layerValue;
                                } else {
                                    if (layerType == "universalDependency"){
                                        vector<string> values = StringUtils::split(layerValue, "\\$");
                                        universalDependency = new UniversalDependencyRelation(std::stoi(values.at(0)), values.at(1));
                                    } else {
                                        if (layerType == "framenet" || layerType == "frameNet"){
                                            frameElementList = new FrameElementList(layerValue);
                                        } else {
                                            if (layerType == "slot"){
                                                slot = new Slot(layerValue);
                                            } else {
                                                if (layerType == "polarity"){
                                                    setPolarity(layerValue);
                                                } else {
                                                    if (layerType == "ccg") {
                                                        ccg = layerValue;
                                                    } else {
                                                        if (layerType == "posTag") {
                                                            posTag = layerValue;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

/**
 * Another constructor for AnnotatedWord. Gets the word and a namedEntityType and sets two layers.
 * @param name Lemma of the word.
 * @param namedEntityType Named entity of the word.
 */
AnnotatedWord::AnnotatedWord(const string& name, NamedEntityType* namedEntityType) : Word(name) {
    this->namedEntityType = namedEntityType;
}

/**
 * Converts an AnnotatedWord to string. For each annotation layer, the method puts a left brace, layer name,
 * equal sign and layer value finishing with right brace.
 * @return String form of the AnnotatedWord.
 */
string AnnotatedWord::to_string() const{
    string result;
    switch (language) {
        case Language::TURKISH:
            result = "{turkish=" + name + "}";
            break;
        case Language::ENGLISH:
            result = "{english=" + name + "}";
            break;
        case Language::PERSIAN:
            result = "{persian=" + name + "}";
            break;
    }
    if (parse != nullptr){
        result = result + "{morphologicalAnalysis=" + parse->to_string() + "}";
    }
    if (metamorphicParse != nullptr){
        result = result + "{metaMorphemes=" + metamorphicParse->to_string() + "}";
    }
    if (!semantic.empty()){
        result = result + "{semantics=" + semantic + "}";
    }
    if (namedEntityType != nullptr){
        result = result + "{namedEntity=" + getNamedEntityType(*namedEntityType) + "}";
    }
    if (argumentList != nullptr){
        result = result + "{propbank=" + argumentList->to_string() + "}";
    }
    if (frameElementList != nullptr){
        result = result + "{framenet=" + frameElementList->to_string() + "}";
    }
    if (!shallowParse.empty()){
        result = result + "{shallowParse=" + shallowParse + "}";
    }
    if (universalDependency != nullptr){
        result = result + "{universalDependency=" + std::to_string(universalDependency->to()) + "$" + universalDependency->to_string() + "}";
    }
    if (slot != nullptr){
        result = result + "{slot=" + slot->to_string() + "}";
    }
    if (polarity != nullptr){
        result = result + "{polarity=" + getPolarityString() + "}";
    }
    if (!ccg.empty()) {
        result = result + "{ccg=" + ccg + "}";
    }
    if (!posTag.empty()) {
        result = result + "{posTag=" + posTag + "}";
    }
    return result;
}

/**
 * Another constructor for AnnotatedWord. Gets the word and morphological parse and sets two layers.
 * @param name Lemma of the word.
 * @param parse Morphological parse of the word.
 */
AnnotatedWord::AnnotatedWord(const string& name, MorphologicalParse *parse) : Word(name) {
    this->parse = parse;
}

/**
 * Another constructor for AnnotatedWord. Gets the word and morphological parse and sets two layers.
 * @param name Lemma of the word.
 * @param parse Morphological parse of the word.
 */
AnnotatedWord::AnnotatedWord(const string& name, FsmParse *parse) : Word(name){
    this->parse = parse;
    setMetamorphicParse(parse->getWithList());
}

/**
 * Returns the value of a given layer.
 * @param viewLayerType Layer for which the value questioned.
 * @return The value of the given layer.
 */
string AnnotatedWord::getLayerInfo(ViewLayerType viewLayerType) const{
    switch (viewLayerType){
        case ViewLayerType::INFLECTIONAL_GROUP:
            if (parse != nullptr){
                return parse->to_string();
            }
            break;
        case ViewLayerType::META_MORPHEME:
            if (metamorphicParse != nullptr){
                return metamorphicParse->to_string();
            }
            break;
        case ViewLayerType::SEMANTICS:
            return semantic;
        case ViewLayerType::NER:
            if (namedEntityType != nullptr){
                return getNamedEntityType(*namedEntityType);
            }
            break;
        case ViewLayerType::SHALLOW_PARSE:
            return shallowParse;
        case ViewLayerType::TURKISH_WORD:
            return name;
        case ViewLayerType::PROPBANK:
            if (argumentList != nullptr){
                return argumentList->to_string();
            }
            break;
        case ViewLayerType::FRAMENET:
            if (frameElementList != nullptr){
                return frameElementList->to_string();
            }
            break;
        case ViewLayerType::DEPENDENCY:
            if (universalDependency != nullptr){
                return std::to_string(universalDependency->to()) + "$" + universalDependency->to_string();
            }
            break;
        case ViewLayerType::SLOT:
            if (slot != nullptr){
                return slot->to_string();
            }
            break;
        case ViewLayerType::POLARITY:
            if (polarity != nullptr){
                return getPolarityString();
            }
            break;
        case ViewLayerType::CCG:
            return ccg;
        case ViewLayerType::POS_TAG:
            return posTag;
    }
    return "";
}

/**
 * Returns the morphological parse layer of the word.
 * @return The morphological parse of the word.
 */
MorphologicalParse *AnnotatedWord::getParse() const{
    return parse;
}

/**
 * Sets the morphological parse layer of the word.
 * @param parseString The new morphological parse of the word in string form.
 */
void AnnotatedWord::setParse(const string& parseString) {
    if (!parseString.empty()){
        parse = new MorphologicalParse(parseString);
    } else {
        parse = nullptr;
    }
}

/**
 * Returns the metamorphic parse layer of the word.
 * @return The metamorphic parse of the word.
 */
MetamorphicParse *AnnotatedWord::getMetamorphicParse() const{
    return metamorphicParse;
}

/**
 * Sets the metamorphic parse layer of the word.
 * @param parseString The new metamorphic parse of the word in string form.
 */
void AnnotatedWord::setMetamorphicParse(const string& parseString) {
    metamorphicParse = new MetamorphicParse(parseString);
}

/**
 * Returns the semantic layer of the word.
 * @return Sense id of the word.
 */
string AnnotatedWord::getSemantic() const{
    return semantic;
}

/**
 * Sets the _semantic layer of the word.
 * @param _semantic New sense id of the word.
 */
void AnnotatedWord::setSemantic(const string& _semantic) {
    this->semantic = _semantic;
}

/**
 * Returns the named entity layer of the word.
 * @return Named entity tag of the word.
 */
NamedEntityType *AnnotatedWord::getNamedEntity() const{
    return namedEntityType;
}

/**
 * Sets the named entity layer of the word.
 * @param namedEntity New named entity tag of the word.
 */
void AnnotatedWord::setNamedEntityType(const string& namedEntity) {
    if (!namedEntity.empty()){
        namedEntityType = new NamedEntityType(getNamedEntityType(namedEntity));
    } else {
        namedEntityType = nullptr;
    }
}

/**
 * Returns the semantic role layer of the word.
 * @return Semantic role tag of the word.
 */
ArgumentList *AnnotatedWord::getArgumentList() const{
    return argumentList;
}

/**
 * Sets the semantic role layer of the word.
 * @param _argument New semantic role tag of the word.
 */
void AnnotatedWord::setArgumentList(const string& _argument) {
    if (!_argument.empty()){
        this->argumentList = new ArgumentList(_argument);
    } else {
        this->argumentList = nullptr;
    }
}

/**
 * Returns the framenet layer of the word.
 * @return Framenet tag of the word.
 */
FrameElementList *AnnotatedWord::getFrameElementList() const{
    return frameElementList;
}

/**
 * Sets the framenet layer of the word.
 * @param _frameElement New framenet tag of the word.
 */
void AnnotatedWord::setFrameElementList(const string& _frameElement) {
    if (!_frameElement.empty()){
        this->frameElementList = new FrameElementList(_frameElement);
    } else {
        this->frameElementList = nullptr;
    }
}

/**
 * Returns the slot filling layer of the word.
 * @return Slot tag of the word.
 */
Slot *AnnotatedWord::getSlot() const{
    return slot;
}

/**
 * Sets the _slot filling layer of the word.
 * @param _slot New _slot tag of the word.
 */
void AnnotatedWord::setSlot(const string& _slot) {
    if (!_slot.empty()){
        this->slot = new Slot(_slot);
    } else {
        this->slot = nullptr;
    }
}

/**
 * Returns the polarity layer of the word.
 * @return Polarity tag of the word.
 */
PolarityType* AnnotatedWord::getPolarity() const{
    return polarity;
}

/**
 * Sets the slot filling layer of the word.
 * @param _polarity New polarity tag of the word.
 */
void AnnotatedWord::setPolarity(const string& _polarity) {
    if (!_polarity.empty()){
        if (_polarity == "positive" || _polarity == "pos"){
            this->polarity = new PolarityType(PolarityType::POSITIVE);
        } else {
            if (_polarity == "negative" || _polarity == "neg"){
                this->polarity = new PolarityType(PolarityType::NEGATIVE);
            } else {
                this->polarity = new PolarityType(PolarityType::NEUTRAL);
            }
        }
    } else {
        this->polarity = nullptr;
    }
}

/**
 * Returns the polarity layer of the word.
 * @return Polarity string of the word.
 */
string AnnotatedWord::getPolarityString() const{
    switch (*polarity){
        case PolarityType::POSITIVE:
            return "positive";
        case PolarityType::NEGATIVE:
            return "negative";
        case PolarityType::NEUTRAL:
        default:
            return "neutral";
    }
}

/**
 * Returns the shallow parse layer of the word.
 * @return Shallow parse tag of the word.
 */
string AnnotatedWord::getShallowParse() const{
    return shallowParse;
}

/**
 * Sets the shallow _parse layer of the word.
 * @param _parse New shallow _parse tag of the word.
 */
void AnnotatedWord::setShallowParse(const string& _parse) {
    this->shallowParse = _parse;
}

/**
 * Returns the universal dependency layer of the word.
 * @return Universal dependency relation of the word.
 */
UniversalDependencyRelation* AnnotatedWord::getUniversalDependency() const{
    return universalDependency;
}

/**
 * Sets the universal dependency layer of the word.
 * @param to Word related to.
 * @param dependencyType type of dependency the word is related to.
 */
void AnnotatedWord::setUniversalDependency(int to, const string& dependencyType) {
    this->universalDependency = new UniversalDependencyRelation(to, dependencyType);
}

/**
 * Returns the CCG layer of the word.
 * @return CCG string of the word.
 */
string AnnotatedWord::getCcg() const{
    return ccg;
}

/**
 * Sets the CCG layer of the word.
 * @param _ccg New CCG of the word.
 */
void AnnotatedWord::setCcg(const string& _ccg) {
    this->ccg = _ccg;
}

/**
 * Returns the posTag layer of the word.
 * @return PosTag string of the word.
 */
string AnnotatedWord::getPosTag() const{
    return posTag;
}

/**
 * Sets the posTag layer of the word.
 * @param _posTag New posTag of the word.
 */
void AnnotatedWord::setPosTag(const string& _posTag) {
    this->posTag = _posTag;
}

/**
 * Checks the gazetteer and sets the named entity tag accordingly.
 * @param gazetteer Gazetteer used to set named entity tag.
 */
void AnnotatedWord::checkGazetteer(const Gazetteer &gazetteer){
    if (gazetteer.contains(name) && parse->containsTag(MorphologicalTag::PROPERNOUN)){
        setNamedEntityType(gazetteer.getName());
    }
    if (name.find('\'') != string::npos && gazetteer.contains(name.substr(0, name.find('\''))) && parse->containsTag(MorphologicalTag::PROPERNOUN)){
        setNamedEntityType(gazetteer.getName());
    }
}

/**
 * Converts a language string to language.
 * @param languageString String defining the language name.
 * @return Language corresponding to the languageString.
 */
Language AnnotatedWord::getLanguageFromString(const string& languageString) const{
    if (languageString == "turkish" || languageString == "Turkish") {
        return Language::TURKISH;
    } else {
        if (languageString == "english" || languageString == "English") {
            return Language::ENGLISH;
        } else {
            if (languageString == "persian" || languageString == "Persian") {
                return Language::PERSIAN;
            }
        }
    }
    return Language::TURKISH;
}

/**
 * Returns the language of the word.
 * @return The language of the word.
 */
Language AnnotatedWord::getLanguage() const{
    return language;
}

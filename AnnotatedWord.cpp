//
// Created by Olcay Taner Yıldız on 2019-04-24.
//

#include "AnnotatedWord.h"
#include "NamedEntityType.h"

/**
 * Constructor for the {@link AnnotatedWord} class. Gets the word with its annotation layers as input and sets the
 * corresponding layers.
 * @param word Input word with annotation layers
 */
AnnotatedWord::AnnotatedWord(string word) {
    vector<string> splitLayers = Word::split(move(word), "[\\{\\}]");
    for (const string& layer:splitLayers){
        if (layer.empty())
            continue;
        if (layer.find('=') == string::npos){
            name = layer;
            continue;
        }
        string layerType = Word::substring(layer, 0, layer.find('='));
        string layerValue = Word::substring(layer, layer.find('=') + 1);
        if (layerType == "turkish"){
            name = layerValue;
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
                            if (layerType == "propbank"){
                                argument = new Argument(layerValue);
                            } else {
                                if (layerType == "shallowParse"){
                                    shallowParse = layerValue;
                                } else {
                                    if (layerType == "universalDependency"){
                                        vector<string> values = Word::split(move(layerValue), "\\$");
                                        universalDependency = new UniversalDependencyRelation(std::stoi(values.at(0)), values.at(1));
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
 * Another constructor for {@link AnnotatedWord}. Gets the word and a namedEntityType and sets two layers.
 * @param name Lemma of the word.
 * @param namedEntityType Named entity of the word.
 */
AnnotatedWord::AnnotatedWord(string name, NamedEntityType* namedEntityType) : Word(move(name)) {
    this->namedEntityType = namedEntityType;
    parse = nullptr;
    metamorphicParse = nullptr;
    semantic = "";
    argument = nullptr;
    shallowParse = "";
    universalDependency = nullptr;
}

AnnotatedWord::~AnnotatedWord() {
    delete namedEntityType;
    delete parse;
    delete metamorphicParse;
    delete argument;
    delete universalDependency;
}

/**
 * Converts an {@link AnnotatedWord} to string. For each annotation layer, the method puts a left brace, layer name,
 * equal sign and layer value finishing with right brace.
 * @return String form of the {@link AnnotatedWord}.
 */
string AnnotatedWord::to_string() {
    string result = "{turkish=" + name + "}";
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
    if (argument != nullptr){
        result = result + "{propbank=" + argument->to_string() + "}";
    }
    if (!shallowParse.empty()){
        result = result + "{shallowParse=" + shallowParse + "}";
    }
    if (universalDependency != nullptr){
        result = result + "{universalDependency=" + std::to_string(universalDependency->to()) + "$" + universalDependency->to_string() + "}";
    }
    return result;
}

/**
 * Another constructor for {@link AnnotatedWord}. Gets the word and morphological parse and sets two layers.
 * @param name Lemma of the word.
 * @param parse Morphological parse of the word.
 */
AnnotatedWord::AnnotatedWord(string name, MorphologicalParse *parse) : Word(move(name)) {
    this->parse = parse;
    this->namedEntityType = nullptr;
    argument = nullptr;
    metamorphicParse = nullptr;
    semantic = "";
    shallowParse = "";
    universalDependency = nullptr;
}

/**
 * Another constructor for {@link AnnotatedWord}. Gets the word and morphological parse and sets two layers.
 * @param name Lemma of the word.
 * @param parse Morphological parse of the word.
 */
AnnotatedWord::AnnotatedWord(string name, FsmParse *parse) : Word(move(name)){
    this->parse = parse;
    namedEntityType = nullptr;
    argument = nullptr;
    setMetamorphicParse(parse->getWithList());
    semantic = "";
    shallowParse = "";
    universalDependency = nullptr;
}

/**
 * Returns the value of a given layer.
 * @param viewLayerType Layer for which the value questioned.
 * @return The value of the given layer.
 */
string AnnotatedWord::getLayerInfo(ViewLayerType viewLayerType) {
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
            if (argument != nullptr){
                return argument->to_string();
            }
            break;
        case ViewLayerType::DEPENDENCY:
            if (universalDependency != nullptr){
                return std::to_string(universalDependency->to()) + "$" + universalDependency->to_string();
            }
            break;
    }
    return "";
}

/**
 * Returns the morphological parse layer of the word.
 * @return The morphological parse of the word.
 */
MorphologicalParse *AnnotatedWord::getParse() {
    return parse;
}

/**
 * Sets the morphological parse layer of the word.
 * @param parseString The new morphological parse of the word in string form.
 */
void AnnotatedWord::setParse(string parseString) {
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
MetamorphicParse *AnnotatedWord::getMetamorphicParse() {
    return metamorphicParse;
}

/**
 * Sets the metamorphic parse layer of the word.
 * @param parseString The new metamorphic parse of the word in string form.
 */
void AnnotatedWord::setMetamorphicParse(string parseString) {
    metamorphicParse = new MetamorphicParse(move(parseString));
}

/**
 * Returns the semantic layer of the word.
 * @return Sense id of the word.
 */
string AnnotatedWord::getSemantic() {
    return semantic;
}

/**
 * Sets the semantic layer of the word.
 * @param semantic New sense id of the word.
 */
void AnnotatedWord::setSemantic(string semantic) {
    this->semantic = move(semantic);
}

/**
 * Returns the named entity layer of the word.
 * @return Named entity tag of the word.
 */
NamedEntityType *AnnotatedWord::getNamedEntity() {
    return namedEntityType;
}

/**
 * Sets the named entity layer of the word.
 * @param namedEntity New named entity tag of the word.
 */
void AnnotatedWord::setNamedEntityType(string namedEntity) {
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
Argument *AnnotatedWord::getArgument() {
    return argument;
}

/**
 * Sets the semantic role layer of the word.
 * @param argument New semantic role tag of the word.
 */
void AnnotatedWord::setArgument(string argument) {
    if (!argument.empty()){
        this->argument = new Argument(argument);
    } else {
        this->argument = nullptr;
    }
}

/**
 * Returns the shallow parse layer of the word.
 * @return Shallow parse tag of the word.
 */
string AnnotatedWord::getShallowParse() {
    return shallowParse;
}

/**
 * Sets the shallow parse layer of the word.
 * @param parse New shallow parse tag of the word.
 */
void AnnotatedWord::setShallowParse(string parse) {
    this->shallowParse = move(parse);
}

/**
 * Returns the universal dependency layer of the word.
 * @return Universal dependency relation of the word.
 */
UniversalDependencyRelation* AnnotatedWord::getUniversalDependency() {
    return universalDependency;
}

/**
 * Sets the universal dependency layer of the word.
 * @param to Word related to.
 * @param dependencyType type of dependency the word is related to.
 */
void AnnotatedWord::setUniversalDependency(int to, string dependencyType) {
    this->universalDependency = new UniversalDependencyRelation(to, move(dependencyType));
}

void AnnotatedWord::checkGazetteer(Gazetteer gazetteer) {
    if (gazetteer.contains(name) && parse->containsTag(MorphologicalTag::PROPERNOUN)){
        setNamedEntityType(gazetteer.getName());
    }
    if (name.find('\'') != string::npos && gazetteer.contains(name.substr(0, name.find('\''))) && parse->containsTag(MorphologicalTag::PROPERNOUN)){
        setNamedEntityType(gazetteer.getName());
    }
}

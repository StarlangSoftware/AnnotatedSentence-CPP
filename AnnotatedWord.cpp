//
// Created by Olcay Taner Yıldız on 2019-04-24.
//

#include "AnnotatedWord.h"
#include "NamedEntityType.h"

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
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

AnnotatedWord::AnnotatedWord(string name, NamedEntityType* namedEntityType) : Word(move(name)) {
    this->namedEntityType = namedEntityType;
    parse = nullptr;
    metamorphicParse = nullptr;
    semantic = "";
    argument = nullptr;
    shallowParse = "";
}

AnnotatedWord::~AnnotatedWord() {
    if (namedEntityType != nullptr){
        delete namedEntityType;
    }
    if (parse != nullptr){
        delete parse;
    }
    if (metamorphicParse != nullptr){
        delete metamorphicParse;
    }
    if (argument != nullptr){
        delete argument;
    }
}

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
    return result;
}

AnnotatedWord::AnnotatedWord(string name, MorphologicalParse *parse) : Word(move(name)) {
    this->parse = parse;
    this->namedEntityType = nullptr;
    argument = nullptr;
    metamorphicParse = nullptr;
    semantic = "";
    shallowParse = "";
}

AnnotatedWord::AnnotatedWord(string name, FsmParse *parse) : Word(move(name)){
    this->parse = parse;
    namedEntityType = nullptr;
    argument = nullptr;
    setMetamorphicParse(parse->getWithList());
    semantic = "";
    shallowParse = "";
}

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
    }
    return "";
}

MorphologicalParse *AnnotatedWord::getParse() {
    return parse;
}

void AnnotatedWord::setParse(string parseString) {
    if (!parseString.empty()){
        parse = new MorphologicalParse(parseString);
    } else {
        parse = nullptr;
    }
}

MetamorphicParse *AnnotatedWord::getMetamorphicParse() {
    return metamorphicParse;
}

void AnnotatedWord::setMetamorphicParse(string parseString) {
    metamorphicParse = new MetamorphicParse(move(parseString));
}

string AnnotatedWord::getSemantic() {
    return semantic;
}

void AnnotatedWord::setSemantic(string semantic) {
    this->semantic = move(semantic);
}

NamedEntityType *AnnotatedWord::getNamedEntity() {
    return namedEntityType;
}

void AnnotatedWord::setNamedEntityType(string namedEntity) {
    if (!namedEntity.empty()){
        namedEntityType = new NamedEntityType(getNamedEntityType(namedEntity));
    } else {
        namedEntityType = nullptr;
    }
}

Argument *AnnotatedWord::getArgument() {
    return argument;
}

void AnnotatedWord::setArgument(string argument) {
    if (!argument.empty()){
        this->argument = new Argument(argument);
    } else {
        this->argument = nullptr;
    }
}

string AnnotatedWord::getShallowParse() {
    return shallowParse;
}

void AnnotatedWord::setShallowParse(string parse) {
    this->shallowParse = move(parse);
}

void AnnotatedWord::checkGazetteer(Gazetteer gazetteer) {
    if (gazetteer.contains(name) && parse->containsTag(MorphologicalTag::PROPERNOUN)){
        setNamedEntityType(gazetteer.getName());
    }
    if (name.find('\'') != string::npos && gazetteer.contains(name.substr(0, name.find('\''))) && parse->containsTag(MorphologicalTag::PROPERNOUN)){
        setNamedEntityType(gazetteer.getName());
    }
}

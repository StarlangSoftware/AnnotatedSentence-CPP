//
// Created by Olcay Taner Yıldız on 2019-04-24.
//

#include "AnnotatedWord.h"

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
                parse = MorphologicalParse(layerValue);
            } else {
                if (layerType == "metaMorphemes"){
                    metamorphicParse = MetamorphicParse(layerValue);
                } else {
                    if (layerType == "semantics"){
                        semantic = layerValue;
                    } else {
                        if (layerType == "namedEntity"){
                            namedEntityType = getNamedEntityType(layerValue);
                        } else {
                            if (layerType == "propbank"){
                                argument = Argument(layerValue);
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

AnnotatedWord::AnnotatedWord(string name, NamedEntityType namedEntityType) : Word(name) {
    this->namedEntityType = namedEntityType;
    parse = MorphologicalParse();
    metamorphicParse = MetamorphicParse();
    semantic = "";
    argument = Argument("NONE", "");
    shallowParse = "";
}

//
// Created by Olcay Taner Yıldız on 2019-04-24.
//

#ifndef ANNOTATEDSENTENCE_ANNOTATEDWORD_H
#define ANNOTATEDSENTENCE_ANNOTATEDWORD_H

#include <Word.h>
#include <MorphologicalParse.h>
#include <MetamorphicParse.h>
#include <NamedEntityType.h>
#include <Argument.h>
#include <FsmParse.h>
#include <UniversalDependencyRelation.h>
#include <FrameElement.h>
#include <PolarityType.h>
#include "ViewLayerType.h"
#include "Gazetteer.h"
#include "Slot.h"

class AnnotatedWord : public Word{
/**
 * In order to add another layer, do the following:
 * 1. Select a name for the layer.
 * 2. Add a new constant to ViewLayerType.
 * 3. Add private attribute.
 * 4. Add an if-else to the constructor, where you set the private attribute with the layer name.
 * 5. Update toString method.
 * 6. Add initial value to the private attribute in other constructors.
 * 7. Update getLayerInfo.
 * 8. Add getter and setter methods.
 */
private:
    MorphologicalParse* parse = nullptr;
    MetamorphicParse* metamorphicParse = nullptr;
    string semantic;
    NamedEntityType* namedEntityType = nullptr;
    Argument* argument = nullptr;
    FrameElement* frameElement = nullptr;
    PolarityType* polarity = nullptr;
    string shallowParse;
    Slot* slot = nullptr;
    string ccg;
    UniversalDependencyRelation* universalDependency = nullptr;
public:
    ~AnnotatedWord() override;
    explicit AnnotatedWord(string word);
    AnnotatedWord(string name, NamedEntityType* namedEntityType);
    string to_string();
    AnnotatedWord(string name, MorphologicalParse* parse);
    AnnotatedWord(string name, FsmParse* parse);
    string getLayerInfo(ViewLayerType viewLayerType);
    MorphologicalParse* getParse();
    void setParse(string parseString);
    MetamorphicParse* getMetamorphicParse();
    void setMetamorphicParse(string parseString);
    string getSemantic();
    void setSemantic(string semantic);
    NamedEntityType* getNamedEntity();
    void setNamedEntityType(string namedEntity);
    Argument* getArgument();
    void setArgument(string argument);
    FrameElement* getFrameElement();
    void setFrameElement(string frameElement);
    Slot* getSlot();
    void setSlot(string slot);
    PolarityType* getPolarity();
    string getPolarityString();
    void setPolarity(string polarity);
    string getShallowParse();
    void setShallowParse(string parse);
    UniversalDependencyRelation* getUniversalDependency();
    void setUniversalDependency(int to, string dependencyType);
    string getCcg();
    void setCcg(string ccg);
    void checkGazetteer(Gazetteer gazetteer);
};


#endif //ANNOTATEDSENTENCE_ANNOTATEDWORD_H

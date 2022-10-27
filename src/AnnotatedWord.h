//
// Created by Olcay Taner Yıldız on 2019-04-24.
//

#ifndef ANNOTATEDSENTENCE_ANNOTATEDWORD_H
#define ANNOTATEDSENTENCE_ANNOTATEDWORD_H

#include "Dictionary/Word.h"
#include <MorphologicalParse.h>
#include <MetamorphicParse.h>
#include <NamedEntityType.h>
#include <Argument.h>
#include <FsmParse.h>
#include "Universal/UniversalDependencyRelation.h"
#include <FrameElement.h>
#include <PolarityType.h>
#include "ViewLayerType.h"
#include "Language.h"
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
    string posTag;
    Language language = Language::TURKISH;
    UniversalDependencyRelation* universalDependency = nullptr;
    Language getLanguageFromString(const string& languageString) const;
public:
    explicit AnnotatedWord(const string& word);
    AnnotatedWord(const string& name, NamedEntityType* namedEntityType);
    string to_string() const;
    AnnotatedWord(const string& name, MorphologicalParse* parse);
    AnnotatedWord(const string& name, FsmParse* parse);
    string getLayerInfo(ViewLayerType viewLayerType) const;
    MorphologicalParse* getParse() const;
    void setParse(const string& parseString);
    MetamorphicParse* getMetamorphicParse() const;
    void setMetamorphicParse(const string& parseString);
    string getSemantic() const;
    void setSemantic(const string& _semantic);
    NamedEntityType* getNamedEntity() const;
    void setNamedEntityType(const string& namedEntity);
    Argument* getArgument() const;
    void setArgument(const string& _argument);
    FrameElement* getFrameElement() const;
    void setFrameElement(const string& _frameElement);
    Slot* getSlot() const;
    void setSlot(const string& _slot);
    PolarityType* getPolarity() const;
    string getPolarityString() const;
    void setPolarity(const string& _polarity);
    string getShallowParse() const;
    void setShallowParse(const string& _parse);
    UniversalDependencyRelation* getUniversalDependency() const;
    void setUniversalDependency(int to, const string& dependencyType);
    string getCcg() const;
    void setCcg(const string& _ccg);
    string getPosTag() const;
    void setPosTag(const string& _posTag);
    void checkGazetteer(Gazetteer gazetteer);
    Language getLanguage() const;
};


#endif //ANNOTATEDSENTENCE_ANNOTATEDWORD_H

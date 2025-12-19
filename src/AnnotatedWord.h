//
// Created by Olcay Taner Yıldız on 2019-04-24.
//

#ifndef ANNOTATEDSENTENCE_ANNOTATEDWORD_H
#define ANNOTATEDSENTENCE_ANNOTATEDWORD_H

#include "Dictionary/Word.h"
#include <MorphologicalParse.h>
#include <MetamorphicParse.h>
#include <NamedEntityType.h>
#include <ArgumentList.h>
#include <FsmParse.h>
#include "Universal/UniversalDependencyRelation.h"
#include <FrameElementList.h>
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
    ArgumentList* argumentList = nullptr;
    FrameElementList* frameElementList = nullptr;
    PolarityType* polarity = nullptr;
    string shallowParse;
    Slot* slot = nullptr;
    string ccg;
    string posTag;
    Language language = Language::TURKISH;
    UniversalDependencyRelation* universalDependency = nullptr;
    [[nodiscard]] Language getLanguageFromString(const string& languageString) const;
public:
    explicit AnnotatedWord(const string& word);
    AnnotatedWord(const string& name, NamedEntityType* namedEntityType);
    [[nodiscard]] string to_string() const;
    AnnotatedWord(const string& name, MorphologicalParse* parse);
    AnnotatedWord(const string& name, FsmParse* parse);
    [[nodiscard]] string getLayerInfo(ViewLayerType viewLayerType) const;
    [[nodiscard]] MorphologicalParse* getParse() const;
    void setParse(const string& parseString);
    [[nodiscard]] MetamorphicParse* getMetamorphicParse() const;
    void setMetamorphicParse(const string& parseString);
    [[nodiscard]] string getSemantic() const;
    void setSemantic(const string& _semantic);
    [[nodiscard]] NamedEntityType* getNamedEntity() const;
    void setNamedEntityType(const string& namedEntity);
    [[nodiscard]] ArgumentList* getArgumentList() const;
    void setArgumentList(const string& _argument);
    [[nodiscard]] FrameElementList* getFrameElementList() const;
    void setFrameElementList(const string& _frameElement);
    [[nodiscard]] Slot* getSlot() const;
    void setSlot(const string& _slot);
    [[nodiscard]] PolarityType* getPolarity() const;
    [[nodiscard]] string getPolarityString() const;
    void setPolarity(const string& _polarity);
    [[nodiscard]] string getShallowParse() const;
    void setShallowParse(const string& _parse);
    [[nodiscard]] UniversalDependencyRelation* getUniversalDependency() const;
    void setUniversalDependency(int to, const string& dependencyType);
    [[nodiscard]] string getCcg() const;
    void setCcg(const string& _ccg);
    [[nodiscard]] string getPosTag() const;
    void setPosTag(const string& _posTag);
    void checkGazetteer(const Gazetteer &gazetteer);
    [[nodiscard]] Language getLanguage() const;
};


#endif //ANNOTATEDSENTENCE_ANNOTATEDWORD_H

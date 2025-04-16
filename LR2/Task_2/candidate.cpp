#include "candidate.h"

Candidate::Candidate(int id, const QString &name, int age, int height, int weight, const QString &habits, const QString &hobby, int minAge, int  maxAge, int minHeight, int maxHeight, int minWeight, int maxWeight, const QString &gender)
    :m_id(id), m_name(name), m_age(age),m_height(height),m_weight(weight), m_habits(habits),m_hobby(hobby), m_minAge(minAge),m_maxAge(maxAge),m_minHeight(minHeight),m_maxHeight(maxHeight),m_minWeight(minWeight),m_maxWeight(maxWeight),m_gender(gender)
{
    bool isActive = true;
}

int Candidate::getId() const { return m_id; }
QString Candidate::getName() const { return m_name; }
int Candidate::getAge() const { return m_age; }
int Candidate::getHeight() const { return m_height; }
int Candidate::getWeight() const { return m_weight; }
QString Candidate::getHabits() const { return m_habits; }
QString Candidate::getHobby() const { return m_hobby; }
int Candidate::getMinAge() const { return m_minAge; }
int Candidate::getMaxAge() const { return m_maxAge; }
int Candidate::getMinHeight() const { return m_minHeight; }
int Candidate::getMaxHeight() const { return m_maxHeight; }
int Candidate::getMinWeight() const { return m_minWeight; }
int Candidate::getMaxWeight() const { return m_maxWeight; }
bool Candidate::getIsActive() const { return m_isActive; }
QString Candidate::getGender() const { return m_gender; }

void Candidate::setId(int id) { m_id = id; }
void Candidate::setName(const QString &name) { m_name = name; }
void Candidate::setAge(int age) { m_age = age; }
void Candidate::setHeight(int height) { m_height = height; }
void Candidate::setWeight(int weight) { m_weight = weight; }
void Candidate::setHabits(const QString &habits) { m_habits = habits; }
void Candidate::setHobby(const QString &hobby) { m_hobby = hobby; }
void Candidate::setMinAge(int value) { m_minAge = value; }
void Candidate::setMaxAge(int value) { m_maxAge = value; }
void Candidate::setMinHeight(int value) { m_minHeight = value; }
void Candidate::setMaxHeight(int value) { m_maxHeight = value; }
void Candidate::setMinWeight(int value) { m_minWeight = value; }
void Candidate::setMaxWeight(int value) { m_maxWeight = value; }
void Candidate::setIsActive(bool active) { m_isActive = active; }
void Candidate::setGender(const QString &gender) { m_gender = gender; }




bool Candidate::isSuitable(const Candidate &partner) const{
    bool partnerSuits=(partner.getAge() >= m_minAge && partner.getAge()<=m_maxAge) && (partner.getHeight()>=m_minHeight && partner.getHeight() <=m_maxHeight) && (partner.getWeight()>=m_minWeight && partner.getWeight()<=m_maxWeight);

    bool thisSuits=(m_age>=partner.getMinAge() && m_age<=partner.getMaxAge()) &&(m_weight >= partner.getMinWeight() && m_weight <= partner.getMaxWeight());

    return partnerSuits && thisSuits;
}

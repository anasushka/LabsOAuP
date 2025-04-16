#ifndef CANDIDATE_H
#define CANDIDATE_H
#include <QString>

class Candidate
{
public:
   // Candidate();

    Candidate(int id, const QString &name, int age, int height, int weight, const QString &habits, const QString & hobby,
              int minAge, int maxAge, int minHeight, int maxHeight, int minWeight, int maxWeight, const QString &gender);


    int getId() const;
    QString getName() const;
    int getAge() const;
    int getHeight() const;
    int getWeight() const;
    QString getHabits() const;
    QString getHobby() const;
    QString getGender() const;
    bool getIsActive() const;
    int getMinAge() const;
    int getMaxAge() const;
    int getMinHeight() const;
    int  getMaxHeight()const;
    int getMinWeight() const;
    int getMaxWeight() const;


    void setId(int it);
    void setName(const QString &name);
    void setAge(int age);
    void setHeight(int height);
    void setWeight(int weight);
    void  setHabits(const QString &habits);
    void setHobby(const QString &hobby);
    void setGender(const QString &gender);
    void setMinAge(int minAge);
    void setMaxAge(int maxAge);
    void setMinHeight(int minHeight);
    void setMaxHeight(int maxHeight);
    void setMinWeight(int minWeight);
    void setMaxWeight(int maxWeight);
    void setIsActive(bool active);


    bool isSuitable(const Candidate &partner) const;

private:
    int m_id;
    QString m_name;
    int m_age;
    int m_height;
    int m_weight;
    QString m_habits;
    QString m_hobby;

    //предпочтения
    int m_minAge;
    int m_maxAge;
    int m_minHeight;
    int m_maxHeight;
    int m_minWeight;
    int m_maxWeight;

    bool m_isActive;
    QString m_gender;

};

#endif // CANDIDATE_H

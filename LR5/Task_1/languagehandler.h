#ifndef LANGUAGEHANDLER_H
#define LANGUAGEHANDLER_H

#include <QObject>
#include <QMap>

class LanguageHandler : public QObject {
    Q_OBJECT
public:
    explicit LanguageHandler(QObject *parent = nullptr);
    QMap<QString, QString> loadLanguageTexts() const;
    QString getSystemLanguage() const;
};

#endif

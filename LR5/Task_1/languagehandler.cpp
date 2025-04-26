#include "languagehandler.h"
#include <QLocale>
#include <QFile>

LanguageHandler::LanguageHandler(QObject *parent) : QObject(parent) {}

QMap<QString, QString> LanguageHandler::loadLanguageTexts() const {
    QMap<QString, QString> texts;
    texts["Немецкий"] = "Dies ist ein Beispieltext für das Tastaturtraining.";
    texts["Французский"] = "Ceci est un texte d'exemple pour la formation au clavier.";
    // Добавить тексты для остальных языков...
    return texts;
}

QString LanguageHandler::getSystemLanguage() const {
    QString sysLang = QLocale::system().name().left(2);
    QMap<QString, QString> langMap = {{"de", "Немецкий"}, {"fr", "Французский"} /* ... */};
    return langMap.value(sysLang, "Английский");
}

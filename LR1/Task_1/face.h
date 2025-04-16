// face.h
#ifndef FACE_H
#define FACE_H
#include <QGraphicsScene>
#include "movingellipse.h"

class Face : public QObject
{
    Q_OBJECT

public:
    explicit Face(QGraphicsScene *scene, QObject *parent = nullptr);

public slots:
    void openMouth();
    void moveEyes();
    void resetFace();

private:
    QGraphicsScene *scene;
    MovingEllipse *faceOutline;

    // Глаза
    MovingEllipse *leftEyeWhite;
    MovingEllipse *rightEyeWhite;
    MovingEllipse *leftPupil;
    MovingEllipse *rightPupil;

    // Рот
    MovingEllipse *upperLip;
    MovingEllipse *lowerLip;

    QPointF leftPupilStartPos, rightPupilStartPos;
    QPointF upperLipStartPos, lowerLipStartPos;
};

#endif // FACE_H

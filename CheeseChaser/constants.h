#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QVector>
#include <QPair>

static const int maxTransitionFrames = 20;
static constexpr float drawDelay = 10.42f;
static const float TILE_SIZE = 50.f;
static const float TILE_SIZE_SQR = TILE_SIZE * TILE_SIZE;
static const int pIndices[4] = {-1, +1, 0, 0};
static const int qIndices[4] = {0, 0, -1, +1};
const QString mainBackgroungStyleSheet = "QWidget { background-color : grey; }";
const QString buttonsStyleSheet = "QPushButton"
                                      "{ border-radius: 5px;"
                                      "background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 white, stop: 0.75 green);"
                                      "height: 42px;"
                                      "font-size: 32px;"
                                      "max-width: 144px; }"
                                  "QPushButton:pressed"
                                      "{ background-color: darkgreen;"
                                      "  }"
                                  "QPushButton:hover:!pressed"
                                      "{ background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0.01 white, stop: 1 green);"
                                      "  }";
#endif // CONSTANTS_H

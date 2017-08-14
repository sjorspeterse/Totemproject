#include <PCD8544.h>

#include <Penpivot.h>

Penpivot myPivotingPen(55.5);
void setup() {
  // put your setup code here, to run once:
}

float deg = 0.0;
void loop() {
  deg = deg + 1;
  myPivotingPen.pivotRight(deg);
}

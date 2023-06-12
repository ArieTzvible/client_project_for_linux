
#pragma once

#ifndef HeaderTest
#define HeaderTest

#include "HeaderUtilities.h"
#include "HeaderDelet.h"
#include "CreatingManager.h"

void testingTheNewCell(ListManager manager, PClient* newCell);// Checking whether the ID already exists
void cellUpdateInLitst(PClient* newCell, PClient* temp);//Cell update
int comparisonOfCells(PClient* newCell, PClient* temp);//Cell comparison
int comparingDates(Date nweCell, Date temp);//Comparing dates
void isTheDataCorrect(PClient* client);

#endif
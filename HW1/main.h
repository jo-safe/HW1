#pragma once

#include "header.h"
#include "supply.h"
#include "stdrep.h"

void readData(Supply &supplies, string path);
void saveData(Supply supplies, string path);

void operateRequest(int param, int data);

int main();
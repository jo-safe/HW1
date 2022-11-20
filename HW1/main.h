#pragma once

#include "header.h"
#include "supply.h"
#include "stdrep.h"

#define M_OPEN_FILE 0
#define M_SAVE_FILE 1
#define M_SHOW_DATA 2

#define MpS(line, multiplier) multiplicateString(line, multiplier)

List<Supply> readData(string path);
void saveData(string path, List<Supply> data);

void operateRequest(int param, List<Supply>& data);

int main();
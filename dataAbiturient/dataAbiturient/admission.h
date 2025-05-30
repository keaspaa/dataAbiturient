#pragma once
#include <vector>

struct abiturient {
    double attestat;
    int subj1;
    int subj2;
    int subjLang;
    bool student;
};

int admission(std::vector<abiturient>& abits, int places);
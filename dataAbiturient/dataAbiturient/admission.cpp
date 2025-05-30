#include "admission.h"
#include <algorithm>

int admission(std::vector<abiturient>& abits, int places) {
    std::sort(abits.begin(), abits.end(), [](const abiturient& a, const abiturient& b) {
        double scoreA = a.attestat * 10 + a.subj1 + a.subj2 + a.subjLang;
        double scoreB = b.attestat * 10 + b.subj1 + b.subj2 + b.subjLang;
        return scoreA > scoreB;
        });

    int passingScore = 0;
    for (size_t i = 0; i < abits.size(); ++i) {
        abits[i].student = (i < static_cast<size_t>(places));
        if (i == static_cast<size_t>(places) - 1) {
            passingScore = abits[i].attestat * 10 + abits[i].subj1 + abits[i].subj2 + abits[i].subjLang;
        }
    }
    return passingScore;
}
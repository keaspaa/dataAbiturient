#include "CppUnitTest.h"
#include "../dataAbiturient/admission.h"
#include "../dataAbiturient/admission.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AdmissionTests
{
    TEST_CLASS(AdmissionTests)
    {
    public:

        TEST_METHOD(TestEmptyInput)
        {
            std::vector<abiturient> abits;
            int passingScore = admission(abits, 5);
            Assert::AreEqual(0, passingScore);
        }

        TEST_METHOD(TestZeroPlaces)
        {
            std::vector<abiturient> abits = {
                {9.5, 90, 85, 95, false},
                {8.0, 80, 75, 85, false}
            };
            int passingScore = admission(abits, 0);
            Assert::AreEqual(0, passingScore);
            Assert::IsFalse(abits[0].student);
            Assert::IsFalse(abits[1].student);
        }

        TEST_METHOD(TestMorePlacesThanApplicants)
        {
            std::vector<abiturient> abits = {
                {9.0, 80, 85, 90, false},
                {8.5, 75, 80, 85, false}
            };
            int expectedScore = 8.5 * 10 + 75 + 80 + 85;
            int passingScore = admission(abits, 5);

            Assert::AreEqual(expectedScore, passingScore);
            Assert::IsTrue(abits[0].student);
            Assert::IsTrue(abits[1].student);
        }

        TEST_METHOD(TestCompetitiveAdmission)
        {
            std::vector<abiturient> abits = {
                {10.0, 100, 100, 100, false},  // 400
                {9.5, 95, 95, 95, false},      // 380
                {9.0, 90, 90, 90, false},      // 360
                {8.5, 85, 85, 85, false},      // 340
                {8.0, 80, 80, 80, false}       // 320
            };
            int passingScore = admission(abits, 2);

            Assert::AreEqual(380, passingScore);
            Assert::IsTrue(abits[0].student);
            Assert::IsTrue(abits[1].student);
            Assert::IsFalse(abits[2].student);
            Assert::IsFalse(abits[3].student);
            Assert::IsFalse(abits[4].student);
        }

        TEST_METHOD(TestTieBreaking)
        {
            std::vector<abiturient> abits = {
                {9.0, 90, 90, 90, false},  // 360
                {9.0, 90, 90, 90, false},  // 360
                {9.0, 90, 90, 90, false},  // 360
                {8.0, 80, 80, 80, false}   // 320
            };
            int passingScore = admission(abits, 2);

            Assert::AreEqual(360, passingScore);
            Assert::IsTrue(abits[0].student);
            Assert::IsTrue(abits[1].student);
            Assert::IsFalse(abits[2].student);
            Assert::IsFalse(abits[3].student);
        }

        TEST_METHOD(TestSingleApplicant)
        {
            std::vector<abiturient> abits = {
                {8.5, 85, 80, 75, false}  // 325
            };
            int passingScore = admission(abits, 1);

            Assert::AreEqual(325, passingScore);
            Assert::IsTrue(abits[0].student);
        }

        TEST_METHOD(TestSingleApplicantNoPlaces)
        {
            std::vector<abiturient> abits = {
                {10.0, 100, 100, 100, false}  // 400
            };
            int passingScore = admission(abits, 0);

            Assert::AreEqual(0, passingScore);
            Assert::IsFalse(abits[0].student);
        }
    };
}
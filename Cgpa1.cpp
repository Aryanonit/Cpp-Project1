#include <iostream>
#include <vector>

using namespace std;

// Function to calculate CGPA
float calculateCGPA(vector<float> grades, vector<int> credits) {
    float totalGradePoints = 0.0;
    int totalCredits = 0;

    for (size_t i = 0; i < grades.size(); ++i) {
        totalGradePoints += grades[i] * credits[i];
        totalCredits += credits[i];
    }

    return totalGradePoints / totalCredits;
}

int main() {
    int numSubjects;
    cout << "Enter the number of subjects: ";
    cin >> numSubjects;

    vector<float> grades(numSubjects);
    vector<int> credits(numSubjects);

    // Input grades and credits for each subject
    for (int i = 0; i < numSubjects; ++i) {
        cout << "Enter grade (out of 10) for subject " << i + 1 << ": ";
        cin >> grades[i];
        cout << "Enter credits for subject " << i + 1 << ": ";
        cin >> credits[i];
    }

    // Calculate CGPA
    float cgpa = calculateCGPA(grades, credits);
    cout << "Your CGPA is: " << cgpa << endl;

    return 0;
}

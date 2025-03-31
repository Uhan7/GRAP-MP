#include <iostream>
#include <iomanip>

#include <string>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

void PrintVector(glm::vec3 vector){
    for (int i = 0; i < 3; i++){
        cout << fixed << setprecision(2) << i+1 << ": " << vector[i] << "\t\t";
    }
    cout << endl;
}

void PrintVector(string debugMessage, glm::vec3 vector){
    cout << debugMessage << endl;
    for (int i = 0; i < 3; i++){
        cout << fixed << setprecision(2) << i+1 << ": " << vector[i] << "\t\t";
    }
    cout << endl;
}

void PrintVector(glm::vec4 vector){
    for (int i = 0; i < 4; i++){
        cout << fixed << setprecision(2) << i+1 << ": " << vector[i] << "\t\t";
    }
    cout << endl;
}

void PrintVector(string debugMessage, glm::vec4 vector){
    cout << debugMessage << endl;
    for (int i = 0; i < 4; i++){
        cout << fixed << setprecision(2) << i+1 << ": " << vector[i] << "\t\t";
    }
    cout << endl;
}
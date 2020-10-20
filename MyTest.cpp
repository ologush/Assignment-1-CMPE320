#include <iostream>
#include <string>
#include <vector>
#include <time.h>

#include "insultgenerator_17ojl.h"

using namespace std;

int main() {
    
    InsultGenerator ig;
    
    ig.initialize();
    
    string test = ig.talkToMe();
    cout << test + "\n";

    vector<string> generatedInsults;
    generatedInsults = ig.generate(10);

    for(int i = 0; i < 10; i++) {
        cout << generatedInsults[i] << endl;
    }

    return 0;
};
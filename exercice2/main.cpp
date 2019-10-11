#include <iostream>
#include <cmath>
using namespace std;
int main(){
    float x;
    cout << "Tapez un flottant " << endl;
    cin >> x;
    cout << "Le carre de " << x << "est : " << x*x << endl << "Le racine carre de " << x << " est : " << sqrt(x) << endl;
    cout << "Le perimetre de  rayon " << x << " est : " << ((x*2)*3.14) << endl;
    cout << "L'air du cercle " <<  x << " est : " << 3.14*x*x;
    
}
#include <iostream>
using namespace std;
int main(){
    int n,min,max,sum{0},i{0};
    while(n!=0){
        cout << "Ajouter un entier de votre suite un entier " << endl;
        cout << "Tapez 0 pur quitter " << endl;
        cin >> n;
        if (i==0)
        {
            min = max = n;
        }
        sum += n;
        if(n>max && n!=0){
            max = n;
        }
        if(n<min && n!=0){
            min = n;
        }
        i++;
    }

    
    cout << "Min : " << min << endl;
    cout << "Max : " << max << endl;
    cout << "AVG : " << sum/(i-1) << endl;
}
#include <iostream>
using namespace std;

int main() {

    int N;
    cin >> N;

    int *a = new int[N];

    for(int i=0; i<N; i++) {
        cout << "Inserisci valore " << i+1 << ": ";
        cin >> a[i];
    }

    for(int i=0; i<N; i++) {
        cout << "Inserisci valore " << i+1 << ": ";
        cin >> a[i];
    }

    return 0;
}
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int DIM_ARRAY = 5;

int main() {

    double v[DIM_ARRAY] = {
        1.0,
        2.0,
        3.333333333,
        7.0/3.0,
        0.0
    };

    ofstream f_bin("data.dat"), f_txt("dati.txt");

    for(int i=0; i<DIM_ARRAY; i++)
        f_txt << v[i] << " ";
    f_txt.close();

    f_bin.write(
        reinterpret_cast<char *>(v),
        sizeof(double) * DIM_ARRAY
    );
    f_bin.close();

    ifstream if_bin("data.dat"), if_txt("dati.txt");
    double d;
    for(int i=0; i<DIM_ARRAY; i++) {
        if_txt >> d;
        cout << d << " ";
    }
    cout << endl;

    double v2[DIM_ARRAY];
    if_bin.read(reinterpret_cast<char *>(v2), sizeof(v2));

    cout << setprecision(9);

    cout << "Leggendo dall'array v2:" << endl;
    for(int i=0; i<DIM_ARRAY; i++)
        cout << v2[i] << " ";
    cout << endl;

    return 0;
}

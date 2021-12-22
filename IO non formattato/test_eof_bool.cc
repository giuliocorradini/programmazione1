#include <iostream>
using namespace std;

int main() {
    int a;

    cin >> a;

    cout << "stream status: " << static_cast<bool>(cin)
         << ", eof: "    << cin.eof()
         << ", good: "   << cin.good()
         << ", bad:"     << cin.bad()
         << ", fail: "   << cin.fail()
         << endl;
    return 0;
}
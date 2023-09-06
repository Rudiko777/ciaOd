#include <iostream>
#include "bitset"
#include "vector"
#include "string"
#include "fstream"
#include "ostream"
#include "ctime"
#include "chrono"


using namespace std;

void ex1(){
    unsigned short int x = 0xF247;
    unsigned short int maska = 0x0828;
    x = x | maska;
    cout << endl << bitset<32>(x);
}

void kex1(){
    unsigned short int x = 0xF7D7;
    unsigned short int mask = 0x0828;

    cout << "Было:" << bitset<16>(x) << endl;

    x = x | mask;
    cout << "Стало:" << bitset<16>(x);
}

void ex2(){
    unsigned short int x;
    cin >> x;
    unsigned short int maska = 0x0FFF;
    cout << bitset<16>(x) << endl;
    x = x & maska;
    cout << bitset<16>(x) << endl;;
}

void kex2(){
    unsigned short int x;
    cin >> x; //65535
    unsigned short int mask = 0xFFF0;

    cout << "Было:" << bitset<16>(x) << endl;

    x = x & mask;
    cout << "Стало:" << bitset<16>(x);
}

void ex3(){
    unsigned short int x;
    cin >> x;
    unsigned short int value = x << 5;
    cout << bitset<32>(value);
    cout << "\n" << value;
}

void kex3(){
    unsigned short int x;
    cin >> x; //65535
    unsigned short int value = x << 7;

    cout << "Было:" << x << endl;
    cout << "Стало:" << value;
}

void ex4(){
    unsigned short int x;
    cin >> x;
    unsigned short int value = x >> 5;

    cout << bitset<32>(value);
    cout << "\n" << value;
}

void kex4(){
    unsigned short int x;
    cin >> x; //65535
    unsigned short int value = x >> 7;

    cout << "Было:" << x << endl;
    cout << "Стало:" << value;
}

void ex5(){
    unsigned short int x;
    cin >> x;
    unsigned short maska = 1 << 15;
    unsigned int n;
    cin >> n;
    maska = ~(maska>>(16-n-1));
    cout << bitset<16>(maska) << endl;
    cout << bitset<16>(maska&x);
}

void kex5(){
    unsigned short mask = 1 << 15;
    unsigned short x;
    cin >> x;

    int n;
    cin >> n;
    mask = mask >> (15 - n);

    cout << "Было:" << bitset<16>(x) << endl;

    x = x | mask;
    cout << "Стало:" << bitset<16>(x);

}

void sortBitArray(){
    int n;
    cin >> n;
    vector<unsigned int> array;
    for (int i = 0; i < array.size(); i++){
        unsigned char value;
        cin >> value;
        array.push_back(value);
    }
    unsigned char values = 0;
    for (unsigned int i: array){
        values += (1<<i);
    }

    int index = 0;
    for (int i = 0; i < 8; i++){
        if (values%2 == 1){
            array[index] = i;
            index++;
        }
        values/= 2;
    }

    for (unsigned int i: array){
        cout << i << "\n";
    }
}

void sortBitArrayLarge(){
    int n;
    cin >> n;
    vector<unsigned int> values;
    for (int i = 0; i < n; i++){
        unsigned int value;
        cin >> value;
        values.push_back(value);
    }

    unsigned char zero = 0;
    vector<unsigned char> array = vector<unsigned char>(8, zero);
    for (unsigned int i: values){
        int index = i / 8;
        array[index] += 1 << (i % 8);
    }
    int index = 0;
    for (int j = 0; j < array.size(); j++){
        for (int i = 0; i < 8; i++){
            if (array[j]%2 == 1){
                values[index] = j*8+i;
                index++;
            }
            array[j]/=2;
        }
    }

    for (unsigned int i: values){
        cout << i << "\n";
    }
}

void failSort(){
    string str;
    ifstream in; ofstream out;
    in.open("in.txt"); out.open("out.rtf");

    unsigned long long int zero = 0;
    vector<unsigned long long int> list = vector<unsigned long long int>(156250, zero);

    while(!in.eof()){
        in >> str;
        int index = stoi(str)/64;
        list[index] += 1 << (stoi(str) % 64);
    }

    int index = 0;
    for (int j = 0; j < list.size(); j++){
        for (int i = 0; i < 64; i++){
            if (list[j]%2 == 1){
                out << j*64+i << " ";
                index++;
            }
            list[j]/=2;
        }
    }

    in.close();
    out.close();
}

void failCreate(){
    srand(time(0));

    ofstream in;
    in.open("in.txt");
    vector<int> list(100000000);

    int x = 10000000;

    for(int i = 0; i < x; i++){
        list[i] = i;
    }

    for(int i = 0; i < x-1; i++){
        int x1,x2;
        x1 = 0 + rand() % x-1; x2 = 0 + rand() % x-1;

        int let;
        let = list[x1];
        list[x1] = list[x2];
        list[x2] = let;
    }

    for(int i = 0; i < x; i++){
        in << list[i] << " ";
    }

    in.close();
}

int main() {
    failSort();
    return 0;
}

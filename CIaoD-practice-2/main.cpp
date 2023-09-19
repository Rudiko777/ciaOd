#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Структура для хранения записи о регистрации малого предприятия
struct RegistrationRecord{
    int licenseNumber;
    string name;
    string founder;
};

// Функция для генерации случайных чисел в заданном диапазоне
int generateRandomNumber(int min, int max){
    return min + rand() % (max - min + 1);
}

// Функция для заполнения файла данными о регистрации малых предприятий
void fillFileWithData(const string& filename, int numRecords){
    ofstream outFile(filename, ios::binary);

    if (!outFile){
        cout << "Error with open the file" << endl;
        return;
    }

    srand(time(0));

    for(int i = 0; i < numRecords; ++i){
        RegistrationRecord record;

        // Генерация случайного номера лицензии
        record.licenseNumber = generateRandomNumber(1000, 9999);

        //Генерация случайного названия
        record.name = "Предприятие " + to_string(i + 1);

        //Генерация случайного учредителя
        record.founder = "Учредитель " + to_string(i + 1);

        outFile.write(reinterpret_cast<const char*>(&record), sizeof(RegistrationRecord));
    }

    outFile.close();
    cout << "Successfully operation" << endl;
}

// Функция бинарного поиска записи по ключу
bool binarySearchRecord(const std::string& filename, int licenseNumber, RegistrationRecord& foundRecord) {
    ifstream file(filename, ios::binary);

    if(!file){
        cout << "Ошибка открытия файла" << endl;
        return false;
    }

    file.seekg(0, ios::end);
    int numRecords = file.tellg() / sizeof(RegistrationRecord);

    int first = 0;
    int last = numRecords - 1;

    while(first <= last){
        int mid = (first + last) / 2;
        file.seekg(mid * sizeof(RegistrationRecord));

        RegistrationRecord record;
        file.read(reinterpret_cast<char*>(&record), sizeof(record));

        if (record.licenseNumber == licenseNumber){
            foundRecord = record;
            file.close();
            return true;
        }
        else if (record.licenseNumber < licenseNumber){
            first = mid + 1;
        }
        else{
            last = mid - 1;
        }
    }

    file.close();
    return false;
}

int main() {
    string filename = "registration.bin";
    int numRecords = 10;

    fillFileWithData(filename, numRecords);

    int searchKey = generateRandomNumber(1000, 9999);
    RegistrationRecord foundRecord;

    if (binarySearchRecord(filename, searchKey, foundRecord)) {
        cout << "Record found:" << endl;
        cout << "Number license: " << foundRecord.licenseNumber << endl;
        cout << "Name: " << foundRecord.name << endl;
        cout << "Founder: " << foundRecord.founder << endl;
    } else {
        std::cout << "Record with key " << searchKey << " not found." << std::endl;
    }

    return 0;
}

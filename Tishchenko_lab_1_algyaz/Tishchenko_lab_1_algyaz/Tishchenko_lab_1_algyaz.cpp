#include <iostream>
#include <string>
#include <fstream>
#include <limits>

void Print() {
    std::cout << "-----------------------\n"
        << "1. Добавить трубу \n"
        << "2. Добавить КС \n"
        << "3. Просмотр всех объектов \n"
        << "4. Редактировать трубу \n"
        << "5. Редактировать КС \n"
        << "6. Сохранить в файл\n"
        << "7. Загрузить из файла\n"
        << "0. Выход \n"
        << "-----------------------\n"
        << "Выберите пункт меню: ";
}

void incorrectData() {
    std::cout << "Введите корректное значение: ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

struct Tube {
    std::string name;
    double length;
    double diameter;
    bool inRepair;
};

Tube createTube() {
    Tube tube;

    if (tube.name == "") {
        std::cout << "Введите название трубы: ";
        std::cin.ignore();
        std::getline(std::cin, tube.name);

        std::cout << "Введите длину трубы: ";
        while (!(std::cin >> tube.length) || tube.length <= 0) {
            incorrectData();

        }

        std::cout << "Введите диаметр трубы: ";
        while (!(std::cin >> tube.diameter) || tube.diameter <= 0) {
            incorrectData();
        }

        std::cout << "Труба в ремонте? (1 - да, 0 - нет): ";
        int repairStatus;
        while (!(std::cin >> repairStatus) || (repairStatus != 0 && repairStatus != 1)) {
            incorrectData();
        }
        tube.inRepair = (repairStatus == 1);

        return tube;
    } else {
        std::cout << "Труба уже создана. Данный объект может быть только один.\n";
    }
}

struct CompressionStation {
    std::string name;
    int numbersOfWorkshops;
    int workshopsAtWork;
    int efficiency;
};

CompressionStation createCompressionStation() {
    CompressionStation cs;
    if ((cs.name == "")) {
        std::cout << "Введите название станции: ";
        std::cin.ignore();
        std::getline(std::cin, cs.name);

        std::cout << "Введите количество цехов: ";
        while (!(std::cin >> cs.numbersOfWorkshops) || cs.numbersOfWorkshops <= 0) {
            incorrectData();
        }

        std::cout << "Введите количество работающих цехов: ";
        while (!(std::cin >> cs.workshopsAtWork) || cs.workshopsAtWork > cs.numbersOfWorkshops || cs.workshopsAtWork <= 0) {
            incorrectData();
        }

        std::cout << "Введите значение эффективности: ";
        while (!(std::cin >> cs.efficiency) || cs.efficiency <= 0) {
            incorrectData();
        }
        std::cout << "Компрессорная станция добавлена!\n";
        return cs;
    }
    else {
        std::cout << "Компрессорная станция уже создана. Данный объект может быть только один.\n";
    }
}

void displayTube(const Tube& tube) {
    if (!(tube.name == "")) {
    std::cout << "--- Труба --- \n"
        << "Название трубы: " << tube.name << "\n"
        << "Длина: " << tube.length << "\n"
        << "Диаметр: " << tube.diameter << "\n"
        << "В ремонте: " << (tube.inRepair ? "Да" : "Нет") << "\n";
    }
    else {
        std::cout << "Труба не создана.\n";
    }
}

void displayCompressionStation(const CompressionStation& cs) {
    if (!(cs.name == "")) {
        std::cout << "--- Компрессорная станция --- \n"
            << "Название станции: " << cs.name << "\n"
            << "Количество цехов: " << cs.numbersOfWorkshops << "\n"
            << "Цехов в работе: " << cs.workshopsAtWork << "\n"
            << "Эффективность: " << cs.efficiency << "\n";
    }
    else {
        std::cout << "Компрессорная станция не создана.\n";
    }
}

void editTube(Tube& tube) {
    if (tube.name == "") {
        std::cout << "Труба не создана. Сначала создайте трубу.\n";
    }
    else {

        std::string newName;
        double newLength;
        double newDiameter;
        int newRepairStatus;

        std::cout << "Название: " << tube.name << ". Введите новое имя или нажмите Enter, чтобы оставить текущее: ";
        std::cin.ignore();
        std::getline(std::cin, newName);
        if (!newName.empty()) tube.name = newName;

        std::cout << "Длина: " << tube.length << ". Введите новую длину или 0, чтобы оставить текущую: ";
        while (!(std::cin >> newLength)) {
            incorrectData();
        }
        if (newLength != 0) tube.length = newLength;

        std::cout << "Диаметр: " << tube.diameter << ". Введите новый диаметр или 0, чтобы оставить текущий: ";
        while (!(std::cin >> newDiameter)) {
            incorrectData();
        }
        if (newDiameter != 0) tube.diameter = newDiameter;

        std::cout << "В ремонте (1 - да, 0 - нет): ";
        while (!(std::cin >> newRepairStatus) || (newRepairStatus != 0 && newRepairStatus != 1)) {
            incorrectData();
        }
        tube.inRepair = (newRepairStatus == 1);
    }
}

void editCompressionStation(CompressionStation& cs) {
    if (cs.name == "") {
        std::cout << "Компрессорная станция не создана. Сначала создайте КС.\n";
        return;
    }
    else {

        std::string newName;
        int newNumbersOfWorkshops;
        int newWorkshopsAtWork;
        int newEfficiency;

        std::cout << "Название станции: " << cs.name << ". Введите новое имя или нажмите Enter, чтобы оставить текущее: ";
        std::cin.ignore();
        std::getline(std::cin, newName);
        if (!newName.empty()) cs.name = newName;

        std::cout << "Количество цехов: " << cs.numbersOfWorkshops << ". Введите новое значение или 0, чтобы оставить текущее: ";
        while (!(std::cin >> newNumbersOfWorkshops)) {
            incorrectData();
        }
        if (newNumbersOfWorkshops != 0) cs.numbersOfWorkshops = newNumbersOfWorkshops;

        std::cout << "Цехов в работе: " << cs.workshopsAtWork << ". Введите новое значение или 0, чтобы оставить текущее: ";
        while (!(std::cin >> newWorkshopsAtWork) || (newWorkshopsAtWork > cs.numbersOfWorkshops)) {
            incorrectData();
        }
        if (newWorkshopsAtWork != 0) cs.workshopsAtWork = newWorkshopsAtWork;

        std::cout << "Эффективность: " << cs.efficiency << ". Введите новое значение или 0, чтобы оставить текущее: ";
        while (!(std::cin >> newEfficiency)) {
            incorrectData();
        }
        if (newEfficiency != 0) cs.efficiency = newEfficiency;
    }
}

void saveToFile(const Tube& tube, const CompressionStation& cs) {
    std::ofstream file("smeta.txt");
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для записи." << std::endl;
        return;
    }

    if (!(tube.name == "")) {
        file << "tube \n";
        file << tube.name << "\n";
        file << tube.length << "\n";
        file <<tube.diameter << "\n";
        file << tube.inRepair << "\n";
    }

    if (!(cs.name == "")) {
        file << "cs \n";
        file << cs.name << "\n";
        file << cs.numbersOfWorkshops << "\n";
        file << cs.workshopsAtWork << "\n";
        file << cs.efficiency << "\n";
    }
    file.close();
    std::cout << "Данные сохранены\n";
}

Tube readingTube(std::ifstream& fin)
{
    Tube tube;
    fin >> std::ws;
    std::getline(fin, tube.name);
    fin >> tube.length;
    fin >> tube.diameter;
    fin >> tube.inRepair;
    return tube;
}

CompressionStation readingCS(std::ifstream& fin)
{
    CompressionStation cs;
    fin >> std::ws;
    std::getline(fin, cs.name);
    fin >> cs.numbersOfWorkshops;
    fin >> cs.workshopsAtWork;
    fin >> cs.efficiency;
    return cs;
}

void loadFromFile(Tube& tube, CompressionStation& cs) {
    std::ifstream fin("smeta.txt", std::ios::in);
    if (fin.is_open()) {
        std::string marker;
        while (fin >> marker) {
            fin.ignore(); 
            if (marker == "tube") {
                tube = readingTube(fin);
                std::cout << "Труба загружена!\n";
            }
            else if (marker == "cs") {
                cs = readingCS(fin);
                std::cout << "КС загружена!\n";
            }
        }
        fin.close();
    }
    else {
        std::cout << "Ошибка открытия файла!" << "\n";
    }
}

int main() {
    std::setlocale(LC_ALL, "Russian");
    Tube tube;
    CompressionStation cs;
    int choice;

    while (true) {
        Print();
        while (!(std::cin >> choice)) {
            incorrectData();
        }

        switch (choice) {
        case 1:
            tube = createTube();
            break;

        case 2:
        cs = createCompressionStation();
            break;

        case 3:
            displayTube(tube);
            displayCompressionStation(cs);
            break;

        case 4:
            editTube(tube);
            break;

        case 5:
            editCompressionStation(cs);
            break;

        case 6: 
            saveToFile(tube, cs);
            break;

        case 7:{
            loadFromFile(tube, cs);
            break;
        }
        case 0:
            std::cout << "Выход из программы.\n";
            return 0;

        default:
            std::cout << "Неверный пункт меню.\n";
            break;
        }
        }
    }


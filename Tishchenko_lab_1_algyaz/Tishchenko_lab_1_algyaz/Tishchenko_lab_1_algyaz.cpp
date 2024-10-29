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

void check() {
    std::cout << "Введите корректное значение: ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

struct Tube {
    std::string name;
    double length;
    double diameter;
    bool inRepair;
    bool presence = false;
};

Tube createTube() {
    Tube tube;
    tube.presence = true;

    std::cout << "Введите название трубы: ";
    std::cin.ignore();
    std::getline(std::cin, tube.name);

    std::cout << "Введите длину трубы: ";
    while (!(std::cin >> tube.length) || tube.length <= 0) {
        check();
    }

    std::cout << "Введите диаметр трубы: ";
    while (!(std::cin >> tube.diameter) || tube.diameter <= 0) {
        check();
    }

    std::cout << "Труба в ремонте? (1 - да, 0 - нет): ";
    int repairStatus;
    while (!(std::cin >> repairStatus) || (repairStatus != 0 && repairStatus != 1)) {
        check();
    }
    tube.inRepair = (repairStatus == 1);

    return tube;
}

struct CompressionStation {
    std::string name;
    int numbersOfWorkshops;
    int workshopsAtWork;
    int efficiency;
    bool presence = false;
};

CompressionStation createCompressionStation() {
    CompressionStation cs;
    cs.presence = true;

    std::cout << "Введите название станции: ";
    std::cin.ignore();
    std::getline(std::cin, cs.name);

    std::cout << "Введите количество цехов: ";
    while (!(std::cin >> cs.numbersOfWorkshops) || cs.numbersOfWorkshops <= 0) {
        check();
    }

    std::cout << "Введите количество работающих цехов: ";
    while (!(std::cin >> cs.workshopsAtWork) || cs.workshopsAtWork > cs.numbersOfWorkshops || cs.workshopsAtWork <= 0) {
        check();
    }

    std::cout << "Введите значение эффективности: ";
    while (!(std::cin >> cs.efficiency) || cs.efficiency <= 0) {
        check();
    }

    return cs;
}

void displayTube(const Tube& tube) {
    std::cout << "--- Труба --- \n"
        << "Название трубы: " << tube.name << "\n"
        << "Длина: " << tube.length << "\n"
        << "Диаметр: " << tube.diameter << "\n"
        << "В ремонте: " << (tube.inRepair ? "Да" : "Нет") << "\n";
}

void displayCompressionStation(const CompressionStation& cs) {
    std::cout << "--- Компрессорная станция --- \n"
        << "Название станции: " << cs.name << "\n"
        << "Количество цехов: " << cs.numbersOfWorkshops << "\n"
        << "Цехов в работе: " << cs.workshopsAtWork << "\n"
        << "Эффективность: " << cs.efficiency << "\n";
}

void editTube(Tube& tube) {
    if (!tube.presence) {
        std::cout << "Труба не создана. Сначала создайте трубу.\n";
        return;
    }

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
        check();
    }
    if (newLength != 0) tube.length = newLength;

    std::cout << "Диаметр: " << tube.diameter << ". Введите новый диаметр или 0, чтобы оставить текущий: ";
    while (!(std::cin >> newDiameter)) {
        check();
    }
    if (newDiameter != 0) tube.diameter = newDiameter;

    std::cout << "В ремонте (1 - да, 0 - нет): ";
    while (!(std::cin >> newRepairStatus) || (newRepairStatus != 0 && newRepairStatus != 1)) {
        check();
    }
    tube.inRepair = (newRepairStatus == 1);
}

void editCompressionStation(CompressionStation& cs) {
    if (!cs.presence) {
        std::cout << "Компрессорная станция не создана. Сначала создайте КС.\n";
        return;
    }

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
        check();
    }
    if (newNumbersOfWorkshops != 0) cs.numbersOfWorkshops = newNumbersOfWorkshops;

    std::cout << "Цехов в работе: " << cs.workshopsAtWork << ". Введите новое значение или 0, чтобы оставить текущее: ";
    while (!(std::cin >> newWorkshopsAtWork) || (newWorkshopsAtWork > cs.numbersOfWorkshops)) {
        check();
    }
    if (newWorkshopsAtWork != 0) cs.workshopsAtWork = newWorkshopsAtWork;

    std::cout << "Эффективность: " << cs.efficiency << ". Введите новое значение или 0, чтобы оставить текущее: ";
    while (!(std::cin >> newEfficiency)) {
        check();
    }
    if (newEfficiency != 0) cs.efficiency = newEfficiency;
}

void loadFromFile(Tube& tube, CompressionStation& cs) {
    std::ifstream file("smeta.txt");
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для чтения." << std::endl;
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line == "--- Труба ---") {
            tube.presence = true;
            std::getline(file, line);
            tube.name = line.substr(line.find(":") + 2);

            std::getline(file, line);
            tube.length = std::stod(line.substr(line.find(":") + 2));

            std::getline(file, line);
            tube.diameter = std::stod(line.substr(line.find(":") + 2));

            std::getline(file, line);
            tube.inRepair = (line.substr(line.find(":") + 2) == "Да");
        }
        else if (line == "--- Компрессорная станция ---") {
            cs.presence = true;
            std::getline(file, line);
            cs.name = line.substr(line.find(":") + 2);

            std::getline(file, line);
            cs.numbersOfWorkshops = std::stoi(line.substr(line.find(":") + 2));

            std::getline(file, line);
            cs.workshopsAtWork = std::stoi(line.substr(line.find(":") + 2));

            std::getline(file, line);
            cs.efficiency = std::stoi(line.substr(line.find(":") + 2));
        }
    }
    file.close();
    std::cout << "Данные загружены из файла\n";
}

int main() {
    std::setlocale(LC_ALL, "Russian");
    Tube tube;
    CompressionStation cs;
    int choice;

    while (true) {
        Print();
        while (!(std::cin >> choice)) {
            check();
        }

        switch (choice) {
        case 1:
            if (!tube.presence) {
                tube = createTube();
                std::cout << "Труба добавлена!\n";
            }
            else {
                std::cout << "Труба уже создана. Данный объект может быть только один.\n";
            }
            break;

        case 2:
            if (!cs.presence) {
                cs = createCompressionStation();
                std::cout << "Компрессорная станция добавлена!\n";
            }
            else {
                std::cout << "Компрессорная станция уже создана. Данный объект может быть только один.\n";
            }
            break;

        case 3:
            if (tube.presence) displayTube(tube);
            else std::cout << "Труба не создана.\n";

            if (cs.presence) displayCompressionStation(cs);
            else std::cout << "Компрессорная станция не создана.\n";
            break;

        case 4:
            editTube(tube);
            break;

        case 5:
            editCompressionStation(cs);
            break;

        case 6: {
            std::ofstream file("smeta.txt");  
            if (!file.is_open()) {  
                std::cerr << "Ошибка: не удалось открыть файл для записи." << std::endl;
                return 1;
            }
            if (tube.presence) {
                file << "--- Труба --- \n";
                file << "Название трубы: " << tube.name << "\n";
                file << "Длина: " << tube.length << "\n";
                file << "Диаметр: " << tube.diameter << "\n";
                file << "В ремонте: " << (tube.inRepair ? "Да" : "Нет") << "\n";
            }
            else {
                file << "Труба не создана.\n";
            }
            if (cs.presence) {
                file << "--- Компрессорная станция --- \n";
                file << "Название станции: " << cs.name << "\n";
                file << "Количество цехов: " << cs.numbersOfWorkshops << "\n";
                file << "Цехов в работе: " << cs.workshopsAtWork << "\n";
                file << "Эффективность: " << cs.efficiency << "\n";
            }
            else {
                file << "Компрессорная станция не создана.\n";
            }
            file.close();
            std::cout << "Данные сохранены\n";
        }
              break;

        case 7:
            loadFromFile(tube, cs);
            break;
        
        case 0:
            std::cout << "Выход из программы.\n";
            return 0;

        default:
            std::cout << "Неверный пункт меню.\n";
            break;
        }
    }
}

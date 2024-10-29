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
    while (!(std::cin >> tube.length)) {
        check();
    }

    std::cout << "Введите диаметр трубы: ";
    while (!(std::cin >> tube.diameter)) {
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
    while (!(std::cin >> cs.numbersOfWorkshops)) {
        check();
    }

    std::cout << "Введите количество работающих цехов: ";
    while (!(std::cin >> cs.workshopsAtWork) || cs.workshopsAtWork > cs.numbersOfWorkshops) {
        check();
    }

    std::cout << "Введите значение эффективности: ";
    while (!(std::cin >> cs.efficiency)) {
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
        std::cout << "Компрессорная станция не создана. Сначала создайте Компрессорную станцию.\n";
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

        case 0:
            std::cout << "Выход из программы.\n";
            return 0;

        default:
            std::cout << "Неверный пункт меню.\n";
            break;
        }
    }
}

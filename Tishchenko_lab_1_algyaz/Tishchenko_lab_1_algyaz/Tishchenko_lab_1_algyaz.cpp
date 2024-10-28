#include <iostream>
#include <string>
#include <fstream>

// Вывод основного меню
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
        << "0. -----------------------\n"
        << "Выберите пункт меню: ";
}

void check() {
    std::cout << "Введите корректное значение ";
    std::cin.clear(); // Сброс состояния потока
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Структура для хранения данных о трубе
struct Tube {
    std::string name;
    double length;
    double diameter;
    bool inRepair;
    bool presence = false;  // Поле для проверки, была ли создана труба
};

// Функция для создания новой трубы
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
    std::cin >> repairStatus;
    tube.inRepair = (repairStatus == 1);
    while (!(std::cin >> repairStatus)) {
        check();
    }

    return tube;
}

// Структура для хранения данных о компрессорной станции
struct CompressionStation {
    std::string name;
    int numbersOfWorkshops;
    int workshopsAtWork;
    int efficiency;
    bool presence = false;
};

// Функция для создания новой компрессорной станции
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
    while (!(std::cin >> cs.workshopsAtWork)) {
        check();
    }

    if (cs.workshopsAtWork > cs.numbersOfWorkshops) {
        std::cout << "Количество работающих цехов не должно превышать общее количество цехов.\n";
        cs.presence = false;
        } else {
        std::cout << "Введите значение эффективности: ";
        while (!(std::cin >> cs.efficiency)) {
            check();
        }
    }
    return cs;
}

// Функция для отображения информации о трубе
void displayTube(const Tube& tube) {
    std::cout << "--- Труба --- \n"
        << "Название трубы: " << tube.name << "\n"
        << "Длина: " << tube.length << "\n"
        << "Диаметр: " << tube.diameter << "\n"
        << "В ремонте: " << (tube.inRepair ? "Да" : "Нет") << "\n";
}

// Функция для отображения информации о компрессорной станции
void displayCompressionStation(const CompressionStation& cs) {
    std::cout << "--- Компрессорная станция --- \n"
        << "Название станции: " << cs.name << "\n"
        << "Количество цехов: " << cs.numbersOfWorkshops << "\n"
        << "Цехов в работе: " << cs.workshopsAtWork << "\n"
        << "Эффективность: " << cs.efficiency << "\n";
}

int main() {
    std::setlocale(LC_ALL, "Russian");

    Tube tube;                  // Объект для хранения трубы
    CompressionStation cs;      // Объект для хранения компрессорной станции
    int choice;

    while (true) {
        // Вывод меню
        Print();
        while (!(std::cin >> choice)) { 
            check();
        }

        switch (choice) {
        case 1:
            if (!tube.presence) {  // Проверяем, создана ли труба
                tube = createTube();
                std::cout << "Труба добавлена!\n";
            }
            else {
                std::cout << "Труба уже создана. Данный объект может быть только один.\n";
            }
            break;

        case 2:
            if (!cs.presence) {  // Проверяем, создана ли компрессорная станция
                cs = createCompressionStation();
                if (cs.presence) {
                    std::cout << "Компрессорная станция добавлена!\n";
                }
            }
            else {
                std::cout << "Компрессорная станция уже создана. Данный объект может быть только один.\n";
            }
            break;

        case 3:
            if (tube.presence) {
                displayTube(tube);  // Выводим информацию о трубе
            }
            else {
                std::cout << "Труба не создана.\n";
            }
            if (cs.presence) {
                displayCompressionStation(cs);  // Выводим информацию о компрессорной станции
            }
            else {
                std::cout << "Компрессорная станция не создана.\n";
            }
            break;

        case 6: {
            std::ofstream file("smeta.txt");  // Создание файла
            if (!file.is_open()) {  // Проверка на возможность открытия фала
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

        case 0:
            std::cout << "Выход из программы.\n";
            return 0;
        }
    }
}

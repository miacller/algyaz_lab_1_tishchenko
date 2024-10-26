#include <iostream>
#include <string>

// Вывод основного меню
void Print() {
    std::cout << "-----------------------\n"
        << "1. Добавить трубу \n"
        << "2. Добавить КС \n"
        << "3. Просмотр всех объектов \n"
        << "4. Редактировать трубу \n"
        << "5. Редактировать КС \n"
        << "6. Сохранить \n"
        << "7. Загрузить \n"
        << "0. Выход \n"
        << "Выберите пункт меню: ";
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
    std::cin.ignore();  // Игнорируем остаток предыдущего ввода
    std::getline(std::cin, tube.name);

    std::cout << "Введите длину трубы: ";
    std::cin >> tube.length;

    std::cout << "Введите диаметр трубы: ";
    std::cin >> tube.diameter;

    std::cout << "Труба в ремонте? (1 - да, 0 - нет): ";
    int repairStatus;
    std::cin >> repairStatus;
    tube.inRepair = (repairStatus == 1);

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
    std::cin.ignore();  // Игнорируем остаток предыдущего ввода
    std::getline(std::cin, cs.name);

    std::cout << "Введите количество цехов: ";
    std::cin >> cs.numbersOfWorkshops;

    std::cout << "Введите количество работающих цехов: ";
    std::cin >> cs.workshopsAtWork;

    if (cs.workshopsAtWork > cs.numbersOfWorkshops) {
        std::cout << "Количество работающих цехов не должно превышать общее количество цехов.\n";
        cs.presence = false;  // Устанавливаем наличие на false, если данные некорректны
    }
    else {
        std::cout << "Введите значение эффективности: ";
        std::cin >> cs.efficiency;
    }
    return cs;
}

// Функция для отображения информации о трубе
void displayTube(const Tube& tube) {
    std::cout << "Название трубы: " << tube.name << "\n"
        << "Длина: " << tube.length << "\n"
        << "Диаметр: " << tube.diameter << "\n"
        << "В ремонте: " << (tube.inRepair ? "Да" : "Нет") << "\n";
}

// Функция для отображения информации о компрессорной станции
void displayCompressionStation(const CompressionStation& cs) {
    std::cout << "Название станции: " << cs.name << "\n"
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
        std::cin >> choice;

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

        case 0:
            std::cout << "Выход из программы.\n";
            return 0;

        default:
            std::cout << "Введите корректное значение.\n";
            break;
        }
    }
}

C++98: Первый официальный стандарт
Фундамент, на котором всё держится. До этого момента язык жил «по понятиям» (книге Страуструпа).
 * STL (Standard Template Library): Появились контейнеры (vector, list), алгоритмы и итераторы.
 * RTI (Run-Time Type Information): dynamic_cast и typeid.
 * Шаблоны: Основа для метапрограммирования.
 * Пространства имен: Появление std.
 * Exceptions: (#include <exception>).
C++03: «Техническое исправление»
Минорное обновление. Исправили баги C++98, добавили лишь одно заметное новшество — Value Initialization. По сути, это патч, а не полноценная версия.
C++11: Революция (Modern C++)
Самое масштабное обновление, которое буквально спасло язык от забвения.
 * Move-семантика: &&, std::move, std::forward — заставили код летать за счет исключения лишних копирований.
 * Auto и decltype (хвостовой тип ->): Компилятор наконец-то начал помогать с типами.
 * Лямбда-выражения: Функции «на лету».
 * Умные указатели: unique_ptr, shared_ptr. Прощай, ручной delete (почти).
 * Многопоточность: Встроенная библиотека <thread>, мьютексы и атомарные типы.
 * nullptr: Настоящий нулевой указатель вместо макроса NULL.
 * Uniform Initialization (Универсальная инициализация {}).
 * Инициализация полей при объявлении (NSDMI) в теле класса.
 * = default и = delete для конструкторов / деструкторов.
 * Delegating constructors: Позволяет одному конструктору вызывать другой в том же классе.
 * Override / Final: Защита от ошибок при наследовании (чтобы точно переопределить виртуальную функцию).
 * static_assert с сообщением: Проверка условия на этапе компиляции.
 * (typename) std::enable_if и (SFINAE) (#include <type_traits>): «выключает» определенные перегрузки функций или специализации шаблонов.
 * std::exception_ptr.
 * noexcept: для методов класса.
 * Range-based for loop.
 * ref-qualifier for methods.
 * alignas().
 * alias templates; опускание typename ...::type.
 * constexpr functions: Только return.
C++14: Работа над ошибками
Шлифовка идей C++11.
 * Generic lambdas: auto в аргументах лямбд.
 * ReturnType deduction: [auto & decltype(auto)] Компилятор сам понимает, что возвращает функция.
 * Binary literals: Запись чисел в духе 0b101010.
 * std::make_unique: Наконец-то симметрия с make_shared.
 * обнова constexpr functions: Циклы, ветвления, локальные переменные.
C++17: Удобство и синтаксический сахар
Сделал код чище и приятнее.
 * structured Bindings: Распаковка кортежей и структур: auto [x, y] = point;.
 * std::filesystem: Стандартная работа с папками и файлами.
 * std::optional, std::variant, std::any: Безопасные способы хранения «чего-то или ничего».
 * if constexpr: Метапрограммирование стало выглядеть как обычный код.
 * string_view: Легковесная ссылка на строку без копирования.
 * inline variables: Позволило объявлять переменные в хедер-файлах без ошибок линковки.
 * static_assert без сообщения.
 * CTAD: constructor template argument deduction.
 * Deduction guides: ручные правила вывода CTAD.
 * Fold expressions: (args + ...) and others.
 * template <auto>: для non-type template параметров.
 * if & switch with initializers: if (init; condition).
C++20: «Большая четверка»
Второе по значимости обновление после C++11. Язык изменился фундаментально.
 * Concepts: Человеческие ограничения для шаблонов (больше никаких страшных ошибок в 100 строк).
 * Modules: Попытка заменить древние #include и ускорить компиляцию.
 * Coroutines: Поддержка асинхронности на уровне языка.
 * Ranges: Возможность писать std::sort(vec) вместо std::sort(vec.begin(), vec.end()) и строить конвейеры обработки данных.
 * Оператор <=>: «Космический корабль» для трехстороннего сравнения.
 * Designated Initializers (Назначенные инициализаторы): из Си, инициализация полей по именам: Window w{.width = 800};.
 * Agregate types: Вновь пересмотрено определение.
 * Agregate CTAD: для агрегатов.
 * Alias CTAD: для using псевдонимов.
 * Abbreviated function templates: auto в аргументах обычных ф-ий.
 * consteval functions.
 * constinit variables.
C++23: Косметический ремонт
Небольшое, но полезное обновление.
 * std::expected: Обработка ошибок в функциональном стиле (альтернатива исключениям).
 * std::print / std::println: Наконец-то современный и быстрый вывод текста (прощай, printf и тяжелый cout).
 * Многомерный operator[]: Теперь можно писать matrix[x, y].
 * if consteval: Явное разделение кода для компиляции и выполнения.
 * Explicit object member function (this auto && self).
C++26:
 * Reflection.
 * Contracts.
 * consteval named blocks.
Ждём C++29.

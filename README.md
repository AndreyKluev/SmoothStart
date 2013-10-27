SmoothStart
===========

Плавный запуск мощной нагрузки на ATtiny13

Проект разрабатывается для интеграции в самодельный сверлильный станок, сделанный из микроскопа.


Основные функции:

1. Плавное включение/выключение двигателя
2. Плавное включение/выключение подсветки


Все управление будет реализовано одной кнопкой, по следующему алгоритму

1. Короткое нажатие кнопки - включение/отключение подсветки
2. Среднее нажатие кнопки - включение/отключение двигателя
3. Длинное нажатие кнопки - отключение двигателя и подсветки


Задачи

1. <del>Разработать принципиальную схему устройства</del> - Выполнено
2. <del>Разработать и изготовить печатную плату устройства, с учетом особенностей предполагаемого места установки</del> - Выполнено
3. Разработать прошивку для микроконтроллера


Цели проекта:

1. Изучение работы ШИМ, таймеров и прерываний МК
2. Получение опыта комплексной разработки (от постановки задачи до начала использования)
3. Разработка устройства для дальнейшего применения

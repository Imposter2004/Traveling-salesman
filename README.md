# Задача коммивояжера
## Постановка задачи
Реализовать граф и решить для него задачу Комивояжера методом ветвей и границ.
Для решения данной задачи необходимо:
- Создать класс Graph.
- Решить для данного графа задачу Комивояжера.
- Визуализировать граф.
- Визуализировать решение задачи Комивояжера.
- Реализовать интерфейс в Qt Creator

## Анализ задачи
- Базовый класс ```Graph``` взят из лабораторной работы графы. Граф хранится в виде массива матрицы смежности. 
- Для решения задачи комивояжера использован метод ветвей и границ, который находит локально-оптимальное решение для данного графа. Но при решении внесены правки - такие как установка стартовой вершины. Для этого вершна принудительно добавляется в список, который представляет из себя маршрут по вершинам. Если задачу невозможно решить для данного графа, то есть одна или несколько вершин не достижимы, то решения не будет и высветится подскаска, что необходимо отредактировать граф.
- Для визуализации использована библиотека ```QPainter```.Вершины графа отрисовываются по функции вставки эллипса по кругу, от вершины к вершине проходит ребро под необходимым вычисленным углом. Также по середине ребра располагается его вес, а на вершинах порядковый номер вершины.
- Для визуализации решения задачи Комивояжера отрисовывать граф и на экран выводить кратчайший путь и его длину. Сам путь на графе отображается красным цветом. 
 

## Тестирование
Для тестирования программы необходимо выполнить тесты решения задачи и визуализации на разном количестве вершин, а также на разных типах ребрах.
Тестирование программы представленно в видео на YouTube: 
## Ссылка на 1 часть творческой работы
https://github.com/KHox/QT-Post
## Контактные данные
Аксёнов Давид:davidka.aksenov.2004@mail.ru

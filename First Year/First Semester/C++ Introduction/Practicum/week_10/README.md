[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/0PNRvkZ0)
# Търсене с връщане назад (Backtracking) - 03.12.2024

## Задача 1

Да се напише *рекурсивна* функция, която по подаден низ проверява дали той е палиндром.

## Задача 2

Да се напише функция, която по подаден масив извежда всички подмножества на множеството от елементите на масива. Приемаме, че в масива няма повторения.

## Задача 3

Дадена е булева матрица MxN и начални координати (0,0). `0` в матрицата представлява проходима клетка, а `1` - непроходима. Да се напише функция, която да проверява дали съществува път от началната точка до точката в долния десен ъгъл на матрицата. Приемаме, че тези две точки винаги ще са проходими.

*Бонус*: Да се промени функцията така, че матрицата да остава непроменена след изпълнението на функцията.

## Задача 4

Дадена е булева матрица MxN. От конзолата се въвеждат координати на начална и крайна точка. Клетките, маркирани с `0`, се считат за проходими, а тези, маркирани с `1` - за непроходими.

- Да се напише функция, която връща дължината на най-късия път от началната до крайната точка. 
- Да се напише функция, която връща броя на всички възможни пътища от началната до крайната точка.
- Да се напише функция, която извежда всички възможни пътища от началната до крайната точка.

*Забележка*: Позволено е началната/крайната клетка да са непроходими.

## Задача 5

Да се напише *рекурсивна* функция, която приема масив от цели положителни числа и целева сума и връща дали съществува подмножество от елементи на масива, чийто сбор е равен на целевата сума. **Да се изведат на конзолата всичките начини да бъде образувана тази сума.**

*Забележка*: Повторението на елементи **не** е позволено.

## Задача 6

Да се напише *рекурсивна* функция, която приема масив от цели положителни числа и целева сума и връща дали съществува мултимножество с елементи числата от масива, чийто сбор е равен на целевата сума.

*Забележка*: Повторението на елементи е **позволено**.

## Задача 7

Да се напише *рекурсивна* функция, която приема низ `s` и цяло неотрицателно число `n` и извежда всички низове с дължина `n`, които могат да се образуват от символите в низа `s`.

*Бонус*: Да се напише функция, която приема низ и цяло неотрицателно число `k` и извежда всички такива низове за всички естествени числа, по-малки или равни на `k`.

## Задача 8

Да се напише функция, която по подаден масив извежда всичките пермутации на елементите му.

*Забележка*: Пермутация на елементите на масив `arr` ще наричаме масивът, получен след прилагането на серия от транспозиции върху масива `arr`. Транспозиция на два елемента наричаме тяхната размяна.

Пример:

```
{1,2,3} -> { {1,2,3}, {1,3,2}, {2,1,3}, {2,3,1}, {3,2,1}, {3,1,2} }
```

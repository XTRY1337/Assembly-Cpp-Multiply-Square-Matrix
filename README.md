# Arquitetura de Computadores - Projeto em grupo

## Trabalho utilizando assembly - Trabalho número 8

Using SIMD instructions and pure assembly, make a function to multiply efficiently square
matrix of float values. The matrix can have any size multiple of 4 (4, 8, 12, 16, …). Compare
the results obtained with the C++ code. 

## Matrizes quadradas

Matrizes que têm o mesmo número de linhas e colunas
Tamanho das matrizes a serem utilizadas no projeto: apenas multiplos de 4, ou sejam, 4x4, 8x8, 12x12, etc..

Exemplo de multiplicaçao de duas matrizes quadradas:

-------      --------   -----------------------------
| 1  2 |     | 4  5 |   | (1x4 + 2x6) | (1x5 + 2x7) |
|      |  X  |      | = |                           |
| 3  4 |     | 6  7 |   | (3x4 + 4x6) | (3x5 + 4x7) |
-------      --------   -----------------------------


# Автоматический решатель Судоку

## Описание
Этот проект реализует графический интерфейс для ввода и автоматического решения игры Судоку с помощью библиотеки Swing в Java. 

## Код

```java
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


public class Sudoku extends JFrame {
    private JTextField[][] cells = new JTextField[9][9];
    private final int SIZE = 81;
    private int[] field = new int[SIZE];
    private int[] field_changeable = new int[SIZE];
    private JButton getDataButton;

    // Конструктор класса
    public Sudoku() {
        setTitle("Sudoku Auto Solver"); // Устанавливаем заголовок окна
        setSize(500, 550); // Устанавливаем размеры окна
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Завершаем программу при закрытии окна
        setLayout(new BorderLayout()); // Устанавливаем менеджер компоновки

        JPanel gridPanel = new JPanel(); // Создаем панель для сетки Судоку
        gridPanel.setLayout(new GridLayout(3, 3)); // Устанавливаем компоновку 3x3 для групп панелей

        // Создаем 3x3 панели для каждой группы ячеек
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                JPanel panel = new JPanel(); // Создаем новую панель для группы ячеек
                panel.setLayout(new GridLayout(3, 3)); // Устанавливаем компоновку 3x3 для ячеек
                panel.setBorder(BorderFactory.createLineBorder(Color.BLACK, 2)); // Устанавливаем границу для панели
                panel.setBackground(Color.YELLOW); // Устанавливаем цвет фона

                // Создаем ячейки Судоку и добавляем их на панель
                for (int k = 0; k < 3; k++) {
                    for (int l = 0; l < 3; l++) {
                        cells[i * 3 + k][j * 3 + l] = new JTextField(1); // Создаем текстовое поле для ячейки
                        cells[i * 3 + k][j * 3 + l].setHorizontalAlignment(JTextField.CENTER); // Устанавливаем выравнивание текста
                        cells[i * 3 + k][j * 3 + l].setFont(new Font("Arial", Font.BOLD, 22)); // Устанавливаем шрифт
                        panel.add(cells[i * 3 + k][j * 3 + l]); // Добавляем ячейку на панель
                        cells[i * 3 + k][j * 3 + l].setBackground(Color.LIGHT_GRAY); // Устанавливаем цвет фона
                        cells[i * 3 + k][j * 3 + l].setForeground(Color.RED);  // Устанавливаем цвет текста
                    }
                }
                gridPanel.add(panel); // Добавляем панель с ячейками в основную панель сетки
            }
        }


        getDataButton = new JButton("Solve"); // Создаем кнопку для запуска решения Судоку
        getDataButton.setFont(new Font("Arial", Font.BOLD, 22));
        getDataButton.setBackground(Color.DARK_GRAY); // Устанавливаем цвет фона
        getDataButton.setForeground(Color.GREEN); // Устанавливаем цвет текста
        getDataButton.addActionListener(new ActionListener() { // Добавляем обработку нажатия кнопки
            @Override
            public void actionPerformed(ActionEvent e) { // Метод, который выполняется при нажатии кнопки
                fillBoard(); // Заполняем массив значениями из текстовых полей
                solveSudoku(); // Запускаем процесс решения Судоку
            }
        });

        add(gridPanel, BorderLayout.CENTER); // Добавляем панель сетки в центр окна
        add(getDataButton, BorderLayout.SOUTH); // Добавляем кнопку в нижнюю часть окна
    }

    public void start() {
        setVisible(true); // Делаем окно видимым
    }

    private void updateFields() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cells[i][j].setText(String.valueOf(field[i * 9 + j])); // Устанавливаем текст ячейки
                if (field_changeable[i * 9 + j] != 1) {
                    cells[i][j].setForeground(Color.BLUE); // Устанавливаем цвет текста
                }
            }
        }
    }

    private void fillBoard() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                String text = cells[i][j].getText(); // Получаем текст из ячейки
                field[i * 9 + j] = text.isEmpty() ? 0 : Integer.parseInt(text); // Заполняем массив значениями
            }
        }
    }

    private boolean isValid(int row, int col) {
        int id = row * 9 + col; // Вычисляем индекс ячейки в массиве
        int current = field[id]; // Получаем текущее значение ячейки
        // Проверка на дубликаты в строке
        for (int i = 0; i < 9; i++) {
            if (field[row * 9 + i] == current && row * 9 + i != id) {
                return false; // Возвращаем false, если есть дубликаты
            }
        }
        // Проверка на дубликаты в столбце
        for (int j = 0; j < 9; j++) {
            if (field[j * 9 + col] == current && j * 9 + col != id) {
                return false; // Возвращаем false, если есть дубликаты
            }
        }
        // Проверка на дубликаты в 3x3 квадрате
        int temp_row = (row / 3) * 3 + 1;
        int temp_col = (col / 3) * 3 + 1;
        for (int a = temp_row - 1; a < temp_row + 2; a++) {
            for (int b = temp_col - 1; b < temp_col + 2; b++) {
                int temp_id = a * 9 + b; // Вычисляем индекс ячейки в массиве
                if (field[temp_id] == current && temp_id != id) {
                    return false; // Возвращаем false, если есть дубликаты
                }
            }
        }
        return true; // Возвращаем true, если все проверки пройдены
    }

    private void solveSudoku() throws WrongSudokuField, WrongSudokuNum {
        // Проверяем, корректно ли заполнение
        for (int i = 0; i < SIZE; i++) {
            if (!isValid(i / 9, i % 9) && field[i] != 0) {
                throw new WrongSudokuField("The field is filled in incorrectly."); // Исключение при неверном заполнении
            }
        }
        // Проверяем, корректны ли значения
        for (int j = 0; j < SIZE; j++) {
            if (field[j] > 9 || field[j] < 0) {
                throw new WrongSudokuNum("Invalid value in the field."); // Исключение при некорректном значении
            }
        }
        // Определяем изменяемые ячейки
        for (int k = 0; k < SIZE; k++) {
            if (field[k] != 0) {
                field_changeable[k] = 1; // Отмечаем, что ячейка неизменяема
            }
        }
        int cursor = 0; // Указатель на текущую ячейку
        String dir = "forward"; // Направление перебора
        while (cursor < SIZE) {
            if (field_changeable[cursor] != 0) {
                if (dir.equals("forward")) {
                    cursor++; // Переходим к следующей ячейке
                    continue; // Продолжаем цикл
                } else if (dir.equals("backward")) {
                    cursor--; // Возвращаемся к предыдущей ячейке
                    continue; // Продолжаем цикл
                }
            } else {
                if (field[cursor] == 9) {
                    field[cursor] = 0; // Сбрасываем значение
                    cursor--; // Возвращаемся к предыдущей ячейке
                    dir = "backward"; // Меняем направление на "назад"
                    continue; // Продолжаем цикл
                } else {
                    field[cursor]++; // Увеличиваем значение ячейки
                    if (isValid(cursor / 9, cursor % 9)) {
                        cursor++; // Переходим к следующей ячейке
                        dir = "forward"; // Меняем направление на "вперед"
                        continue; // Продолжаем цикл
                    }
                }
            }
        }
        updateFields(); // Обновляем текстовые поля в интерфейсе с решением
        getDataButton.setEnabled(false); // Отключаем кнопку 
        getDataButton.setText("Solved!"); // Изменяем текст кнопки
    }
}
```

## Объяснение кода

### Класс Sudoku
Этот класс наследуется от `JFrame`, что позволяет использовать его в качестве основного окна приложения.

#### Поля класса
- `private JTextField[][] cells`: Двумерный массив текстовых полей для ввода значений cудоку.
- `private final int SIZE`: Константа, равная 81 (9x9) — размер поля cудоку.
- `private int[] field`: Массив для хранения значений cудоку, введенных пользователем.
- `private int[] field_changeable`: Массив для отслеживания изменяемых ячеек.
- `private JButton getDataButton`: Поле для кнопки, чтобы к ней можно было обращаться из других методов.

#### Конструктор
В конструкторе устанавливается название окна, его размеры и поведение при закрытии. Далее создается панель, на которую добавляются текстовые поля, сгруппированные по 3x3, и кнопка "Solve" для запуска решения.

#### Методы класса
- **Метод `fillBoard()`**: Считывает значения из текстовых полей и заполняет массив `field` соответствующими значениями, заменяя пустые поля на 0.
- **Метод `updateFields()`**: Обновляет текстовые поля с решением судоку после его нахождения.
- **Метод `isValid(int row, int col)`**: Проверяет корректность расположения цифры, следуя правилам игры.
- **Метод `solveSudoku()`**: Реализует алгоритм решения судоку, проверяя корректность введенных данных и заполняя массив `field` с решением, если таковое возможно. Вызывает исключения `WrongSudokuNum` и `WrongSudokuField` при неверном заполнении поля.

### Исключения

**Исключение `WrongSudokuField`**: Исключение при неверном заполнении полей.

```java
public class WrongSudokuField extends RuntimeException {
    public WrongSudokuField(String message) {
        super(message);
    }
}
```

**Исключение `WrongSudokuNum`**: Исключение при некорректном значении в одном из полей.

```java
public class WrongSudokuNum extends RuntimeException {
    public WrongSudokuNum(String message) {
        super(message);
    }
}
```

### Запуск приложения

```java
public class Main {
    public static void main(String[] args) {
        Sudoku sudoku = new Sudoku();
        sudoku.start();
    }
}
```

## Использование
После запуска приложения пользователь может ввести значения в текстовые поля и нажать кнопку "Solve", чтобы увидеть решение судоку прямо в интерфейсе.

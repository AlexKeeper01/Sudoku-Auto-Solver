# Автоматический решатель Судоку

## Описание
Этот проект реализует графический интерфейс для ввода и автоматического решения игры Судоку с помощью библиотеки Swing в Java. 

## Код Sudoku.java

```java
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Sudoku extends JFrame{
    private JTextField[][] cells = new JTextField[9][9];
    private final int SIZE = 81;
    private int[] field = new int[SIZE];
    private int[] field_changeable = new int[SIZE];

    public Sudoku() {
        setTitle("Sudoku Auto Solver");
        setSize(400, 450);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        JPanel gridPanel = new JPanel();
        gridPanel.setLayout(new GridLayout(3, 3));

        // Создаем 3x3 панели для каждой группы ячеек
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                JPanel panel = new JPanel();
                panel.setLayout(new GridLayout(3, 3));
                panel.setBorder(BorderFactory.createLineBorder(Color.BLACK, 2));

                for (int k = 0; k < 3; k++) {
                    for (int l = 0; l < 3; l++) {
                        cells[i * 3 + k][j * 3 + l] = new JTextField(1);
                        cells[i * 3 + k][j * 3 + l].setHorizontalAlignment(JTextField.CENTER);
                        cells[i * 3 + k][j * 3 + l].setFont(new Font("Arial", Font.BOLD, 18));
                        panel.add(cells[i * 3 + k][j * 3 + l]);
                    }
                }
                gridPanel.add(panel);
            }
        }

        JButton getDataButton = new JButton("Solve");
        getDataButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                fillBoard();
                solveSudoku();
            }
        });

        add(gridPanel, BorderLayout.CENTER);
        add(getDataButton, BorderLayout.SOUTH);
    }

    public void start() {
        setVisible(true);
    }

    private void updateFields() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cells[i][j].setText(String.valueOf(field[i * 9 + j]));
            }
        }
    }

    private void fillBoard() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                String text = cells[i][j].getText();
                field[i * 9 + j] = text.isEmpty() ? 0 : Integer.parseInt(text);
            }
        }
    }

    private boolean isValid(int row, int col) {
        int id = row * 9 + col;
        int current = field[id];
        for (int i = 0; i < 9; i++) {
            if (field[row * 9 + i] == current && row * 9 + i != id) {
                return false;
            }
        }
        for (int j = 0; j < 9; j++) {
            if (field[j * 9 + col] == current && j * 9 + col != id) {
                return false;
            }
        }
        int temp_row = (row / 3) * 3 + 1;
        int temp_col = (col / 3) * 3 + 1;
        for (int a = temp_row - 1; a < temp_row + 2; a++) {
            for (int b = temp_col - 1; b < temp_col + 2; b++) {
                int temp_id = a * 9 + b;
                if (field[temp_id] == current && temp_id != id) {
                    return false;
                }
            }
        }
        return true;
    }

    private void solveSudoku() throws WrongSudokuField, WrongSudokuNum {
        for (int i = 0; i < SIZE; i++) {
            if (!isValid(i / 9, i % 9) && field[i] != 0) {
                throw new WrongSudokuField("The field is filled in incorrectly.");
            }
        }
        for (int j = 0; j < SIZE; j++) {
            if (field[j] > 9 || field[j] < 0) {
                throw new WrongSudokuNum("Invalid value in the field.");
            }
        }
        for (int k = 0; k < SIZE; k++) {
            if (field[k] != 0) {
                field_changeable[k] = 1;
            }
        }
        int cursor = 0;
        String dir = "forward";
        while (cursor < SIZE) {
            if (field_changeable[cursor] != 0){
                if (dir.equals("forward")) {
                    cursor++;
                    continue;
                } else if (dir.equals("backward")) {
                    cursor--;
                    continue;
                }
            } else {
                if (field[cursor] == 9) {
                    field[cursor] = 0;
                    cursor--;
                    dir = "backward";
                    continue;
                } else {
                    field[cursor]++;
                    if (isValid(cursor / 9, cursor % 9)) {
                        cursor++;
                        dir = "forward";
                        continue;
                    }
                }
            }
        }
        updateFields();
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

#### Конструктор Sudoku
В конструкторе устанавливается название окна, его размеры и поведение при закрытии. Далее создается панель, на которую добавляются текстовые поля, сгруппированные по 3x3.

- **Метод `fillBoard()`**: Считывает значения из текстовых полей и заполняет массив `field` соответствующими значениями, заменяя пустые поля на 0.
- **Метод `updateFields()`**: Обновляет текстовые поля с решением судоку после его нахождения.
- **Метод `isValid(int row, int col)`**: Проверяет корректность введенных значений судоку, следуя правилам игры.
- **Метод `solveSudoku()`**: Реализует алгоритм решения судоку, проверяя корректность введенных данных и заполняя массив `field` с решением, если таковое возможно.

### Запуск приложения
Метод `start()` делает окно видимым для пользователя.

## Использование
После запуска приложения пользователь может ввести значения в текстовые поля и нажать кнопку "Solve", чтобы увидеть решение судоку прямо в интерфейсе.

## Заключение
Данный код представляет собой простой автоматический решатель судоку с графическим интерфейсом. Он может быть доработан и улучшен для повышения функциональности и удобства использования.

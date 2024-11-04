
# Sudoku Auto Solver

This project is a simple Sudoku auto solver implemented in Java using Swing for the graphical user interface. The application allows users to input a Sudoku puzzle and find a solution for it.

## Overview

The Sudoku solver consists of a main class named `Sudoku`, which extends `JFrame` to create a windowed application. The application includes a grid of text fields for inputting numbers, a button to trigger the solving process, and methods for validating and solving the Sudoku puzzle.

## Class Breakdown

### 1. Imports
```java
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
```
The code imports necessary classes from the Swing library for building the user interface and handling events.

### 2. Class Definition
```java
public class Sudoku extends JFrame {
```
The `Sudoku` class extends `JFrame`, allowing it to create a window where the Sudoku game will be displayed.

### 3. Instance Variables
```java
private JTextField[][] cells = new JTextField[9][9];
private final int SIZE = 81;
private int[] field = new int[SIZE];
private int[] field_changeable = new int[SIZE];
```
- `cells`: A 2D array of `JTextField` objects representing the Sudoku grid.
- `SIZE`: A constant representing the total number of cells in a Sudoku puzzle (9x9 = 81).
- `field`: An array storing the values of the Sudoku grid.
- `field_changeable`: An array to keep track of which cells can be modified.

### 4. Constructor
```java
public Sudoku() {
```
The constructor initializes the JFrame, sets the layout, and creates the grid of text fields.

#### Creating the Grid
```java
JPanel gridPanel = new JPanel();
gridPanel.setLayout(new GridLayout(3, 3));
```
A `JPanel` is created to hold the 3x3 panels that represent the Sudoku grid.

#### Adding Panels and Text Fields
```java
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
```
This nested loop creates a 3x3 grid of panels, each containing 9 text fields (total of 81) for user input.

### 5. Solve Button
```java
JButton getDataButton = new JButton("Solve");
getDataButton.addActionListener(new ActionListener() {
    @Override
    public void actionPerformed(ActionEvent e) {
        fillBoard();
        solveSudoku();
    }
});
```
A button labeled "Solve" is created, which triggers the solving process when clicked.

### 6. Method: `start()`
```java
public void start() {
    setVisible(true);
}
```
This method makes the JFrame visible when called.

### 7. Method: `updateFields()`
```java
private void updateFields() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cells[i][j].setText(String.valueOf(field[i * 9 + j]));
        }
    }
}
```
This method updates the text fields in the GUI with the values from the `field` array after solving the puzzle.

### 8. Method: `fillBoard()`
```java
private void fillBoard() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            String text = cells[i][j].getText();
            field[i * 9 + j] = text.isEmpty() ? 0 : Integer.parseInt(text);
        }
    }
}
```
This method reads the values from the text fields and fills the `field` array with these values, converting empty fields to 0.

### 9. Method: `isValid(int row, int col)`
```java
private boolean isValid(int row, int col) {
    int id = row * 9 + col;
    int current = field[id];
    // Check for validity in rows, columns, and boxes
}
```
This method checks if the current value at the specified row and column is valid according to Sudoku rules. It checks for duplicates in the same row, column, and 3x3 box.

### 10. Method: `solveSudoku()`
```java
private void solveSudoku() throws WrongSudokuField, WrongSudokuNum {
    // Validate the Sudoku field
    // Implement backtracking algorithm to solve the puzzle
    // Call updateFields() to display the solution
}
```
This method contains the logic to solve the Sudoku puzzle using a backtracking algorithm. It also includes validation checks for the current state of the Sudoku grid and updates the fields once a solution is found.

### 11. Main Method
```java
public static void main(String[] args) {
    SwingUtilities.invokeLater(() -> {
        Sudoku frame = new Sudoku();
        frame.start();
    });
}
```
The main method is the entry point of the application, creating an instance of `Sudoku` and making it visible on the Event Dispatch Thread (EDT).

## Conclusion

This Sudoku auto solver application is a simple yet effective way to demonstrate the use of Java's Swing framework for building user interfaces. The use of arrays and backtracking algorithms provides a solid foundation for solving Sudoku puzzles programmatically.

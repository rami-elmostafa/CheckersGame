# Fall 2024 CS 3503 Computer Organization and Architecture Checkers Game
## Rami Elmostafa
### Language Chosen: 
 - C programming language, due to its direct handling of low-level operations.
#### Purpose of this project: 
- Provide hands-on experience with low-level data handling, including binary arithmetic.
- Highlight the efficiency and practicality of bitwise operations and binary arithmetic in applications such as game development.
- Reinforce understanding of data representation and manipulation in binary formats.
- Foster a deeper understanding of Boolean algebra and binary arithmetic through practical applications.
##### Functionality Requirements
The utility class must include methods for: 
 - Setting a specific bit. 
 - Clearing a specific bit. 
 - Toggling a specific bit. 
 - Getting the value of a specific bit. 
 - Performing basic binary arithmetic (addition, subtraction, multiplication, and division). 
 - Converting data between decimal, binary, and hexadecimal formats. 
 - Methods should work for various data types (Byte, short, int, long or their equivalents).
###### Bitboard Checker's Application Requirements
Implement a bitboard that represents the checkers board, using the utility class. 
 - Demonstrate the bitboard's ability to: 
 - Represent and update the positions of the checkers pieces. 
 - Calculate and validate moves using binary arithmetic (e.g., shifting pieces using multiplication). 
 - Check for legal moves, captures, and conditions using bitwise operations. 
 - Display the checkers board state in binary and hexadecimal formats.

```mermaid
classDiagram
    class BitManipulation {
        +setBit(value, bit) 
        +clearBit(value, bit) 
        +toggleBit(value, bit) 
        +getBit(value, bit) 
        +add(a, b) 
        +subtract(a, b) 
        +multiply(a, b) 
        +divide(a, b) 
        +toBinary(value) 
        +toDecimal(value) 
        +toHexadecimal(value)
    }

    class BitboardChecker {
        +initializeBoard() 
        +updatePosition(from, to) 
        +calculateMoves(position) 
        +validateMove(move) 
        +checkLegalMoves(position) 
        +checkCaptures(position) 
        +displayBoardBinary() 
        +displayBoardHex()
    }

    BitManipulation -- BitboardChecker : uses```

###### Visual Representation
 - Implement a method to visually represent the Checker's board state on a console or graphical interface, showing binary and hexadecimal formats.
###### Sprints
 1. Research and Setup: Research bitwise operations in various languages. Choose a language.
 2. Utility Class: Develop a utility class to manipulate individual bits and perform arithmetic.
 3. Bitboard Application: Create a bitboard for a checkers game using the utility class.
 4. Documentation & Presentation: Write a report, document the application, and prepare a video demo.
 5. Final Submission: Submit code, report, and video.
######View the Final Report (.doc) 
<iframe src="https://docs.google.com/document/d/e/2PACX-1vR6HW-xK8MFDgO1YQlAov65aIoRwXgeg9iXwQLQgjAgNMe3yXNbk2dweM-Powg5fLZEr7LYKi4XcbMg/pub?embedded=true"></iframe> 
# Sudoku
I got this idea in the summer from another student. Create a sudoku program in C++
I talked to my CS teacher and he thought itll be hard but doable and so I hopped on the train and started crushing it
My plan was to first work with creating the board and then work on the playable aspect
I started with the print function. Probably the easiest
After that I created a 3D vector that contains the pencil marks for each square
A pencil mark is what each square could be. This means that they all start at 1-9 and slowly as numbers are assigned the squares limit their posisbilities
After that, I Start to randomly assign the values in the top corner and work to the bottom corner one at a time
I hit a snag that not all combos are going to work
I added a reset function for when it hits that snag
Basically it resets all the values, both the board array and 3D vector
There is enough comments for anyone to follow
I am so happy it works!

# test

# first example on canvas
echo 3 -4 5 1 7 0 8 0 15 12 3 5 3 3 3 3 3 | ./histogram

#second example on canvas
echo 3 -4 5 1 7 0 8 0 15 12 3 5 18 19 20 30 7 12 50 34 32 19 44| ./histogram

#third example on canvas
echo 150| ./histogram

# fourth example on canvas
echo {1..16} 150 | ./histogram


#my own examples

#1
echo 8 12 12 12 19 4 7 8 16 28 39 14 6 8 9 3 3 2| ./histogram

#2
echo 2 2 2 8 14 5 19 3 76 8 12 3 4 19 21| ./histogram

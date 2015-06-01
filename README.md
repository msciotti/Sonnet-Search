# Sonnet-Search
A program that searches Shakespeare's sonnets for unique word information written in C++

These two programs search through the entire collection of Shakespeare's sonnets for information about unique words. The first, unique_words.cpp, reads the text of Shakespeare’s sonnets from a text file and stores each unique word in a hash table, counting the number of times that word is used. It then iterates through the hash table, placing each wordPair (made of the word and its frequency) into a vector, thereby eliminating blank locations. Finally, it sorts the vector alphabetically and outputs each unique word and how many times it is used in the sonnets.

The second, specific_sonnet.cpp, inputs the text from Shakespeare’s sonnets from a file and stores the words in a binary search tree. It then searches for a user-inputted sonnet, displays the sonnet, and displays a list of all the words used in the sonnet in alphabetical order. This is done by traversing the previously created binary search tree.

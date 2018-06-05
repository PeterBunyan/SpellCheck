# SpellCheck

# Synopsis
This program is a spell-checker. It loads a dictionary, reads in the text from one of the associated text files and checks the spelling of each word, based on whether or not that word is found in the associated dictionary file. The time required for each step is measured and totaled.

# Useage
Download zip file and, after unzipping, go to CS50 IDE at https://cs50.io/
Create new folder on left side of screen. Drag contents from unzipped folder to newly created folder.
Using terminal window from IDE, navigate to "SpellCheck-master" folder.

Compile program using the following command:
"make speller".

The spell-checker uses the "large" dictionary file, by default:
./speller texts/text file

If a different dictionary is desired:
./speller dictionaries/dictionary file texts/text file

Execution code example:
./speller texts/alice.txt

Program Output:
WORDS MISSPELLED:     127
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        29758
TIME IN load:         0.14
TIME IN check:        0.03
TIME IN size:         0.00
TIME IN unload:       0.28
TIME IN TOTAL:        0.45

# Purpose
This problem set was designed with the function body of each function in "dictionary.c" left blank to allow any implementation of data structures.
The goal was to choose the data structure that would solve the problem in the shortest amount of time. This program uses a trie data structure to load in the dictionary of words that gets text-file words checked against.

# Contributors
Only the logic contained within "dictionary.c" is my own creation. The other files are the work of the Harvard CS50 team.

# License
I claim no license over the code contained within “dictionary.c” or the files from the Harvard CS50 team which implement its functionality.

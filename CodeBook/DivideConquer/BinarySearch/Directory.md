
# Binary Seach

### Fill Bates

Given string `S`, and multiple queries consisting of strings `s_i`. We want to find the first and shortest substring of `s_i` that appears in `S`, or state there is none.

##### Solution

For each of type of character in `S` ('a' to 'z' and 'A' to 'Z') we keep a vector of all the occurences of the character in order. Say we are at position `pos` in S and want to find the ith letter of s_i. We can simply binary search for the first occurence of that letter, looking in the correct index of our vector. 

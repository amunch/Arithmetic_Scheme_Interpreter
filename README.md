Project 01: uScheme
===================

This is a simple implementation of a [Scheme] interpreter that supports the
following syntax:

    <digit>         = 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
    <number>        = {<digit>}
    <op>            = - | + | * | /
    <expression>    = (<op> <expression> <expression>) | <number>

Examples
--------

    :::scheme
    1
    (+ 1 2)
    (+ 1 (- 2 3))
    (+ (* 1 2) (- 3 4))

[Scheme]:   https://en.wikipedia.org/wiki/Scheme_(programming_language)

Questions
---------

Question 1:
	The complexity of this program is Nlog(N), where N is the total number of characters, including digits, operations, and parentheses.  This is because it takes N operations to read in all of the data, and then log(N) to traverse the tree for each element.  This time to run this program would increase slightly more than constantly for an increase in the size of the input.  A stack does not affect the evaluation because all operations on the stack take place in constant time.

Question 2:
	The uscheme executable size is 112K while the uschemeSmart is 171K. However, the memory used by both executables is same. We prefer the one with smart pointers even though the size of the executable is larger. The amount of memory the smart pointer program uses is not enough to outweigh the easiness of using smart pointers. Furthermore, smart pointers protect us from memory leaks and helps prevents errors. Therefore, using smart pointers is the better choice since the pros easily override the con of the larger executable.  

Question 3:
	To support more than 2 numbers or operators, the tree could no longer be binary. Each parent would need to support more than two children or a different container would need to be used all together such has the struct containig a stack of nodes. The parser would need to continue to accept new numbers and push into the stack of nodes until a ")" is reached. The interpreter would need to popout all the numbers from the stack and compute them by using the operator on the total and the new number. 


Both members of the group pair programmed the entire project so each member was present and involved in all aspects of producing the end result.

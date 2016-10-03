Project 01: uScheme
===================

By Andy Munch (amunch) & Mark Pruitt (mpruitt1)

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

*Question 1:*
	The complexity of this program is N, where N is the total number of characters, including digits, operations, and parentheses.  This is because it takes N operations to read in all of the data, and then N to evaluate the tree, so by definition of big-O this will be O(N).  This time to run this program would increase constantly for an increase in the size of the input (double the size of the input will double the time taken).  A stack does not affect the evaluation in terms of complexity because the complexity of the operations performed are constant (top, pop, and push).

*Question 2:*
	The uscheme executable size is 112K while the uschemeSmart is 171K.  The memory used by uschemeSmart is slightly larger, .738 Mbytes compared to .727 Mbytes, based on the provided measure program and inputting a small Scheme line (+ 1 2). We prefer the one with smart pointers even though the size of the executable is larger. The amount of memory the smart pointer program uses is not enough to outweigh the easiness of using smart pointers. Furthermore, smart pointers protect us from memory leaks and helps prevents errors. Therefore, using smart pointers is the better choice since the pros easily override the con of the larger executable.  

*Question 3:*
	To support more than 2 numbers or operators, the tree could no longer be binary. Each parent would need to support more than two children or a different container would need to be used all together such has the struct containig a stack of nodes. The parser would need to continue to accept new numbers and push into the stack of nodes until a ")" is reached. The interpreter would need to popout all the numbers from the stack and compute them by using the operator on the total and the new number. 

*Contributions:*
	Both members (amunch & mpruitt1) of the group pair programmed the entire project so each member was present and involved in all aspects of producing the end result.

# Scalc

### Description

#### Purpose
This is an application to evaluate set of integers based on given input data.

Where the whole grammar is:
expression := “\[“ operator N sets “\]”
sets := set | set sets
set := file | expression
operator := “EQ” | “LE” | “GR”

“file” is a file with sorted integers, one integer in a line.
“N” is a positive integer
Meaning of operators:
EQ - returns a set of integers which consists only from values which exists in exactly N sets -
arguments of operator
LE - returns a set of integers which consists only from values which exists in less then N sets -
arguments of operator
GR - returns a set of integers which consists only from values which exists in more then N sets -
arguments of operator

#### Input data
Input should be provided argument by argument with spaces between.
It's allowed to provide arguments
{"[", "]", "<file_path>", "GR", "LE", "EQ", "<integer_value>"}

#### Return data
* sorted unique positive integers, one integer in a line
* error message if occurs (look Error handling)

#### Error handling
Program will return an error in following situations:
* given file is empty
* given file contains non-digit chars
* given file contains more than one digit per line
* argument doesn't match to list of allowed arguments


#### Unit tests
For unit tests its needed to download gtest and put
in subdirectory called gtest
https://github.com/google/googletest
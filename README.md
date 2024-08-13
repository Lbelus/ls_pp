# ls_pp
A basic implementation of ls in full cpp



Topics: Static_cast, dynamic_cast, reinterpret_cast

## Task

Project: Create a custom Linux ls command implementation that lists files in a directory. Use different cast types when processing file attributes, like determining if an entry is a file or directory.

## Description

Display each operand that names a file of a type different than directory. Must display names any requested or/and associated information.

Display each operand that names a file of a type directory. Must display names of files within directory any requested or/and associated information.

if no operand : content of current directory's content is displayed

if more than one operand : non directory operand are displayed first
directory and non directory are sorted separately and in lexicographical order.

Flags :

-a include directory entries beginning with a dot (.).
-t sort by time modified (most recently modified first) before sorting by lexicographical order. ==>Recommendation : make use of tv_sec and tv_nsec.



## Installation


## Usage




## The Core Team
* [Lorris BELUS](//github.com/Lbelus) - Developer


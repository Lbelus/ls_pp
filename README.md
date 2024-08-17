# ls_pp
A basic implementation of ls in full cpp



Topics: std::filesystem, lambda, vector

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
go to ``build`` dir:
```bash
cmake ..
make
```


## Usage

insert my_ls ``OPTION``... ``file``... into terminal

-t provide a file list sorted by time
-a provide a list with hidden files

exemple :
```bash
   ./ls_pp
   ./ls_pp -t dir1
   ./ls_pp -a dir1 
   ./ls_pp -at dir1 dir2 dir3
```

## The Core Team
* [Lorris BELUS](//github.com/Lbelus) - Developer


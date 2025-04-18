## Custom Linux and Git
### Git
-Custom git log 
```c++ 
    alias plog='git log --pretty=format:"%Cred[%h] %Cblue[%cs] %Cgreen[%an] %Creset%s"'

    //Example: 
    // [ebf59fa] [2024-06-27] [DuyDat] Noref: upgrade code
    // [7804ff8] [2024-06-20] [DuyDat] Noref: update relative path for some data file
    // [c11cd04] [2024-06-20] [DuyDat] Noref: replace raw pointer to smart pointer
    // [58de3ed] [2024-06-20] [DuyDat] Noref: move some function from prj2.cpp to utils
    // [9b77e2e] [2024-06-18] [DuyDat] Noref: seperate chechValid.h and add .gitignore
    // [2eb7e5e] [2024-06-18] [DuyDat] Noref: seperate some method to utils.
```
### Linux
- Custom PS1:
```bat 
parse_git_branch(){
        git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/ (\1)/'
}

export PS1="\n\[\e[38;5;195m\]\w\[\033[0m\]\[\033[33m\]\n \[\e[38;5;51m\]evuxdat\[\e[0;31m\]$(parse_git_branch)\[\033[00m\]$ "

#example:
~/repo/Knowledge_CPP/Bash
 evuxdat (main)$ 
```

- grep 'a': filter with pattern 'a'
- uniq -c : report or omit repeated lines; -c count occurence.
- sort    : sort line of the text file
- sed -r 's/\s+(.*) ()/\\2\\1/': ignore space, capture 1 and capture 2 and reverse them
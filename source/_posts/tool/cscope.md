---
title: cscope 安装，配置，使用
categories:
- tools
date: 2021/2/8
toc: true # 是否启用内容索引
---

---
### 安装
---
~~~
    sudo apt install cscope
~~~

---
### 配置
---
~/.vimrc 中添加如下配置
~~~bash
    " tags 设置
    set tags=tags;
        set autochdir

    if has("cscope")
        set csprg=/usr/bin/cscope
        "指定用来执行 cscope 的命令
        set csto=1
        "先搜索tags标签文件,再搜索cscope数据库
        set cst
        "使用|:cstag|(:cs find g),而不是缺省的:tag
        set nocsverb
        "不显示添加数据库是否成功
        " add any database in current directory
        if filereadable("cscope.out")
            cs add cscope.out
        "添加cscope数据库
        endif
        "显示添加成功与否
        set csverb
    endif

    :set cscopequickfix=s-,c-,d-,i-,t-,e-

    nmap <C-\>s :cs find s <C-R>=expand("<cword>")<CR><CR>
    nmap <C-\>g :cs find g <C-R>=expand("<cword>")<CR><CR>
    # 查找哪里调用了当前的函数
    nmap <C-\>c :cs find c <C-R>=expand("<cword>")<CR><CR>
    nmap <C-\>t :cs find t <C-R>=expand("<cword>")<CR><CR>
    # 查找所有符号
    nmap <C-\>e :cs find e <C-R>=expand("<cword>")<CR><CR>
    nmap <C-\>f :cs find f <C-R>=expand("<cfile>")<CR><CR>
    nmap <C-\>i :cs find i ^<C-R>=expand("<cfile>")<CR>$<CR>
    nmap <C-\>d :cs find d <C-R>=expand("<cword>")<CR><CR>
~~~

---
### 建立索引
---
建立脚本，执行生成tag, cscope符号表
~~~bash
    #!/bin/sh
    find `pwd` -name "*.[ch]" -o -name "*.cpp" > cscope.files  
    cscope -bRkq -i cscope.files  

    ctags -R
~~~

---
### cscope 使用
---
快捷键，上面配置中已经配置了。
~~~bash
    cscope --help
    Usage: cscope [-bcCdehklLqRTuUvV] [-f file] [-F file] [-i file] [-I dir] [-s dir]
                [-p number] [-P path] [-[0-8] pattern] [source files]

    -b            Build the cross-reference only.
    -C            Ignore letter case when searching.
    -c            Use only ASCII characters in the cross-ref file (don't compress).
    -d            Do not update the cross-reference.
    -e            Suppress the <Ctrl>-e command prompt between files.
    -F symfile    Read symbol reference lines from symfile.
    -f reffile    Use reffile as cross-ref file name instead of cscope.out.
    -h            This help screen.
    -I incdir     Look in incdir for any #include files.
    -i namefile   Browse through files listed in namefile, instead of cscope.files
    -k            Kernel Mode - don't use /usr/include for #include files.
    -L            Do a single search with line-oriented output.
    -l            Line-oriented interface.
    -num pattern  Go to input field num (counting from 0) and find pattern.
    -P path       Prepend path to relative file names in pre-built cross-ref file.
    -p n          Display the last n file path components.
    -q            Build an inverted index for quick symbol searching.
    -R            Recurse directories for files.
    -s dir        Look in dir for additional source  files.
    -T            Use only the first eight characters to match against C symbols.
    -U            Check file time stamps.
    -u            Unconditionally build the cross-reference file.
    -v            Be more verbose in line mode.
    -V            Print the version number.

    Please see the manpage for more information.
~~~

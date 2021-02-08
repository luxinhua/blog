---
title: vim plug 
categories:
- tools
date: 2021/2/8
toc: true # 是否启用内容索引
---

---
### 安装vim-plug 
---
~~~
    vim    :  curl -fLo ~/.vim/autoload/plug.vim --create-dirs https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
    neovim :  curl -fLo ~/.config/nvim/autoload/plug.vim --create-dirs https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
~~~


---
### 配置 vim-plug
---
修改 ~/.vimrc
~~~
    call plug#begin('~/.vim/plugged')
    Plug 'itchyny/lightline.vim'
    call plug#end()
~~~

---
### 插件操作
---
~~~
    # 导入插件
    :PlugInstall

    # 更新插件
    :PlugUpdate

    # 清理插件
    :PlugClean
~~~

---
### 常用插件
---
~~~
    # 目录树
    Plug 'scrooloose/nerdtree', { 'on':  'NERDTreeToggle' }  
~~~

---
### 配置实现的插件
---
换行 ALT + 上下 实现vscode类似的换行效果
~~~
    noremap <A-up> :call feedkeys( line('.')==1 ? '' : 'ddkP' )<CR>
    noremap <A-down> ddp
~~~
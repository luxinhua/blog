" Copyright (c) %Y XinHuaNo Company Inc. All rights reserved.
" Author            : Xin Hua Lu  <2846154596@qq.com>
" Date              : 2021-09-05 05:19:53
" Last Modified Date: 2021-09-05 05:19:53
" Last Modified By  : Xin Hua Lu  <2846154596@qq.com>

set nu
set ts=2
set cursorcolumn     
set nocscopeverbose  
set cursorline
set expandtab

highlight CursorLine   cterm=NONE ctermbg=black ctermfg=green guibg=NONE guifg=NONE
highlight CursorColumn cterm=NONE ctermbg=black ctermfg=green guibg=NONE guifg=NONE
                                        
call plug#begin('~/.vim/plugged')       
Plug 'rootkiter/vim-hexedit'
Plug 'vim-airline/vim-airline'
Plug 'matze/vim-move'
Plug 'scrooloose/nerdcommenter'
Plug 'neoclide/coc.nvim', {'branch': 'release'}
Plug 'crusoexia/vim-monokai'
Plug 'chazy/cscope_maps'
Plug 'vim-scripts/a.vim'
Plug 'scrooloose/nerdtree'
Plug 'jiangmiao/auto-pairs'
Plug 'alpertuna/vim-header'
Plug 'mbbill/undotree'
Plug 'Yggdroot/indentLine'
Plug 'rking/ag'
Plug 'terryma/vim-multiple-cursors'
Plug '~/my-prototype-plugin'
call plug#end()

" indentLine
" 开启缩进线
let g:indentLine_enabled = 1
" json和markdown文件禁用缩进线，避免特殊的显示问题
let g:vim_json_syntax_conceal = 0
let g:indentLine_fileTypeExclude = ['json', 'markdown']
augroup indentline_
    autocmd!
    autocmd BufRead,BufNewFile * if count(['markdown'], &ft) | setlocal conceallevel=0 | endif
augroup END


"
" coc 
" 使用<c-space>结束补全
inoremap <silent><expr> <C-space> coc#refresh()
" 使用`[g` and `]g` 跳转到下一个问题诊断处
nmap <silent> [g <Plug>(coc-diagnostic-prev)
nmap <silent> ]g <Plug>(coc-diagnostic-next)

" 跳转到定义位置
nmap <silent> <C-g> <Plug>(coc-definition)
nmap <silent> <leader>gd <Plug>(coc-definition)
" 跳转到类型定义位置
nmap <silent> <leader>gt <Plug>(coc-type-definition)
" 跳转到实现位置
nmap <silent> <leader>gi <Plug>(coc-implementation)
" 跳转到引用位置
nmap <silent> <leader>gr <Plug>(coc-references)
" 修复当前行可修复的第一个错误修复操作。
nmap <leader>gy <Plug>(coc-fix-current)

" 在预览窗口中展示光标下符号的文档
nnoremap <silent> <leader>gh :call <SID>show_documentation()<CR>
function! s:show_documentation()
    if (index(['vim','help'], &filetype) >= 0)
        execute 'h '.expand('<cword>')
    else
        call CocActionAsync('doHover')
    endif
endfunction
augroup coc_
    autocmd!
    " 自动高亮光标下的符号
    autocmd CursorHold * silent call CocActionAsync('highlight')
augroup END
" 显示所有诊断信息
nnoremap <silent> <leader>ga  :<C-u>CocList diagnostics<cr>
" 重命名光标下的符号
nmap <leader>gn <Plug>(coc-rename)

let g:coc_global_extensions = []
let g:coc_global_extensions += ['coc-ultisnips']
let g:coc_global_extensions += ['coc-yaml']
let g:coc_global_extensions += ['coc-highlight']
let g:coc_global_extensions += ['coc-git']
let g:coc_global_extensions += ['coc-vimlsp']
let g:coc_global_extensions += ['coc-tsserver']
let g:coc_global_extensions += ['coc-json']
let g:coc_global_extensions += ['coc-java']
let g:coc_global_extensions += ['coc-metals']
let g:coc_global_extensions += ['coc-markdownlint']
let g:coc_global_extensions += ['coc-jedi']
let g:coc_global_extensions += ['coc-go']

let g:coc_global_extensions += ['coc-clangd']
call coc#config('clangd.semanticHighlighting', 1)
" 在C++的头文件和实现文件间切换
nmap <silent> <Leader>a :CocCommand clangd.switchSourceHeader<cr>
highlight LspCxxHlGroupMemberVariable ctermfg=LightGray  guifg=LightGray



" vim-multiple-cursors
function! Multiple_cursors_before()
    let s:old_ycm_whitelist = g:ycm_filetype_whitelist
    let g:ycm_filetype_whitelist = {}
    set foldmethod=manual
endfunction
function! Multiple_cursors_after()
    let g:ycm_filetype_whitelist = s:old_ycm_whitelist
    set foldmethod=indent
endfunction

" Ag 
" cmd : Ag <you want world>


" mbbill/undotree
nnoremap <F5> :UndotreeToggle<CR>

" alpertuna/vim-header  ok 
let g:header_field_author = 'Xin Hua Lu '
let g:header_field_author_email = '2846154596@qq.com'
let g:header_auto_add_header = 0
let g:header_auto_update_header = 1
let g:header_field_filename = 0
let g:header_field_timestamp_format = '%Y-%m-%d %H:%M:%S'
let g:header_field_copyright = 'Copyright (c) %Y XinHuaNo Company Inc. All rights reserved.'
let g:header_alignment = 1
let g:header_max_size = 20
map <F1> :AddHeader<CR>

"
"" " 自动识别文件类型,使用文件类型plugin脚本,使用缩进定义文件
filetype plugin indent on
" 打开语法加亮
syntax on
" session中不保存当前目录，这样使用Session.vim文件恢复时，Session.vim文件所在目录自动变成当前目录
set sessionoptions-=curdir
set sessionoptions+=sesdir
" 用啥鼠标
set mouse-=a
" 文件修改之后自动载入
set autoread
" 开启正则表达式的magic模式，例如使用\w匹配单词
set magic
" 设置不兼容vi, 只使用增强模式
set nocompatible
" 设置可以删除行首空格,断行, 进入Insert模式之前的位置
set backspace=indent,eol,start
" 新行使用设置自动缩进,使用上一行的缩进方式
set autoindent
" 设置智能缩进
set smartindent
" 设置命令历史列表的长度
set history=50
" 将TAB替换为空格
set expandtab
" 设置TAB宽度
set tabstop=4
" 和ignorecase配合实现智能大小写匹配
set smartcase
set ignorecase
" 在80个字符处设置锚线
set colorcolumn=80
" 补全内容不以分割子窗口形式出现，只显示补全列表
set completeopt=longest,menu,preview
" 使路径包含当前目录下的所有子目录
set path+=**



"matze/vim-move ok
:map <C-Up>     <plug>MoveBlockUp
:map <C-Left>   <plug>MoveBlockLeft
:map <C-Right>  <plug>MoveBlockRight
:map <C-Down>   <plug>MoveLineDown
:map <C-Up>     <plug>MoveLineUp

" scrooloose/nerdcommenter  ok
" Create default mappings
let g:NERDCreateDefaultMappings = 1
" Add spaces after comment delimiters by default
let g:NERDSpaceDelims = 1
" Use compact syntax for prettified multi-line comments
let g:NERDCompactSexyComs = 1
" Align line-wise comment delimiters flush left instead of following code indentation
let g:NERDDefaultAlign = 'left'
" Set a language to use its alternate delimiters by default
let g:NERDAltDelims_java = 1
" Add your own custom formats or override the defaults
let g:NERDCustomDelimiters = { 'c': { 'left': '/**','right': '*/' } }
" Allow commenting and inverting empty lines (useful when commenting a region)
let g:NERDCommentEmptyLines = 1
" Enable trimming of trailing whitespace when uncommenting
let g:NERDTrimTrailingWhitespace = 1
" Enable NERDCommenterToggle to check all selected lines is commented or not
let g:NERDToggleCheckAllLines = 1"
:map <C-z>  <plug>NERDCommenterToggle

" Plug 'crusoexia/vim-monokai'  ok 
colo monokai

"　NERDTreeToggle  ok 
map <F2> :NERDTreeToggle<CR>

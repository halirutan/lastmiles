
Sun Aug 11 19:03:59 UTC 2019

Two different vim rc files for any user :

suppose you want colour highlights and language syntax for
C programming etc however you want to always have a tab char
as just four spaces : 

syntax on
set t_Co=256
colo elflord
filetype plugin indent on
" show existing tab with 4 spaces width
set tabstop=4
" when indenting with '>', use 4 spaces width
set shiftwidth=4
" On pressing tab, insert 4 spaces
set expandtab
 

suppose you want vim to just act like plain jane ordinary vi with
no smart silly indent or colour or anything else : 

syntax off
augroup auto_comment
    au!
    au FileType * setlocal formatoptions-=c formatoptions-=r formatoptions-=o
augroup END



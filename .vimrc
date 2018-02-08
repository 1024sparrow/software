set ts=4
set sw=4
set sts=4
set et
syntax on
set number
set hlsearch

colorscheme color1

nnoremap <F2> :shell<CR>

:let mapleader = "-"
xmap <leader>y :w! ~/.vitmp<CR>
nmap <leader>p :r! cat ~/.vitmp<CR>

" GENERAL SETTINGS PREFERENCES
set noswapfile
set background=dark
set t_Co=256
set hlsearch

nmap <PageUp> :tabp<CR>
nmap <PageDown> :tabn<CR>

autocmd Filetype cpp setlocal tabstop=4
autocmd Filetype cpp setlocal shiftwidth=4
autocmd Filetype cpp setlocal expandtab

" VUNDLE SETTINGS
set rtp+=~/.vim/bundle/vundle/
call vundle#begin()

" let vundle manage vundle
Plugin 'gmarik/vundle'

" list all plugins that you'd like to install here
Plugin 'scrooloose/syntastic' " syntax checker
Plugin 'kien/ctrlp.vim' " fuzzy find files
Plugin 'scrooloose/nerdtree' " file drawer, open with :NERDTreeToggle
Plugin 'tpope/vim-fugitive' " the ultimate git helper
Plugin 'tpope/vim-commentary' " comment/uncomment lines with gcc or gc in visual mode
Plugin 'tpope/vim-surround' " quoting/parenthesizing made simple
Plugin 'valloric/youcompleteme' " code completion engine for Vim
Plugin 'vim-airline/vim-airline' " status/tabline for vim very light
Plugin 'vim-airline/vim-airline-themes' " themes for the status/tabline
Plugin 'altercation/vim-colors-solarized' " precision color scheme for vim text editor
Plugin 'godlygeek/tabular' " text filtering alignment

call vundle#end()
filetype plugin indent on

" VIM TOOLS MAPPING
nmap <F1> :NERDTreeToggle<CR>
nmap <F2> :CtrlP<CR>

" SYNTASTIC SETTINGS
set statusline+=%#warningmsg#
set statusline+=%{SyntasticStatuslineFlag()}
set statusline+=%*

let g:syntastic_always_populate_loc_list = 1
let g:syntastic_auto_loc_list = 1
let g:syntastic_check_on_open = 1
let g:syntastic_check_on_wq = 0

let g:syntastic_cpp_checkers = ['gcc']

" AIRLINE SETTINGS
let g:airline#extensions#tabline#enabled = 1
let g:airline#extensions#tmuxline#enabled = 1

" YOUCOMPLETEME
let g:ycm_show_diagnostics_ui = 0 
let g:ycm_autoclose_preview_window_after_insertion = 1
set completeopt-=preview
let g:ycm_key_list_stop_completion = ['<Right>']
let g:ycm_key_invoke_completion = '<C-Space>'

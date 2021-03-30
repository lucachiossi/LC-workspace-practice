" GENERAL SETTINGS PREFERENCES
set noswapfile
set t_Co=256
set hlsearch
set number
set mouse=a

colorscheme dante

nmap <PageUp> :tabp <CR><F4><F4>
nmap <PageDown> :tabn<CR><F4><F4>

" in case not sure about filetype
" echo &filetype

autocmd Filetype sh setlocal tabstop=2 shiftwidth=2 expandtab
autocmd Filetype javascript setlocal tabstop=2 shiftwidth=2 expandtab
autocmd Filetype json setlocal tabstop=2 shiftwidth=2 expandtab

autocmd Filetype cpp setlocal tabstop=4 shiftwidth=4 expandtab
autocmd Filetype xml setlocal tabstop=4 shiftwidth=4 expandtab
autocmd Filetype html setlocal tabstop=4 shiftwidth=4 expandtab
autocmd Filetype htmldjango setlocal tabstop=4 shiftwidth=4 expandtab

" *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* VUNDLE - PLUGINS SETUP *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
set nocompatible              " be iMproved, required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

" let Vundle manage Vundle, required
Plugin 'gmarik/Vundle.vim'

" list all plugins that you'd like to install here

" 1) ----------> youcompleteme (autocomplete)
Plugin 'valloric/youcompleteme'
"cd ~/.vim/bundle/youcompleteme
"git checkout d98f896
"python install.py --all

" 2) ----------> syntax checker
Plugin 'scrooloose/syntastic' 
":SyntasticInfo to see what's goin on

" 3) ----------> file drawer, open with :NERDTreeToggle
Plugin 'scrooloose/nerdtree' 

" 4) ----------> the ultimate git helper
Plugin 'tpope/vim-fugitive'

" 5) ----------> comment/uncomment lines with gcc or gc in visual mode
Plugin 'tpope/vim-commentary'

" 6) ----------> quoting/parenthesizing made simple
Plugin 'tpope/vim-surround'

" 7) ----------> status/tabline for vim very light
Plugin 'vim-airline/vim-airline'

" 8) ----------> themes for the status/tabline
Plugin 'vim-airline/vim-airline-themes'

" 9) ----------> color scheme pack for vim text editor
Plugin 'flazz/vim-colorschemes'
" cp colors/* ~/.vim/colors

" 10) ---------> text filtering alignment
Plugin 'godlygeek/tabular' 

" 11) ---------> fuzzy find files
Plugin 'kien/ctrlp.vim'

" 12) ---------> autoclose (X)HTML tags
Plugin 'alvan/vim-closetag'

" 13) ---------> displays tags in a window, ordered by scope
Plugin 'majutsushi/tagbar'
" apt install exuberant-ctags

" 14) ---------> always highlights the enclosing html/xml tags
Plugin 'valloric/matchtagalways'

call vundle#end()            " required
filetype plugin indent on    " required
" *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* VUNDLE - PLUGINS SETUP *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

" TOOLS MAPPING
nmap <F1> :NERDTreeToggle<CR>
nmap <F2> :CtrlP<CR>
nmap <F3> :TagbarToggle<CR>
nmap <F4> :call SyntasticToggle()<CR>

" SETTINGS syntastic
set statusline+=%#warningmsg#
set statusline+=%{SyntasticStatuslineFlag()}
set statusline+=%*

let g:syntastic_always_populate_loc_list = 1
let g:syntastic_auto_loc_list = 1
let g:syntastic_check_on_open = 1
let g:syntastic_check_on_wq = 0

let g:syntastic_is_open = 0  
function! SyntasticToggle()
	if g:syntastic_is_open == 1
		lclose
		let g:syntastic_is_open = 0 
	else
		Errors
		let g:syntastic_is_open = 1 
	endif
endfunction

" C++
let g:syntastic_cpp_checkers = ['gcc']
" python
let g:syntastic_python_checkers = ['pylint']
" javascript/reactES6
let g:syntastic_javascript_checkers = ['eslint']
" npm -g install eslint
" npm -g install eslint-plugin-react
" configure ~/.eslintrc
"	parser: "babel-eslint",
"	plugin: ["react"],

" SEETTINGS airline
let g:airline#extensions#tabline#enabled = 1
let g:airline#extensions#tmuxline#enabled = 1

" SEETTINGS youcompleteme
let g:ycm_show_diagnostics_ui = 0 
let g:ycm_autoclose_preview_window_after_insertion = 1
set completeopt-=preview
let g:ycm_key_list_stop_completion = ['<Right>']
let g:ycm_key_invoke_completion = '<C-Space>'

" SETTINGS closetag
let g:closetag_filenames = '*.html,*.xhtml,*.phtml'
let g:closetag_xhtml_filenames = '*.xhtml,*.jsx'
let g:closetag_shortcut = '>'
" Disables auto-close if not in a valid region (based on filetype)
" let g:closetag_regions = {'typescript.tsx': 'jsxRegion,tsxRegion' 'javascript.jsx': 'jsxRegion'}

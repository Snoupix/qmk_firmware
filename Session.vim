let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/work/qmk
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +243 keyboards/crkbd/keymaps/snoupix/keymap.c
badd +29 keyboards/crkbd/keymaps/snoupix/rules.mk
badd +255 keyboards/crkbd/keymaps/snoupix/oled_bongocat.c
badd +425 keyboards/crkbd/keymaps/snoupix/oled_luna.c
badd +1 keyboards/crkbd/keymaps/snoupix/oled_font.c
badd +9 keyboards/crkbd/keymaps/snoupix/oled_icons.c
badd +125 keyboards/crkbd/keymaps/snoupix/config.h
badd +1 display_keymap.rs
badd +288 keyboards/crkbd/keymaps/colemak_luna/keymap.c
badd +1 keyboards/crkbd/keymaps/colemak_luna/config.h
argglobal
%argdel
edit keyboards/crkbd/keymaps/snoupix/config.h
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
argglobal
balt keyboards/crkbd/keymaps/snoupix/keymap.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 107 - ((27 * winheight(0) + 28) / 56)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 107
normal! 03|
lcd ~/work/qmk
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
nohlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :

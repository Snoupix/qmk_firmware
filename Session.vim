let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd /home/snoupix/work/qmk
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +399 keyboards/crkbd/keymaps/snoupix/keymap.c
badd +29 keyboards/crkbd/keymaps/snoupix/rules.mk
badd +1 keyboards/crkbd/keymaps/snoupix/oled_font.c
badd +9 keyboards/crkbd/keymaps/snoupix/oled_icons.c
badd +36 keyboards/crkbd/keymaps/snoupix/config.h
badd +46 display_keymap.rs
badd +470 keyboards/crkbd/keymaps/snoupix/oled_right.c
badd +137 keyboards/crkbd/keymaps/snoupix/oled_left.c
badd +1 .gitignore
argglobal
%argdel
edit keyboards/crkbd/keymaps/snoupix/keymap.c
argglobal
balt keyboards/crkbd/keymaps/snoupix/oled_right.c
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
let s:l = 480 - ((27 * winheight(0) + 27) / 55)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 480
normal! 09|
lcd /home/snoupix/work/qmk
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
nohlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :

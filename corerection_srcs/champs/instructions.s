.name		"All instructions possible"
.comment	"Corewar is fun"

live	%1
ld		:1, r1
ld		%1, r1
st		r1, r1
st		r1, :1
add		r1, r1, r1
sub		r1, r1, r1
and		r1, r1, r1
and		r1, %1, r1
and		r1, :1, r1
and		%1, r1, r1
and		%1, %1, r1
and		%1, :1, r1
and		:1, r1, r1
and		:1, %1, r1
and		:1, :1, r1
or		r1, r1, r1
or		r1, %1, r1
or		r1, :1, r1
or		%1, r1, r1
or		%1, %1, r1
or		%1, :1, r1
or		:1, r1, r1
or		:1, %1, r1
or		:1, :1, r1
xor		r1, r1, r1
xor		r1, %1, r1
xor		r1, :1, r1
xor		%1, r1, r1
xor		%1, %1, r1
xor		%1, :1, r1
xor		:1, r1, r1
xor		:1, %1, r1
xor		:1, :1, r1
zjmp	%:1
ldi		r1, %1, r1
ldi		r1, %:1, r1
ldi		%1, %1, r1
ldi		%1, %:1, r1
ldi		%:1, %1, r1
ldi		%:1, %:1, r1
sti		r1, r1, %1
sti		r1, r1, %:1
sti		r1, %1, %1
sti		r1, %1, %:1
sti		r1, %:1, %1
sti		r1, %:1, %:1
fork	%:1
lld		:1, r1
lld		%1, r1
lldi	r1, %1, r1
lldi	r1, %:1, r1
lldi	%1, %1, r1
lldi	%1, %:1, r1
lldi	%:1, %1, r1
lldi	%:1, %:1, r1
lfork	%:1
aff		r1
1:

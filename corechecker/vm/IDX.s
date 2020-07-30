.name		"IDX"
.comment	"A way to demonstrate that the VM correctly applies IDX modulo when required"

ld		517, r1			# equivalent to ld 5, r1
st		r1, 576			# equivalent to st r1, 64
ldi		%260, %259, r2	# total is 7 bytes further, which is the next instruction
sti		r2, %512, %64	# total is 576 % IDX = 64 bytes further
ld		%0, r3			# setting the carry to 1
zjmp	%521			# equivalent to zjmp 9, skipping to the 4th zjmp
zjmp	%11				# this zjmp would skip to the end of the instructions, but will never be executed
zjmp	%6				# jumping to st r1, 64
zjmp	%-515			# equivalent to zjmp -3, going back to the 3rd zjmp
st		r1, 576			# this command getting executed proves that the zjmp are correctly applying IDX mod

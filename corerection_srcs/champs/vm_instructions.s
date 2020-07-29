.name		"VM instructions"
.comment	"Demonstrating that the vm executes instructions properly"

l1:
	zjmp	%:l2
	ld		%256, r1
	zjmp	%:l2
	ld		%0, r2
	zjmp	%:l3
l2:
	zjmp	%:l2
l3:
	sti		r1, %64, %0

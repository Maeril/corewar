.name		"All instructions possible - This name is very long for comparison purposes. It completly fills the space used for the name! "
.comment	"Corewar is fun. This comment is now filled with star wars prequel quotes. Hello there. General Kenobi, you're a bold one. I love democracy. This is where the fun begins. I'll try spinning, that's a good trick. You were the chosen one! Only a sith deals in absolutes. Then you are lost. Perhaps. The senate will decide your fate. I am the senate. Not yet. It's treason then. It's outrageous, it's unfair! What about the droid attack on the wookies? Oh no I'm not brave enough for politics. A fine addition to my collection. You have becme the very thing you swore to destroy. Farming, really? A man of your talents? We stand here amidst my achievement,not yours! I'm one with the force and the force is with me. 2044 characters is a lot longer than I expected, damned. Not just the men, but the women and children too. This is getting out of hands, now there are two of them! It's over Anakin, I have the high ground. Are we blind? Deploy the garrison! You are strong and wise Anakin, and I am very proud of you. We wont be seeing him again. We need to be going up, not down! The attempt onmy life has left me scarred and deformed. My powers have doubled since the last time we've met. Good, twice the pride, double the fall. If what you've told me is true, you will have gained my trust. Because of Obi-Wan? Did you ever hear the tragedy of Darth Plagueis The Wise?  I thought not. It's not a story the Jedi would tell you. It's a Sith legend. Darth Plagueis was a Dark Lord of the Sith, so powerful and so wise he could use the Force to influence the midichlorians to create life… He had such a knowledge of the dark side, he could even keep the ones he cared about from dying. The dark side of the Force is a pathway to many abilities some consider to be unnatural. He became so powerful… the only thing he was afraid of was losing his power, which eventually, of course, he did. Unfortunately, he taught his apprentice everything he knew, then his apprentice killed him in his sleep. Ironic. He could save others from death, but not himself."

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

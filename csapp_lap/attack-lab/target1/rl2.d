ROP coding:
1. to get target value:
   parsing value to stack, and using `POP $rax` instruction to get value.
2. the whole stack we inject would be only two kinds:
   P: gadget position, which ends up with a `RET` instruction
   V: target value to get with a gadget like `POP $rax`

so for level2:
the stack would be
_
|	touch2 Pos
test-st	gadget2 Pos	mov $eax,$edi
|	cookie Value 
-	gadget1 Pos     POP $rax
|
getbuf stack
|
_

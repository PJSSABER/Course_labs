ROP coding:
1. to get target value:
   parsing value to stack, and using `POP $rax` instruction to get value.
2. the whole stack we inject would be only two kinds:
   P: gadget position, which ends up with a `RET` instruction
   V: target value to get with a gadget like `POP $rax`
3. using $rsp to get the address of randomnized stack
so for level3:
the stack :

	target string 
	touch3 addr
	mov rax,rdi
	lea(rdi,rsi),rax
	mov ecx,esi
	mov edx,ecx
	mov eax,edx
	0x48
	popq eax
	movq rax,rdi
	movq rsp,rax

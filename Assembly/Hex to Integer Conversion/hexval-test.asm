# This file contains the hexValTest subprogram for testing hexVal.
#

	.globl	hexValTest

	.data

# Output strings
#
newline:
	.asciiz	"\n"
header:
	.asciiz "Testing hexVal ----------------------------------\n\n"
prefix:
	.asciiz "hexVal('"
suffix:
	.asciiz "') = "

# Test string
#
testString:
	.asciiz "/059:@ACFG`acfg"

	.text

# procedure hexValTest
#
# MAL call sequence:
#
#   jal     hexValTest
#
# Effect:
#
#   Runs tests on hexVal using each character in testString.
#
# Stack usage:
#
#   return address  ($ra)   saved at 0($sp)
#
# Temporary registers
# This procedure is treated as part of the main program
# so it uses the $s registers instead of the $t registers.
#
#   $s0 - current address in testString
#   $s1 - ch, the string value
#
hexValTest:
	sub		$sp, $sp, 4		# push return address
	sw		$ra, 0($sp)

	li		$v0, 4			# print hexVal test header
	la		$a0, header
	syscall

	la		$s0, testString	# load start address of tesString

hexValTestLoop:
	lb		$s1, 0($s0)		# ch = character at current address in testString
	beqz	$s1, done		# if ch is a null byte return

	li		$v0, 4			# print "hexVal('"
	la		$a0, prefix
	syscall
	li		$v0, 11			# print ch
	move	$a0, $s1
	syscall
	li		$v0, 4			# print "') = "
	la		$a0, suffix
	syscall
	move	$a0, $s1		# print hexVal(ch)
	jal		hexVal
	move	$a0, $v0
	li		$v0, 1
	syscall
	li		$v0, 4			# print a newline
	la		$a0, newline
	syscall

	add		$s0, $s0, 1		# advance to next character in testString and repeat
	b		hexValTestLoop

done:
	li		$v0, 4			# print a blank line
	la		$a0, newline
	syscall

	lw		$ra, 0($sp)		# pop return address and return
	add		$sp, $sp, 4
	jr		$ra

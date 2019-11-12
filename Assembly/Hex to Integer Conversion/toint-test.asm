# This file contains the toIntTest subprogram for testing toInt.
#

	.globl	toIntTest

	.data

# Output strings
#
newline:
	.asciiz	"\n"
header:
	.asciiz	"Testing toInt -----------------------------------\n\n"
prefix:
	.asciiz "toInt(\""
suffix:
	.asciiz "\") = "
errorOut:
	.asciiz "error"

# Test strings
#
test1:
	.asciiz	"a"
test2:
	.asciiz	"ff"
test3:
	.asciiz	"43E"
test4:
	.asciiz	"C840"
test5:
	.asciiz	"7FfFfFfF"
test6:
	.asciiz	"7FfFgFfF"
test7:
	.asciiz	""

# The tests array contains the addresses of the test strings.
# It is terminated by a null address to signal no more tests.
tests:
	.word	test1
	.word	test2
	.word	test3
	.word	test4
	.word	test5
	.word	test6
	.word	test7
	.word	0

 	.text
 	
# procedure toIntTest
#
# MAL call sequence:
#
#   jal     toIntTest
#
# Effect:
#
#   Runs tests on toInt using each string in the tests array.
#
# Stack usage:
#
#   return address  ($ra)   saved at 0($sp)
#
# Temporary registers
# This procedure is treated as part of the main program
# so it uses the $s registers instead of the $t registers.
#
#   $s0 - current address in tests array
#   $s0 - the address of the current test string 
#   $s1 - n, the string value
#   
toIntTest:
	sub		$sp, $sp, 4		# push return address
	sw		$ra, 0($sp)

	li		$v0, 4			# print toInt test header
	la		$a0, header
	syscall

	la		$s0, tests

loopTop:
	lw		$s1, 0($s0)		# $s1 = address of next test string
	beqz	$s1, done		# return if its null

	li		$v0, 4			# print "toInt(""
	la		$a0, prefix
	syscall
	li		$v0, 4			# print test string
	move	$a0, $s1
	syscall
	li		$v0, 4			# print "") = "
	la		$a0, suffix
	syscall

	move	$a0, $s1
	jal		toInt

	beqz	$v1, error		# if success == false print "error"

	move	$a0, $v0		# print toInt return value
	li		$v0, 1
	syscall
	b		endLine

error:
	la		$a0, errorOut	# print "error"	as return value
	li		$v0, 4
	syscall

endLine:
	li		$v0, 4			# print a newline
	la		$a0, newline
	syscall

	add		$s0, $s0, 4		# advance to next test string and repeat
	b		loopTop

done:
	li		$v0, 4			# print a blank line
	la		$a0, newline
	syscall

	lw		$ra, 0($sp)		# pop return address and return
	add		$sp, $sp, 4
	jr		$ra

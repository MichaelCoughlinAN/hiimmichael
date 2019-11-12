# This program computes and displays f(n) = 3*f(n - 1) + 1 of n, where n is entered
# by the user.  The program prompts for new values of n until the user
# enters a negative number.
#

	.globl main

	.data

# main program string constants
#
prompt:
	.asciiz		"Please enter a positive integer:  "
result:
	.asciiz		" = "
newline:
	.asciiz		"\n"
done:
	.asciiz		"Program terminated."

	.text

# main program
#
# Register usage:
#
#   n:        $s0
#   function: $s1
#
main:
	li		$v0, 4			# issue prompt
	la		$a0, prompt
	syscall

	la		$v0, 5			# get n from user
	syscall
	move	$s0, $v0

	bltz	$v0, end		# terminate if n < 0

	move	$a0, $s0		# nFunct = functionF(n)
	jal		function
	move	$s1, $v0

	li		$v0, 1			# print n
	move	$a0, $s0
	syscall

	li		$v0, 4			# print " = "
	la		$a0, result
	syscall

	li		$v0, 1          # print nFunct
	move	$a0, $s1
	syscall

	li		$v0, 4			# print two newlines
	la		$a0, newline
	syscall
	li		$v0, 4
	la		$a0, newline
	syscall

	b		main			# repeat with new n

end:
	li		$v0, 4			# print a termination message
	la		$a0, done
	syscall

	li		$v0, 4			# print a newline
	la		$a0, newline
	syscall
    
	li		$v0, 10			# terminate the program
	syscall
	
# function functionF
#
# C synopsis:
#
#   int functionF(int n)
#
# Typical C call:
#
#   nFunct = functionF(n);
#
# Effect:
#
#   Puts 3*f(n - 1) + 1 into nFunct.
#
# MAL call sequence assuming n is $s0, nFunct is $s1:
#
#   move    $a0, $s0
#   jal     function
#   move    $s1, $v0
#
# Stack usage:
#
#   return address  ($ra)   saved at 0($sp)
#   n               ($a0)   saved at 4($sp)
#
function:
	bgtz	$a0, recur		# recur if n > 0

	li		$v0, 0			# else just return 1
	jr		$ra
recur:
	sub		$sp, $sp, 8		# allocate stack frame
	sw		$ra, 0($sp)		# with return address at 0($sp)
	sw		$a0, 4($sp)		# and n at 4($sp)

	sub		$a0, $a0, 1		# $v0 = functionF(n - 1)
	jal		function

	lw		$ra, 0($sp)		# restore return address
	lw		$a0, 4($sp)		# and n from the stack frame
	add		$sp, $sp, 8		# and deallocate it

	mul		$v0, $v0, 3	   # return 3*f(n-1)
	add     $v0, $v0, 1
	jr		$ra

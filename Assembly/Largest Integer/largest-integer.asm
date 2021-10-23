# This program that returns the largest positive integer n,
# where n is entered by the user. 
# Michael Coughlin 
# 2015
#
 	.globl	main

	.data

# program output text constants
greeting:
	.asciiz "Welcome to Programming Assignment 1! Enter '0' or any negative number to exit."
prompt:
	.asciiz	"Please enter a positive integer: "
result:
	.asciiz	"The largest value that was entered was: "
newline:
	.asciiz	"\n"

 	.text

# main program
#
# program variables
#   largest: $s0
#   temp: $s1
#
main:
    li      $s0, 0          # largest = 0
   	li      $s1, 0          # temp = 0
    
	li		$v0, 4			# issue greeting
	la		$a0, greeting
	syscall
	li		$v0, 4			# prints a newline
	la		$a0, newline
	syscall
	
loop_top:
	li		$v0, 4			# issue prompt
	la		$a0, prompt
	syscall

	li		$v0, 5			# get largest n from user
	syscall
	move	$s1, $v0
     
    bgt $s0, $s1 next		# if (temp > largest)
    move $s0, $s1           #   largest = temp; 
    
next:
  bgtz $s1 loop_top	
  
	li		$v0, 4			# print result 
	la		$a0, result
	syscall

	li		$v0, 1			# print largest
	move	$a0, $s0
	syscall

	li		$v0, 10			# terminate the program
	syscall

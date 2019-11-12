# This file contains the main program for testing the hexVal and toInt subprograms.
#

	.globl	main
 	
main:

	# do tests
	# Either of these test can be omitted by putting a # at the beginning of the line.
	jal		hexValTest
	jal		toIntTest
	
	li		$v0, 10			# terminate the program
	syscall

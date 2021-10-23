# This program sorts an array of integers using a test array. 
# Subprogram printArray displays the contents of the array. 
# Michael Coughlin
# hiimmichael.com
# 2015
#

.data

testArray:	
    .word   9
    .word   8
    .word   7
    .word   4
    .word   5
    .word   6
    .word   3
    .word   2
    .word   1
    .word   0

before:	 .asciiz "Before sorting the array:\n"  
after:	 .asciiz "After sorting the array:\n" 
newline:    .asciiz "\n" 
done: .asciiz		"Program terminated."

	.text
	.globl	main

main:	
	li	$v0,4			# print before string
	la	$a0, before
	syscall

	jal	printArray		# print the unsorted array
	jal	sortArray	    # sort the array using the Bubble Sort
	li	$v0, 4			# print after string
	la	$a0, newline
	syscall

	la	$a0, after
	syscall

	jal	printArray		# Print the array now sorted

	li	$v0, 10			# terminate
	syscall	

# function printArray
#
# C synopsis:
#
#   void printArray(int Array[], int size)
#
# Effect:
#
#   Prints out all the elements of the given array.
#
printArray:
	li $t1, 0			# t1: offset from the beginning of the array				
	li $t2, 40			# t2 = 40 = 4*10

print:
	li	$v0, 1			# print the value at array(t1)
	lw	$a0, testArray($t1)	
	syscall
	
    li $v0, 4           # print newline
    la $a0, newline
    syscall
    
	addi $t1, $t1, 4    # update offset
					
	blt	$t1, $t2, print
	jr		$ra		
			
# function sortArray
#
# C synopsis:
#
#   void sortArray(int Array[], int entryCount)
#
# Effect:
#
#    Sorts an array of integers.
#
sortArray:
	li	$t7, 40		            # size of array	       
	li	$t1, 4			        # size of word
outer:
	lw	$t0, testArray($0)	    # $t0, first element
	sub	$t4, $t7, $t1	 	    # $t4 = $t7 - $t1, outer element
	li	$t2, 0			        # $t2 = 0
inner:
	add $t3, $t2, 4		        # $t3 = $t2 + 4, inner element
						        
	lw	$t6, testArray($t3)	        # $t6 = current inner elemnt
	blt	$t0, $t6, else_condition    # if $t0 >= $t6 
	sw	$t6, testArray($t2)	        #    swap($t2, $t6)
	b end_if_condition
else_condition:
	sw	$t0, testArray($t2)	        # else	$t2 = $t0
	lw	$t0, testArray($t3)	        # $t0 = $t3
end_if_condition:
	add $t2, $t2, 4		            # $t2 = $t2 + 4
	blt	$t2, $t4, inner	            # if $t2 < $t4  branch to inner
inner_end:
	sw	$t0, testArray($t4)	      # $t4 = $t0
	add $t1, $t1, 4		          # $t1 = $t1 + 4
	blt	$t1, $t7, outer	           # if $t1 < $t7 branch to outer
outer_end:
	jr	$ra

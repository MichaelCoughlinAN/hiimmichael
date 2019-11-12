# This program sorts an array of integers using a test array
# and QuickSort algorithm. 
# Subprogram printArray displays the contents of the array. 
# Michael Coughlin
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
    
testArray1:	
    .word   9
    .word   -1
    .word   7
    .word   10
    .word   5
    .word   6
    .word   3
    .word   2
    .word   1
    .word   0
    
testArray2:	
    .word   3
    .word   4
    .word   2
    .word   1
  

before:	  .asciiz  "Before sorting the array:\n"  
after:	  .asciiz  "After sorting the array:\n" 
newline:  .asciiz  "\n" 
done:     .asciiz  "Program terminated."

	.text
	.globl	main

main:	
	li	$v0, 4			# print before string
	la	$a0, before
	syscall
   
	jal	PrintArray		# print the unsorted array
	
    la $a0, testArray   # $a0 = address of array to be sorted
    li $a1, 0           # $a1 = 0
    li $a2, 9           # $a2 = number of elements - 1
    
	jal	QuickSort	    # sort the array using the Bubble Sort
	li	$v0, 4			# print after string
	la	$a0, newline
	syscall

	la	$a0, after
	syscall

	jal	PrintArray		# Print the array now sorted

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
PrintArray:
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
	jr $ra		

# function printArray
#
# C synopsis:
#
#   void quicksort(int Array[], int start, int end)
#
# Effect:
#
#   Sorts all the elements of the given array.
#
# Register Usage:
#   $a0 = address of array to be sorted
#   $a1 = 0
#   $a2 = number of elements - 1
#
QuickSort:
    bgt $a1, $a2, end  # Array does not need to be sorted  

    sub $sp, $sp, 16     # create space in memory
    sw $ra, 16($sp)      # save $ra
    sw $a0, 12($sp)      # save $a0
    sw $a1, 8($sp)       # save $a1
    sw $a2, 4($sp)       # save $a2
    
    jal PartitionArray   # partitionArray(int Array[], int lo, int hi)

    sub $sp, $sp, 4      # create space in memory
    sw $v0, 4($sp)   
    lw $a0, 16($sp)      # $a0 = $v0
    lw $a1, 12($sp)      # $a1 = $a0
    add $a2, $v0, -1     # $a2 = end - 1 
    
    jal QuickSort

    lw $a0, 16($sp)      # $a0 = $v0
    lw $t0, 4($sp)
    add $a1, $t0, 1      # $a1 = start + 1
    lw $a2, 8($sp)       # $a2 = end
    
    jal QuickSort

    add $sp, $sp, 20
    lw $ra, 0($sp)    
end: 
    jr $ra 

# function partitionArray
#
# C synopsis:
#
#   void PartitionArray(int A[], int lo, int hi)
#
# Effect:
#
#   Reorder the array so that all elements with values less 
#   than the pivot come before the pivot, while all elements 
#   with values greater than the pivot come after it (equal 
#   values can go either way). After this partitioning, 
#   the pivot is in its final position. 
#
# Register Usage:
#   $a0 = address of array to be sorted
#   $a1 = lo
#   $a2 = hi
#   $t1 = used to find pivot
#   $t2 = pivot address
#   $t3 = lo + 1
#   $t4 = hi
#   $t5, $t7, $t8, $t9 = Array[lower] & Array[hi]
#   $t6 = temp
#
PartitionArray:
    add $t1, $a1, $a1
    add $t1, $t1, $t1
    add $t1, $t1, $a0    # $t2 = pivot
    lw  $t2, 0($t1)      # pivot address
    add $t3, $a1, 1      # $t3 = lo + 1
    add $t4, $a2, 0      # $t4 = hi
Do:
    blt $t4, $t3, EndPartition

loop1:
    add $t8, $t3, $t3
    add $t8, $t8, $t8
    add $t8, $t8, $a0      
    lw $t5, 0($t8)       # $t5 = Array[lo]
    ble $t5, $t2, loop1_condition
    b loop2
loop1_condition:
    ble $t3, $t4, loop1_operation
    b loop2   
loop1_operation:
    add $t3, $t3, 1
    b loop1
    
loop2:
    add $t8, $t4, $t4
    add $t8, $t8, $t8
    add $t8, $t8, $a0      
    lw $t5, 0($t8)       # $t5 = Array[hi]
    bgt $t5, $t2, loop2_condition
    b temp_swap    
loop2_condition:
    ble $t3, $t4, loop2_operation
    b temp_swap   
loop2_operation:
    add $t4, $t4, -1
    b loop2
    
temp_swap:
    bgt $t3, $t4, Do
    add $t8, $t3, $t3
    add $t8, $t8, $t8
    add $t8, $t8, $a0      
    lw  $t6, 0($t8)       # temp = Array[lo]
    add $t9, $t4, $t4
    add $t9, $t9, $t9
    add $t9, $t9, $a0      
    lw  $t7, 0($t9)       # Array[hi]
    sw  $t7, 0($t8)       # Array[lo] = Array[hi]
    sw  $t6, 0($t9)       # Array[hi] = temp
    add $t3, $t3, 1
    add $t4, $t4, -1
    j Do
    
EndPartition:
    add  $t8, $t4, $t4
    add  $t8, $t8, $t8
    add  $t8, $t8, $a0      
    lw  $t2, 0($t8)       # temp = Array[hi]
    add $t9, $a1, $a1
    add $t9, $t9, $t9
    add $t9, $t9, $a0      
    lw  $t3, 0($t9)       # Array[lo]
    sw  $t3, 0($t8)       # Array[hi] = Array[lo]
    sw  $t2, 0($t9)       # Array[lo] = temp
    add $v0, $t4, 0      
    jr $ra


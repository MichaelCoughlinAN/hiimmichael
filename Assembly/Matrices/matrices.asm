# This program creates and displays matrices using a 
# descriptor containing the number of rows, number 
# of columns, and the base address of the entries,
# statically or dynamically allocated.
# Michael Coughlin
# 2015
#

.data

# static entries declaration
entries:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5

# static descriptor declaration for a 6x1 matrix
matrix6x1:
	.word	6	# 6 rows
	.word	1	# 1 column
	.word	entries
	
# static descriptor declaration for a 3x2 matrix
matrix3x2:
	.word	3	# 3 rows
	.word	2	# 2 columns
	.word	entries
	
# static descriptor declaration for a 2x3 matrix
matrix2x3:
	.word	2	# 2 rows
	.word	3	# 3 columns
	.word	entries
	
# static descriptor declaration for a 1x6 matrix
matrix1x6:
	.word	1	# 1 row
	.word	6	# 6 columns
	.word	entries

# string constants  
newline:  	 .asciiz  "\n" 
doublenewline:   .asciiz  "\n\n" 
space:    	 .asciiz  " "
done:     	 .asciiz  "Program terminated."
matrix6x1string: .asciiz  "6x1 matrix:\n"  
matrix3x2string: .asciiz  "3x2 matrix:\n"  
matrix2x3string: .asciiz  "2x3 matrix:\n"  
matrix1x6string: .asciiz  "1x6 matrix:\n"
matrix6x6string: .asciiz  "6×6 matrix using mcreate subprogram:\n"
 
	.text
	.globl	main

main:	
    li $v0, 4		     # print matrix6x1 string	
    la $a0, matrix6x1string
    syscall	
    la $a0, matrix6x1        # $a0 = matrix6x1 descriptor
    jal	mwrite		

    li $v0, 4                # print newlines
    la $a0, doublenewline
    syscall
    
    li $v0, 4		     # print matrix3x2 string
    la $a0, matrix3x2string
    syscall	
    la $a0, matrix3x2        # $a0 = matrix3x2 descriptor
    jal	mwrite	
    
    li $v0, 4                # print newlines
    la $a0, doublenewline
    syscall
    
    li	$v0, 4	             # print matrix2x3 string		
    la	$a0, matrix2x3string
    syscall	
    la $a0, matrix2x3        # $a0 = matrix2x3 descriptor
    jal	mwrite	
    
    li $v0, 4                # print newlines
    la $a0, doublenewline
    syscall
    
    li	$v0, 4		     # print matrix1x6 string	
    la	$a0, matrix1x6string
    syscall
    la $a0, matrix1x6        # $a0 = matrix1x6 descriptor
    jal	mwrite	
  
    li $v0, 4                # print newlines
    la $a0, doublenewline
    syscall
    
    li $v0, 4		     # print matrix6x6 string 	
    la $a0, matrix6x6string
    syscall	
    la $a0, 6                # $a0 = rows of matrix
    la $a1, 6                # $a1 = columns of matrix
    jal	mcreate	             # Dynamically create the matrix
    jal	mwrite	
    
    li	$v0, 10	             # terminate
    syscall	

# function mwrite
#
#  C Code Synopsis:
#	void mwrite(int descriptor[])
#
# Takes a descriptor containing the number of rows,
# number of columns, and the array containing 
# the entries and prints them out as a matrix.
# 
# Data Usage:
#	$a0: base address of descriptor
# 	$t1: offset from the beginning of the array	
#	$t2: byte size of array
# 	$t3: current element of array
#	$t4: base adress of array
#	$t5: temp register for number of rows 
#	$t6: temp register for number of columns
#       $t7: used to count through number of rows
#	$t8: number of rows
#       $t9: number of columns
#
mwrite:
	li $t1, 0						
	li $t2, 12			
	la $t3, ($a0)
	li $t5, 0
	li $t6, 0
loop:                         # This loop will go through and 
	lw $a0, ($t3)         # get the row size, column size,
        la $t4, ($a0)         # and entries array and assign 
        beqz $t1, condition   # them into temp registers listed
        j next                # above.
condition:
    	lw $t5, ($t3) 
next:
    	beq  $t1, 4, condition1
        j next1
condition1:
        lw $t6, ($t3) 
        move $t8, $t5
        move $t9, $t6
next1:
        add $t1, $t1, 4
	add $t3, $t3, 4      # update offset				
	blt $t1, $t2, loop
	li $t1, 0
	mul $t2, $t8, $t9    # the number of elements in the entries array	
	la $t3, ($t4)   
	li $t7, 0
 print:
 loop_top:
        beq $t7, $t9, exitwhile 
        add $t7, $t7, 1
	li $v0, 1	     
	lw $a0, ($t3)        # print the current element
	syscall
        la $t4, ($a0)
  	li $v0, 4            # print a space
        la $a0, space
        syscall 
        add $t1, $t1, 4
	add $t3, $t3, 4      # update offset				
	blt $t1, $t2, print
        b loop_top 
exitwhile:
	li $t7, 0
	sub $t8, $t8, 1     # row has been printed
	beqz $t8, exit
	li $v0, 4           # print newline
        la $a0, newline
        syscall
	b loop_top
exit:
	jr $ra		

# function mcreate
#
#  C Code Synopsis:
#	void mcreate(int rows, int columns)
#
# Takes the number of rows and number of columns and
# dynamically creates a descriptor for a matrix 
# containing the number of rows, columns, and an array
# of entries all instantiated to 0.
# 
# Data Usage:
#	$a0: number of rows
#	$a1: number of columns
# 	$t0: address of new entries array
#	$t1: address of descriptor	
#	$t2: total number of entries in matrix
# 	$t3: address of new entries array
#	$t4: number of rows
#
mcreate:
	mul $t2, $a0, $a1   # number of enteries
	la $t4, ($a0)
	li $v0, 9           # sbrk code
	li $a0, 144         # byte size of 6x6 matrix
	
	syscall
	move $t0, $v0       # address of the new array
	move $t3, $v0       # address of the new array
        li $t1, 0           # i = 0
        b cond_test
loop_top1:
        sw $zero, ($t0)     # theArray($t0) = 0
  	add $t1, $t1, 1     # i++
        add $t0, $t0, 4     # update offset
cond_test:
        blt $t1, $t2, loop_top1   # continue if i < 36       
	li $v0, 9      # sbrk code for matrix descriptor
	li $a0, 12  
	syscall
	move $t1, $v0 
 	la $a0, ($t4) # set the number of rows
        sw $a0, ($t1)         
        la $a0, ($t1)
   	add $t1, $t1, 4    
   	sw $a1, ($t1) # set the number of columns
        add $t1, $t1, 4    
        sw $t3, ($t1) # set the base address of entries array
        jr $ra


# This file contains the toInt subprogram.
# Michael Coughlin
# hiimmichael.com
# 2015
#

	.globl	toInt
 	
# function toInt
#
# C synopsis:
#
#   int toInt(hexDigits)
#
# MAL call sequence assuming hexDigits is statically declared:
#
#   la      $a0, hexDigits
#   jal     readHex
#
# Effect:
#
#   Returns ($v0) the integer value of hexDigits.
#   Also returns ($v1) a boolean success value.
#   This value is false (0) if there are any characters in hexDigits
#   other than hexadecimal digits.
#   Otherwise its value is true (nonzero).
#
# Stack usage:
#
#   return address  ($ra)   saved at 0($sp)
#
# Temporary registers
# 
#   $t1: n
#   $t2: next base r
#
toInt:	
    li $t1, 0
    li $v1, 1
    sub	$sp, $sp, 4		           # push return address
	sw	$ra, 0($sp)                # old address before stack push
	move $t3, $a0
	lb $t4, 0($t3)                 # take first byte of string and put into $t4
	beqz $t4, test_fail

 loop_top:    
    lb $t4, 0($t3)                 # while there are more base r digits
    move $a0, $t4                  # move $t4 back into $a0 so you can call hexVal on it
    beqz $t4, next                 # at end of string      
    jal	hexVal
    move $t2, $v0  
      
    beq $t2, -1, test_fail         # invalid hex digit
  
	mul $t1, $t1, 16               # multiply n by 16
	add	$t1, $t1, $t2	
	add	$t3, $t3, 1	
    j loop_top
    
    test_fail:                     # invalid char, set boolean $v1 to false
    li $v1, 0 
    next: 		
    move $v0, $t1                  # setting so values change 
    lw		$ra, 0($sp)		       # pop return address and return
	add		$sp, $sp, 4
	jr		$ra

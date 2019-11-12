# This file contains the hexVal subprogram.
#

	.globl	hexVal
 	
# function hexVal
#
# C synopsis:
#
#   int hexVal(char ch)
#
# MAL call sequence assuming ch is in $s0:
#
#   move    $a0, $s0
#   jal     hexVal
#
# Effect:
#
#   If ch is a valid hexadecimal digit then its hexadecimal value is returned. 
#   Otherwise -1 is returned. 
#
# Stack usage:
#
#   FIXME
#
# Temporary registers
#
#   FIXME if necessary (hexVal can be implemented without $s or $t registers)
#
hexVal:
blt $a0, '0', next
bgt $a0, '9', next
sub $v0, $a0, '0'                              #      int hexVal(char ch) {
j end                                          #        if ((ch1 >= '0') && (ch <= '9')) {
next:                                          #           return ch - '0';
                                               #          }
blt $a0, 'a', next1                            #        if (ch >= 'a') and (ch <= 'f') {
bgt $a0, 'f', next1                            #           return ch - 'a' + 10;
sub $a0, $a0, 'a'                              #          }
add $v0, $a0, 10                               #        if (ch >= 'A') and (ch <= 'F') {
j end                                          #           return ch - 'A' + 10;
next1:                                         #         }
                                               #         return -1;
blt $a0, 'A', next2                            #        }
bgt $a0, 'F', next2                            
sub $a0, $a0, 'A'                              
add $v0, $a0, 10
j end
next2:
li $v0, -1
	
	end: 	
	jr		$ra
	
	

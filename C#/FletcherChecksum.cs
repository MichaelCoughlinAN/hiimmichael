// Michael Coughlin
// hiimmichael.com
// 2019

using System;
using System.Text;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Diagnostics;

namespace Test {
    /// <summary>
    /// Calculates Fletcher's checksums
    /// Sample outputs: 
    /// Fletcher16: "abcde" -> 51440
    /// Fletcher32: "abcde" -> 3948201259
    /// Fletcher64: "abcde" -> 14034561336514601929
    /// </summary>
    public class FletcherChecksum {
        /// <summary>
        /// Transforms byte array into an enumeration of blocks of 'blockSize' bytes
        /// </summary>
        /// <param name="inputAsBytes"></param>
        /// <param name="blockSize"></param>
        /// <returns></returns>
        private IEnumerable<UInt64> Blockify(byte[] inputAsBytes, int blockSize) {
            int i = 0;

            //UInt64 used since that is the biggest possible value we can return.
            //Using an unsigned type is important - otherwise an arithmetic overflow will result
            UInt64 block = 0;

            //Run through all the bytes			
            while (i < inputAsBytes.Length) {
                //Keep stacking them side by side by shifting left and OR-ing				
                block = block << 8 | inputAsBytes[i];
                i++;

                //Return a block whenever we meet a boundary
                if (i % blockSize == 0 || i == inputAsBytes.Length) {
                    yield return block;
                    //Set to 0 for next iteration
                    block = 0;
                }
            }
        }

        /// <summary>
        /// Get Fletcher's checksum, n can be either 16, 32 or 64
        /// </summary>
        /// <param name="inputWord"></param>
        /// <param name="n"></param>
        /// <returns></returns>
        /// //            "abcde"-> 51440(0xC8F0)
        // "abcdef"-> 8279(0x2057)
        // "abcdefgh"-> 1575(0x0627)
        public byte[] GetChecksum(byte[] inputAsBytes, int n) {
            //Fletcher 16: Read a single byte
            //Fletcher 32: Read a 16 bit block (two bytes)
            //Fletcher 64: Read a 32 bit block (four bytes)
            int bytesPerCycle = n / 16;
            
            // ASCII encoding conveniently gives us 1 byte per character 
            UInt64 sum1 = 0;
            UInt64 sum2 = 0;
            
            foreach (UInt64 block in Blockify(inputAsBytes, bytesPerCycle)) {
                sum1 = (sum1 + block) % 255;
                sum2 = (sum2 + sum1) % 255;
            }
            
            ulong returnValue = (sum2 << 8) | sum1;
            //Debug.Print(returnValue.ToString());
            //Debug.Print(BitConverter.IsLittleEndian.ToString());
            return BitConverter.GetBytes(returnValue);
        }
    }
}

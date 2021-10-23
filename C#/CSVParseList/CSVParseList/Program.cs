// Michael Coughlin
// hiimmichael.com
// 2019

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSVParseList {
    class Program {
        
        static void Main(string[] args) {
            string file1 = @"Output1.txt";
            string file2 = @"OutputChinese1.txt";
            string output = @"final.txt";

            const Int32 BufferSize = 128;
            using (var fileStream = File.OpenRead(file1))

            using (var streamReader = new StreamReader(fileStream, Encoding.UTF8, true, BufferSize)) {
                String line;
                while ((line = streamReader.ReadLine()) != null) {
                    using (StreamWriter sw = File.AppendText(output)) {
                        Console.WriteLine("Writing line (" + line + ") from " + Path.GetFileName(file1));
                        sw.WriteLine("\"" + line +  "\",");
                    }
                }
            }

            using (var fileStream = File.OpenRead(file2))

            using (var streamReader = new StreamReader(fileStream, Encoding.UTF8, true, BufferSize)) {
                String line;
                while ((line = streamReader.ReadLine()) != null) {
                    using (StreamWriter sw = File.AppendText(output)) {
                        Console.WriteLine("Writing line (" + line + ") from " + Path.GetFileName(file2));
                        sw.WriteLine("\"" + line + "\",");
                    }
                }
            }

            Console.WriteLine("Done.");
            Console.ReadLine();
        }
    }
}
